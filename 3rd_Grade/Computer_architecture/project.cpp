#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// 레지스터 이름 -> 각 번호로 매핑하는 테이블
map<string, int> register_mapping = {
    {"$zero", 0}, {"$at", 1}, {"$v0", 2}, {"$v1", 3}, {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7}, 
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15}, 
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23}, 
    {"$t8", 24}, {"$t9", 25}, {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31}
};

// 정수 -> 이진수 문자열로 변환
string intToBinary(int n, int bits)
{
    string r = "";
    for (int i = bits - 1; i >= 0; i--)
    {
        if (n & (1 << i))
            r += '1';
        else
            r += '0';
    }
    return r;
}

// 어셈블리의 comma(,)를 제거하여 파싱할 수 있도록 구현
string clean(string s)
{
    s.erase(remove(s.begin(), s.end(), ','), s.end());
    size_t first = s.find_first_not_of(" \t\r\n");
    if(string::npos == first)
        return "";
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

int main(int argc, char* argv[]) {
    // 실행 시 인자 개수 확인
    if (argc != 3) {
        cerr << "사용법: " << argv[0] << " input.asm output.bin" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin)
    {
        cerr << "입력 파일을 열 수 없습니다." << endl;
        return 1;
    }

    vector<string> lines;
    map<string, int> LableAddress; // 레이블 주소 저장 공간
    string line;
    int address = 0; // 프로그램 주소는 0을 시작점으로 생각

    // 레이블 주소 확정, 유효 명령어 추출
    while(getline(fin, line))
    {
        if (address == 0 && line.length() >= 3) {
        if ((unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF) {
            line = line.substr(3);
        }
    }
        // 주석(#) 제거
        size_t commandPos = line.find('#');
        if(commandPos != string::npos)
            line = line.substr(0, commandPos);

        stringstream ss(line); 
        string first;
        if (!(ss >> first))
            continue;

        // 레이블인 경우 처리
        if(first.back() == ':') 
        {
            LableAddress[first.substr(0, first.size() - 1)] = address;
            string remain;
            // 레이블 뒤에 같은 줄에 명령어가 더 있는지 확인
            if (ss >> remain)
            {
                lines.push_back(line.substr(line.find(remain)));
                address += 4; // 1 instruction = 4byte의 size이기에 주소는 4byte씩 증가
            }
        }
        else // 일반 명령어인 경우
        {
            lines.push_back(line);
            address += 4;
        }
    }
    fin.close();

    ofstream fout(argv[2]);
    if (!fout) {
        cerr << "출력 파일을 열 수 없습니다." << endl;
        return 1;
    }

    int curAddress = 0;
    // 바이너리 코드로 변환, 파일 출력
    for (const string &l : lines)
    {
        stringstream ss(l);
        string op, t1, t2, t3;
        ss >> op;
        op = clean(op);
        if(op.empty())
            continue;
        string result = "";

        // R-format instruction (add, sub, and, or, xor, nor, slt)
        if (op == "add" || op == "sub" || op == "and" || op == "or" || op == "xor" || op == "nor" || op == "slt") {
            ss >> t1 >> t2 >> t3;
            int rd = register_mapping[clean(t1)];
            int rs = register_mapping[clean(t2)];
            int rt = register_mapping[clean(t3)];
            int funct = (op == "add") ? 0x20 : (op == "sub") ? 0x22 : (op == "and") ? 0x24 : 
                        (op == "or") ? 0x25 : (op == "xor") ? 0x26 : (op == "nor") ? 0x27 : 0x2A;
            result = "000000" + intToBinary(rs, 5) + intToBinary(rt, 5) + intToBinary(rd, 5) + "00000" + intToBinary(funct, 6);
        }
        // R-format shift instruction (sll, srl)
        else if (op == "sll" || op == "srl") {
            ss >> t1 >> t2 >> t3;
            int rd = register_mapping[clean(t1)];
            int rt = register_mapping[clean(t2)];
            int shamt = stoi(clean(t3));
            int funct = (op == "sll") ? 0x00 : 0x02;
            result = "00000000000" + intToBinary(rt, 5) + intToBinary(rd, 5) + intToBinary(shamt, 5) + intToBinary(funct, 6);
        }
        // I-format instruction (addi, andi, ori, xori, slti)
        else if (op == "addi" || op == "andi" || op == "ori" || op == "xori" || op == "slti") {
            ss >> t1 >> t2 >> t3;
            int rt = register_mapping[clean(t1)];
            int rs = register_mapping[clean(t2)];
            int imm = stoi(clean(t3));
            string opcode = (op == "addi") ? "001000" : (op == "andi") ? "001100" : 
                            (op == "ori") ? "001101" : (op == "xori") ? "001110" : "001010";
            result = opcode + intToBinary(rs, 5) + intToBinary(rt, 5) + intToBinary(imm, 16);
        }
        // I-format branch instruction (beq, bne)
        else if (op == "beq" || op == "bne") {
            ss >> t1 >> t2 >> t3;
            int rs = register_mapping[clean(t1)], rt = register_mapping[clean(t2)];
            // offset 계산: (목표주소 - (현재주소 + 4)) / 4
            int offset = (LableAddress[clean(t3)] - (curAddress + 4)) / 4; 
            string opcode = (op == "beq") ? "000100" : "000101";
            result = opcode + intToBinary(rs, 5) + intToBinary(rt, 5) + intToBinary(offset, 16);
        }
        // I-format Load/Store instruction (lw, sw) 
        else if (op == "lw" || op == "sw") {
            ss >> t1 >> t2;
            int rt = register_mapping[clean(t1)];
            int imm = stoi(t2.substr(0, t2.find('(')));
            int rs = register_mapping[clean(t2.substr(t2.find('(') + 1, t2.find(')') - t2.find('(') - 1))];
            string opcode = (op == "lw") ? "100011" : "101011";
            result = opcode + intToBinary(rs, 5) + intToBinary(rt, 5) + intToBinary(imm, 16);
        }
        // J-format instruction (j, jal)
        else if (op == "j" || op == "jal") {
            ss >> t1;
            int target = LableAddress[clean(t1)] / 4; // 점프 시 절대 주소 계산
            string opcode = (op == "j") ? "000010" : "000011";
            result = opcode + intToBinary(target, 26);
        }
        // 특수 목적 명령어 처리 (jr, lui)
        else if (op == "jr") {
            ss >> t1;
            result = "000000" + intToBinary(register_mapping[clean(t1)], 5) + "000000000000000001000";
        }
        else if (op == "lui") {
            ss >> t1 >> t2;
            result = "00111100000" + intToBinary(register_mapping[clean(t1)], 5) + intToBinary(stoi(clean(t2)), 16);
        }

        // 변환된 바이너리 문자열 파일 출력
        if(!result.empty())
            fout << result << endl;
            
        curAddress += 4;
    }

    fout.close();
    return 0;
}