// 컴퓨터네트워크 과제 - Socket 기반 1:1 채팅 + TCP/UDP 특성 시험 프로그램
//
// 지원 기능
//   - TCP / UDP 양쪽 모두 구현
//   - IP 입력 / 미입력(기본값 사용) 모두 지원  -> 총 4가지 케이스
//   - Port 입력 / 미입력(기본값 9000) 지원
//   - 송신 스레드와 수신 스레드를 분리한 전이중(full-duplex) 채팅
//   - 소켓이 실제로 통신 중임을 보여 주는 /info, /stats 명령
//   - TCP/UDP 특성을 수치로 비교하는 시험 기능 (/flood, /report, /pause)
//
// 빌드: g++ -o socket.exe Socket.cpp -lws2_32
// 실행: run.bat 실행, 또는 콘솔 두 개에서 각각 서버/클라이언트로 실행

#include <winsock2.h>
#include <ws2tcpip.h>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

#pragma comment(lib, "ws2_32.lib")  // MSVC용. g++는 -lws2_32 옵션 사용

// 주의: using namespace std 때문에 소켓 bind()가 함수 객체를 만드는 std::bind()와
// 이름이 겹침. 그래서 소켓 bind는 전역 범위를 뜻하는 ::bind() 로 적어야 함.

const unsigned short DEFAULT_PORT = 9000;
const char* DEFAULT_CLIENT_IP = "127.0.0.1";  // 클라이언트가 IP 미입력 시 접속할 루프백 주소
const int BUF_SIZE = 1024;

// 수신 버퍼를 일부러 작게 잡음.
// 기본값(수십~수백 KB)이면 루프백에서는 UDP도 거의 유실되지 않아 신뢰성 차이가
// 드러나지 않음. TCP와 UDP에 같은 크기를 적용해 공정한 비교 조건을 만듦.
// 같은 조건에서 TCP는 흐름 제어와 재전송으로 유실 0, UDP는 대량 유실이 발생함.
const int TEST_RCVBUF = 8192;

// ---------------------------------------------------------------------------
// 애플리케이션 계층 프로토콜 (이 프로그램이 직접 정한 규칙)
//
//   MSG|닉네임|본문       일반 채팅 메시지
//   BYE|닉네임|           퇴장 알림
//   BGN|닉네임|총개수     시험 시작 (수신측 카운터 초기화)
//   SEQ|닉네임|순번       시험 데이터 (화면에 출력하지 않고 세기만 함)
//   END|닉네임|총개수     시험 종료 (수신측이 결과 출력)
//
// 소켓은 "바이트를 옮기는 통로"일 뿐이라 어디까지가 한 메시지인지 알려주지 않음.
// 그래서 위와 같은 형식을 애플리케이션이 직접 정해야 함.
//   - TCP: 바이트 스트림이라 경계가 없음. 메시지 끝에 개행을 붙여 구분
//   - UDP: 데이터그램 단위라 보낸 그대로 한 덩어리로 도착. 구분자 불필요
// ---------------------------------------------------------------------------

atomic<bool> g_running(true);       // 채팅 종료 여부
atomic<long long> g_sentBytes(0);   // 통계: 보낸 바이트
atomic<long long> g_recvBytes(0);   // 통계: 받은 바이트
atomic<long long> g_sentMsgs(0);    // 통계: 보낸 메시지 수
atomic<long long> g_recvMsgs(0);    // 통계: 받은 메시지 수
mutex g_coutMtx;                    // 두 스레드가 동시에 출력하는 것을 방지

// ---- 시험용 카운터 ----
atomic<long long> g_testTotal(0);   // 상대가 보냈다고 알려 준 총 개수
atomic<long long> g_seqRecv(0);     // 실제로 받은 SEQ 개수
atomic<long long> g_recvCalls(0);   // 데이터를 담아 온 recv/recvfrom 호출 횟수
atomic<long long> g_msgParsed(0);   // 그 호출들에서 꺼낸 메시지 총 개수
atomic<int> g_pauseSec(0);          // 수신을 잠시 멈출 초 (흐름 제어 관찰용)
string g_proto = "?";               // 화면 표기용 프로토콜 이름

// 수신 스레드와 입력 스레드가 동시에 cout을 쓰면 글자가 섞이므로 잠금 사용
void safePrint(const string& s) {
    lock_guard<mutex> lock(g_coutMtx);
    cout << s << flush;
}

// 현재 시각을 "HH:MM:SS" 형태로 반환. 메시지가 오간 시점을 보여 주는 용도
string nowTime() {
    time_t t = time(nullptr);
    tm lt;
    localtime_s(&lt, &t);
    char buf[16];
    strftime(buf, sizeof(buf), "%H:%M:%S", &lt);
    return string(buf);
}

// Winsock 오류 메시지 출력 후 종료
void die(const char* msg) {
    cout << "[오류] " << msg << " (코드: " << WSAGetLastError() << ")\n";
    WSACleanup();
    exit(1);
}

// sockaddr_in -> "IP:Port" 문자열 변환
string addrToString(const sockaddr_in& addr) {
    char buf[INET_ADDRSTRLEN];
    InetNtopA(AF_INET, (void*)&addr.sin_addr, buf, sizeof(buf));
    return string(buf) + ":" + to_string(ntohs(addr.sin_port));
}

// 시험 조건을 맞추기 위해 수신 버퍼 크기를 줄임
void shrinkRecvBuffer(SOCKET sock) {
    int rcvbuf = TEST_RCVBUF;
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbuf, sizeof(rcvbuf));
}

// --------------------------------------------------------------- 사용자 입력

// 포트 번호 입력받음. 그냥 엔터 치면 기본 포트 사용
unsigned short inputPort() {
    while (true) {
        cout << "포트 번호 입력 (엔터 시 " << DEFAULT_PORT << "): ";
        string line;
        getline(cin, line);

        if (line.empty()) {
            cout << "  -> 포트 미입력: 기본 포트 " << DEFAULT_PORT << " 사용\n";
            return DEFAULT_PORT;
        }

        try {
            int port = stoi(line);
            // 0번은 예약, 65535가 16비트 최대값
            if (port < 1 || port > 65535) {
                cout << "  [오류] 포트는 1~65535 범위여야 합니다.\n";
                continue;
            }
            // 0~1023은 well-known port로 예약되어 있어 충돌 가능성 높음
            if (port < 1024)
                cout << "  [경고] 0~1023은 well-known port입니다. 충돌할 수 있습니다.\n";

            cout << "  -> 입력한 포트: " << port << "\n";
            return (unsigned short)port;
        } catch (...) {
            cout << "  [오류] 숫자를 입력하세요.\n";
        }
    }
}

// IP 입력받음. 그냥 엔터 치면 빈 문자열 반환
string inputIP(bool isServer) {
    if (isServer)
        cout << "바인딩할 IP 입력 (엔터 시 모든 인터페이스 0.0.0.0): ";
    else
        cout << "접속할 서버 IP 입력 (엔터 시 " << DEFAULT_CLIENT_IP << "): ";

    string ip;
    getline(cin, ip);
    return ip;
}

// 채팅에 사용할 닉네임 입력받음
string inputNick() {
    cout << "닉네임 입력 (엔터 시 user): ";
    string nick;
    getline(cin, nick);
    if (nick.empty()) nick = "user";
    // 세로줄은 프로토콜 구분자라 닉네임에 들어가면 안 됨
    for (char& c : nick)
        if (c == '|') c = '_';
    return nick;
}

// 입력받은 IP와 Port로 sockaddr_in 구성.
// ip가 비어 있으면 서버는 INADDR_ANY, 클라이언트는 127.0.0.1 사용
sockaddr_in makeAddr(const string& ip, bool isServer, unsigned short port) {
    sockaddr_in addr;
    ZeroMemory(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);  // 호스트 바이트 순서 -> 네트워크 바이트 순서

    if (ip.empty()) {
        if (isServer) {
            // IP 미입력: 이 PC의 모든 네트워크 인터페이스에서 수신
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            cout << "  -> IP 미입력: 0.0.0.0 (모든 인터페이스)으로 바인딩합니다.\n";
        } else {
            // IP 미입력: 같은 PC의 서버로 접속 (루프백 테스트용)
            InetPtonA(AF_INET, DEFAULT_CLIENT_IP, &addr.sin_addr);
            cout << "  -> IP 미입력: " << DEFAULT_CLIENT_IP << " 로 접속합니다.\n";
        }
    } else {
        // IP 입력: 점 10진 표기 문자열을 32비트 주소로 변환
        if (InetPtonA(AF_INET, ip.c_str(), &addr.sin_addr) != 1) {
            cout << "[오류] 올바른 IP 주소 형식이 아닙니다: " << ip << "\n";
            WSACleanup();
            exit(1);
        }
        cout << "  -> 입력한 IP: " << ip << "\n";
    }
    return addr;
}

// ------------------------------------------------------------------ 프로토콜

// "타입|닉네임|본문" 형태로 조립
string encode(const string& type, const string& nick, const string& body) {
    return type + "|" + nick + "|" + body;
}

// "타입|닉네임|본문" 분해. 형식이 깨졌으면 전체를 본문으로 취급
void decode(const string& raw, string& type, string& nick, string& body) {
    size_t p1 = raw.find('|');
    size_t p2 = (p1 == string::npos) ? string::npos : raw.find('|', p1 + 1);
    if (p1 == string::npos || p2 == string::npos) {
        type = "MSG";
        nick = "?";
        body = raw;
        return;
    }
    type = raw.substr(0, p1);
    nick = raw.substr(p1 + 1, p2 - p1 - 1);
    body = raw.substr(p2 + 1);
}

// -------------------------------------------------------- 소켓 상태 출력(증명)

// getsockname / getpeername으로 OS가 실제 할당한 주소 확인.
// 소켓이 정말 연결되어 있는지 보여 주는 근거 자료
void printSocketInfo(SOCKET sock, const char* proto) {
    string s = "\n--- 소켓 정보 (" + string(proto) + ") ---\n";

    sockaddr_in local;
    int len = sizeof(local);
    if (getsockname(sock, (sockaddr*)&local, &len) == 0)
        s += "  내 주소   (local): " + addrToString(local) + "\n";
    else
        s += "  내 주소   (local): 확인 실패\n";

    sockaddr_in peer;
    len = sizeof(peer);
    if (getpeername(sock, (sockaddr*)&peer, &len) == 0)
        s += "  상대 주소 (peer) : " + addrToString(peer) + "\n";
    else
        s += "  상대 주소 (peer) : 없음 (UDP는 연결이 없어 peer 정보가 없습니다)\n";

    s += "  소켓 핸들 값     : " + to_string((long long)sock) + "\n";
    s += "------------------------\n";
    safePrint(s);
}

// 지금까지 주고받은 양 출력. 데이터가 실제로 오갔다는 증거
void printStats() {
    string s = "\n--- 송수신 통계 ---\n";
    s += "  보낸 메시지: " + to_string(g_sentMsgs.load()) +
         " 건 / " + to_string(g_sentBytes.load()) + " 바이트\n";
    s += "  받은 메시지: " + to_string(g_recvMsgs.load()) +
         " 건 / " + to_string(g_recvBytes.load()) + " 바이트\n";
    s += "------------------\n";
    safePrint(s);
}

// ------------------------------------------------------------- 시험 결과 출력

// 유실률과 "recv 호출당 메시지 수"를 계산해 출력.
//   - 유실률          : 신뢰성 차이를 보여 줌 (TCP 0% vs UDP 대량)
//   - 호출당 메시지 수 : 스트림/데이터그램 차이를 보여 줌
//                       TCP는 여러 메시지가 한 번에 뭉쳐 오므로 1보다 큼
//                       UDP는 경계가 보존되므로 항상 정확히 1
void printTestReport() {
    long long total = g_testTotal.load();
    long long got = g_seqRecv.load();
    long long lost = (total > got) ? (total - got) : 0;
    long long calls = g_recvCalls.load();
    long long parsed = g_msgParsed.load();

    char lossPct[32] = "0.00";
    if (total > 0) snprintf(lossPct, sizeof(lossPct), "%.2f", 100.0 * lost / total);

    char perCall[32] = "0.00";
    if (calls > 0) snprintf(perCall, sizeof(perCall), "%.2f", (double)parsed / calls);

    string s = "\n=========== 시험 결과 (" + g_proto + ") ===========\n";
    s += "  상대가 보낸 개수   : " + to_string(total) + "\n";
    s += "  실제로 받은 개수   : " + to_string(got) + "\n";
    s += "  유실               : " + to_string(lost) + " (" + lossPct + "%)\n";
    s += "  --------------------------------------\n";
    s += "  recv 호출 횟수     : " + to_string(calls) + "\n";
    s += "  호출당 평균 메시지 : " + string(perCall) + " 개\n";
    s += "  수신 버퍼 크기     : " + to_string(TEST_RCVBUF) + " 바이트\n";
    s += "==========================================\n";
    safePrint(s);
}

// 받은 메시지 한 건을 처리. 상대가 나갔으면 false 반환
bool handleMessage(const string& raw) {
    string type, nick, body;
    decode(raw, type, nick, body);

    g_recvMsgs++;
    g_msgParsed++;

    if (type == "BYE") {
        safePrint("\n*** [" + nowTime() + "] " + nick + " 님이 나갔습니다. ***\n"
                  "엔터를 누르면 종료됩니다.\n");
        return false;
    }
    if (type == "BGN") {
        // 새 시험이 시작되므로 카운터를 0으로 되돌림
        g_testTotal = atoll(body.c_str());
        g_seqRecv = 0;
        g_recvCalls = 0;
        g_msgParsed = 0;
        safePrint("\n[시험] " + nick + " 님이 " + body + "개 전송을 시작했습니다...\n");
        return true;
    }
    if (type == "SEQ") {
        // 시험 데이터는 화면에 찍지 않고 세기만 함 (출력이 병목이 되면 안 되므로)
        g_seqRecv++;
        return true;
    }
    if (type == "END") {
        g_testTotal = atoll(body.c_str());
        printTestReport();
        return true;
    }

    safePrint("[" + nowTime() + "] " + nick + "> " + body + "\n");
    return true;
}

void printHelp() {
    safePrint("\n--- 명령어 ---\n"
              "  /info        현재 소켓의 실제 주소 정보 확인\n"
              "  /stats       주고받은 메시지/바이트 통계 확인\n"
              "  /flood N     시험용 메시지 N개 연속 전송 (예: /flood 10000)\n"
              "  /report      마지막 시험 결과 다시 출력\n"
              "  /pause N     수신을 N초간 멈춤 (TCP 흐름 제어 관찰용)\n"
              "  /help        이 도움말\n"
              "  /exit        채팅 종료\n"
              "그 외 입력은 모두 상대에게 전송됩니다.\n"
              "--------------\n");
}

// 수신 스레드가 매번 확인. /pause 로 지정된 시간만큼 수신을 멈춤.
// 수신을 멈추면 TCP는 버퍼가 차면서 송신측 send()가 블로킹됨(흐름 제어).
// UDP는 그런 장치가 없어 송신측이 계속 보내고 그만큼 버려짐.
void applyPauseIfRequested() {
    int p = g_pauseSec.exchange(0);
    if (p > 0) {
        safePrint("[시험] 수신을 " + to_string(p) + "초간 멈춥니다 (흐름 제어 관찰)\n");
        this_thread::sleep_for(chrono::seconds(p));
        safePrint("[시험] 수신 재개\n");
    }
}

// 순번을 붙인 메시지를 n개 연속 전송.
// sendOne 이 실제 전송을 담당하므로 TCP/UDP 양쪽에서 같은 코드를 사용함
template <typename SendFn>
void runFlood(const string& nick, long long n, SendFn sendOne) {
    safePrint("[시험] " + to_string(n) + "개 연속 전송 시작...\n");

    // 수신측 카운터를 초기화시킴. 버스트 전이라 이 메시지는 유실될 가능성이 낮음
    sendOne(encode("BGN", nick, to_string(n)));
    this_thread::sleep_for(chrono::milliseconds(100));

    auto t0 = chrono::steady_clock::now();
    long long ok = 0;
    for (long long i = 1; i <= n; i++) {
        if (!sendOne(encode("SEQ", nick, to_string(i)))) break;
        ok++;
    }
    auto ms = chrono::duration_cast<chrono::milliseconds>(
                  chrono::steady_clock::now() - t0).count();

    // 버스트가 끝나고 수신측 버퍼가 비워질 시간을 준 뒤 종료를 알림
    this_thread::sleep_for(chrono::milliseconds(500));
    sendOne(encode("END", nick, to_string(ok)));

    safePrint("[시험] 전송 완료: " + to_string(ok) + "개, " +
              to_string(ms) + " ms 소요\n"
              "[시험] 결과는 받는 쪽 화면에 출력됩니다.\n");
}

// 입력한 명령에서 숫자 인자를 꺼냄. 없거나 잘못되면 기본값 반환
long long parseArg(const string& line, long long defaultValue) {
    size_t sp = line.find(' ');
    if (sp == string::npos) return defaultValue;
    try {
        long long v = stoll(line.substr(sp + 1));
        return (v > 0) ? v : defaultValue;
    } catch (...) {
        return defaultValue;
    }
}

// =============================================================== TCP 채팅

// TCP는 스트림이라 요청한 만큼 한 번에 다 보내지 않을 수 있음. 다 보낼 때까지 반복
bool sendAllTcp(SOCKET sock, const string& data) {
    const char* p = data.c_str();
    int left = (int)data.size();
    while (left > 0) {
        int n = send(sock, p, left, 0);
        if (n == SOCKET_ERROR) return false;
        p += n;
        left -= n;
    }
    g_sentBytes += (long long)data.size();
    g_sentMsgs++;
    return true;
}

// 수신 전담 스레드. 상대가 보낸 메시지를 계속 받아서 처리.
// 이 스레드가 따로 있어서 내가 입력하는 중에도 상대 메시지 수신 가능
void tcpRecvLoop(SOCKET sock) {
    char buf[BUF_SIZE];
    string stream;  // TCP는 메시지 경계가 없어 개행이 나올 때까지 모아야 함

    while (g_running) {
        applyPauseIfRequested();

        int len = recv(sock, buf, BUF_SIZE, 0);

        if (len == 0) {  // 상대가 정상적으로 연결을 끊음
            safePrint("\n*** 상대가 연결을 종료했습니다. 엔터를 누르면 종료됩니다. ***\n");
            break;
        }
        if (len == SOCKET_ERROR) {
            if (g_running)  // 내가 끊은 게 아니면 진짜 오류
                safePrint("\n*** 수신 오류 (코드: " + to_string(WSAGetLastError()) +
                          ") 엔터를 누르면 종료됩니다. ***\n");
            break;
        }

        g_recvBytes += len;
        g_recvCalls++;   // 이 호출에서 몇 개의 메시지가 나오는지가 스트림의 증거
        stream.append(buf, len);

        // 버퍼에 쌓인 데이터에서 완성된 메시지(개행 단위)를 모두 꺼냄
        size_t pos;
        while ((pos = stream.find('\n')) != string::npos) {
            string msg = stream.substr(0, pos);
            stream.erase(0, pos + 1);
            if (!handleMessage(msg)) {
                g_running = false;
                return;
            }
        }
    }
    g_running = false;
}

// 연결 성립 후의 공통 채팅 루프. 서버와 클라이언트가 동일하게 사용
void tcpChat(SOCKET sock, const string& nick) {
    g_proto = "TCP";
    printSocketInfo(sock, "TCP");
    printHelp();
    safePrint("\n채팅을 시작합니다. 메시지를 입력하세요.\n\n");

    thread receiver(tcpRecvLoop, sock);  // 수신은 별도 스레드가 담당

    string line;
    while (g_running) {
        if (!getline(cin, line)) break;  // 입력이 끊기면 종료
        if (!g_running) break;           // 상대가 먼저 나간 경우
        if (line.empty()) continue;

        if (line == "/exit") {
            sendAllTcp(sock, encode("BYE", nick, "") + "\n");
            safePrint("채팅을 종료합니다.\n");
            break;
        }
        if (line == "/info")  { printSocketInfo(sock, "TCP"); continue; }
        if (line == "/stats") { printStats(); continue; }
        if (line == "/report") { printTestReport(); continue; }
        if (line == "/help")  { printHelp(); continue; }
        if (line.rfind("/pause", 0) == 0) {
            g_pauseSec = (int)parseArg(line, 5);
            safePrint("[시험] 다음 수신부터 " + to_string(g_pauseSec.load()) +
                      "초간 멈춥니다.\n");
            continue;
        }
        if (line.rfind("/flood", 0) == 0) {
            long long n = parseArg(line, 10000);
            runFlood(nick, n, [&](const string& s) {
                return sendAllTcp(sock, s + "\n");
            });
            continue;
        }

        if (!sendAllTcp(sock, encode("MSG", nick, line) + "\n")) {
            safePrint("*** 전송 실패. 연결이 끊어졌습니다. ***\n");
            break;
        }
    }

    g_running = false;
    shutdown(sock, SD_BOTH);  // 수신 스레드의 recv를 깨워서 빠져나오게 함
    closesocket(sock);
    if (receiver.joinable()) receiver.join();
    printStats();
}

// TCP 서버: socket -> bind -> listen -> accept -> 채팅
void runTcpServer() {
    unsigned short port = inputPort();
    string ip = inputIP(true);
    sockaddr_in serverAddr = makeAddr(ip, true, port);
    string nick = inputNick();

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET) die("socket() 실패");

    // 서버를 껐다 켤 때 "Address already in use" 방지용 옵션
    int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    if (::bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        die("bind() 실패 - 포트가 이미 사용 중일 수 있습니다");

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR)
        die("listen() 실패");

    cout << "\n[TCP 서버] 포트 " << port << " 에서 클라이언트를 기다립니다...\n";

    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSock == INVALID_SOCKET) die("accept() 실패");

    cout << "[TCP 서버] 접속됨: " << addrToString(clientAddr) << "\n";
    closesocket(listenSock);  // 1:1 채팅이라 더 이상 새 연결을 받지 않음

    shrinkRecvBuffer(clientSock);  // UDP와 같은 조건으로 맞춤
    tcpChat(clientSock, nick);
}

// TCP 클라이언트: socket -> connect -> 채팅
void runTcpClient() {
    unsigned short port = inputPort();
    string ip = inputIP(false);
    sockaddr_in serverAddr = makeAddr(ip, false, port);
    string nick = inputNick();

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) die("socket() 실패");

    cout << "\n[TCP 클라이언트] " << addrToString(serverAddr) << " 에 접속 중...\n";
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        die("connect() 실패 - 서버가 실행 중인지, IP와 포트가 맞는지 확인하세요");

    cout << "[TCP 클라이언트] 연결 성공\n";
    shrinkRecvBuffer(sock);
    tcpChat(sock, nick);
}

// =============================================================== UDP 채팅

// UDP는 연결이 없어서 상대가 누구인지를 소켓이 기억해 주지 않음.
// 그래서 보낼 주소를 프로그램이 직접 들고 있어야 함
struct UdpPeer {
    sockaddr_in addr;
    bool known;   // 서버는 첫 데이터그램을 받아야 상대 주소를 알 수 있음
    mutex mtx;
    UdpPeer() : known(false) { ZeroMemory(&addr, sizeof(addr)); }
};

// 수신 전담 스레드. 받은 데이터그램의 출발지 주소를 상대 주소로 기억
void udpRecvLoop(SOCKET sock, UdpPeer* peer) {
    char buf[BUF_SIZE];
    sockaddr_in from;
    int fromLen;

    while (g_running) {
        applyPauseIfRequested();

        fromLen = sizeof(from);
        int len = recvfrom(sock, buf, BUF_SIZE - 1, 0, (sockaddr*)&from, &fromLen);

        if (len == SOCKET_ERROR) {
            if (g_running)
                safePrint("\n*** 수신 오류 (코드: " + to_string(WSAGetLastError()) +
                          ") 엔터를 누르면 종료됩니다. ***\n");
            break;
        }

        g_recvBytes += len;
        g_recvCalls++;   // UDP는 이 값이 메시지 수와 항상 1:1로 일치함
        buf[len] = '\0';

        // 상대 주소를 아직 몰랐다면 여기서 알게 됨 (서버 쪽 경로)
        {
            lock_guard<mutex> lock(peer->mtx);
            if (!peer->known) {
                peer->addr = from;
                peer->known = true;
                safePrint("*** 상대 확인됨: " + addrToString(from) + " ***\n");
            }
        }

        // UDP는 데이터그램 경계가 보존되므로 받은 것이 곧 한 메시지
        if (!handleMessage(string(buf, len))) {
            g_running = false;
            return;
        }
    }
    g_running = false;
}

// 상대 주소가 정해져 있으면 데이터그램 전송
bool udpSend(SOCKET sock, UdpPeer* peer, const string& data) {
    sockaddr_in target;
    {
        lock_guard<mutex> lock(peer->mtx);
        if (!peer->known) {
            safePrint("*** 아직 상대를 모릅니다. 상대가 먼저 메시지를 보내야 합니다. ***\n");
            return true;  // 오류는 아니므로 채팅은 계속 진행
        }
        target = peer->addr;
    }

    int n = sendto(sock, data.c_str(), (int)data.size(), 0,
                   (sockaddr*)&target, sizeof(target));
    if (n == SOCKET_ERROR) return false;

    g_sentBytes += n;
    g_sentMsgs++;
    return true;
}

// UDP 채팅 공통 루프
void udpChat(SOCKET sock, UdpPeer* peer, const string& nick) {
    g_proto = "UDP";
    printSocketInfo(sock, "UDP");
    printHelp();
    safePrint("\n채팅을 시작합니다. 메시지를 입력하세요.\n\n");

    thread receiver(udpRecvLoop, sock, peer);

    string line;
    while (g_running) {
        if (!getline(cin, line)) break;
        if (!g_running) break;
        if (line.empty()) continue;

        if (line == "/exit") {
            udpSend(sock, peer, encode("BYE", nick, ""));
            safePrint("채팅을 종료합니다.\n");
            break;
        }
        if (line == "/info")  { printSocketInfo(sock, "UDP"); continue; }
        if (line == "/stats") { printStats(); continue; }
        if (line == "/report") { printTestReport(); continue; }
        if (line == "/help")  { printHelp(); continue; }
        if (line.rfind("/pause", 0) == 0) {
            g_pauseSec = (int)parseArg(line, 5);
            safePrint("[시험] 다음 수신부터 " + to_string(g_pauseSec.load()) +
                      "초간 멈춥니다.\n");
            continue;
        }
        if (line.rfind("/flood", 0) == 0) {
            long long n = parseArg(line, 10000);
            runFlood(nick, n, [&](const string& s) {
                return udpSend(sock, peer, s);
            });
            continue;
        }

        if (!udpSend(sock, peer, encode("MSG", nick, line))) {
            safePrint("*** 전송 실패 (코드: " + to_string(WSAGetLastError()) + ") ***\n");
            break;
        }
    }

    g_running = false;
    closesocket(sock);  // recvfrom을 깨워서 수신 스레드 종료시킴
    if (receiver.joinable()) receiver.join();
    printStats();
}

// UDP 서버: socket -> bind -> 채팅 (listen, accept 없음)
void runUdpServer() {
    unsigned short port = inputPort();
    string ip = inputIP(true);
    sockaddr_in serverAddr = makeAddr(ip, true, port);
    string nick = inputNick();

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) die("socket() 실패");

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    shrinkRecvBuffer(sock);  // TCP와 같은 조건으로 맞춤

    if (::bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        die("bind() 실패 - 포트가 이미 사용 중일 수 있습니다");

    cout << "\n[UDP 서버] 포트 " << port << " 에서 데이터그램을 기다립니다.\n";
    cout << "[UDP 서버] 상대가 먼저 메시지를 보내야 주소를 알 수 있습니다.\n";

    UdpPeer peer;  // 상대 주소는 첫 수신 때 채워짐
    udpChat(sock, &peer, nick);
}

// UDP 클라이언트: socket -> sendto/recvfrom (connect 없음)
void runUdpClient() {
    unsigned short port = inputPort();
    string ip = inputIP(false);
    sockaddr_in serverAddr = makeAddr(ip, false, port);
    string nick = inputNick();

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) die("socket() 실패");

    // UDP 클라이언트도 반드시 bind 필요.
    // TCP는 connect()가 로컬 주소를 자동으로 잡아 주지만, UDP는 connect가 없어
    // bind 전에는 소켓에 로컬 포트가 없음. 이 상태로 recvfrom을 부르면
    // WSAEINVAL(10022) 오류 발생.
    // 포트 번호에 0을 주면 OS가 비어 있는 포트를 골라 줌(ephemeral port)
    sockaddr_in localAddr;
    ZeroMemory(&localAddr, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);
    if (::bind(sock, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR)
        die("bind() 실패 - 클라이언트 임시 포트 할당 실패");

    shrinkRecvBuffer(sock);

    cout << "\n[UDP 클라이언트] 전송 대상: " << addrToString(serverAddr) << "\n";

    UdpPeer peer;  // 클라이언트는 상대 주소를 처음부터 알고 있음
    peer.addr = serverAddr;
    peer.known = true;

    udpChat(sock, &peer, nick);
}

// =================================================================== main
int main() {
    // 소스 파일은 UTF-8 저장인데 Windows 콘솔 기본 코드페이지는 949(CP949)라
    // 그대로 출력하면 한글이 깨짐. 콘솔 입출력 코드페이지를 UTF-8(65001)로
    // 맞추면 한글 출력과 한글 입력 모두 정상 동작
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Winsock 2.2 초기화. Windows 소켓 프로그램의 필수 시작 단계
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "[오류] WSAStartup() 실패\n";
        return 1;
    }

    cout << "===== 소켓 채팅 프로그램 =====\n\n";
    cout << "1. TCP 서버\n";
    cout << "2. TCP 클라이언트\n";
    cout << "3. UDP 서버\n";
    cout << "4. UDP 클라이언트\n";
    cout << "선택> ";

    string sel;
    getline(cin, sel);
    cout << "\n";

    if (sel == "1")      runTcpServer();
    else if (sel == "2") runTcpClient();
    else if (sel == "3") runUdpServer();
    else if (sel == "4") runUdpClient();
    else {
        cout << "[오류] 1~4 중에서 선택하세요.\n";
        WSACleanup();
        return 1;
    }

    // 사용한 Winsock 리소스 해제
    WSACleanup();
    cout << "\n프로그램을 종료합니다.\n";
    return 0;
}
