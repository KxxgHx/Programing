@echo off
REM ===========================================================================
REM  컴퓨터네트워크 과제 - 소켓 채팅 프로그램 실행 스크립트
REM
REM  하는 일
REM    1. Socket.cpp 를 빌드
REM    2. 서버 창과 클라이언트 창을 자동으로 하나씩 띄움
REM
REM  사용법: 탐색기에서 run.bat 더블클릭, 또는 콘솔에서 run.bat 입력
REM ===========================================================================

REM 이 배치 파일이 있는 폴더로 이동 (더블클릭으로 실행해도 경로가 맞도록)
cd /d "%~dp0"

echo.
echo  ==========================================
echo    소켓 채팅 프로그램 실행 스크립트
echo  ==========================================
echo.

REM --------------------------------------------------------------- 1. 빌드
echo  [1/2] 빌드 중...

where g++ >nul 2>nul
if errorlevel 1 (
    echo.
    echo  [오류] g++ 를 찾을 수 없습니다.
    echo         MSYS2/MinGW 설치 후 PATH 에 추가했는지 확인하세요.
    echo.
    pause
    exit /b 1
)

g++ -o socket.exe Socket.cpp -lws2_32
if errorlevel 1 (
    echo.
    echo  [오류] 빌드 실패. 위 컴파일 오류 메시지를 확인하세요.
    echo.
    pause
    exit /b 1
)

echo        빌드 완료: socket.exe
echo.

REM ------------------------------------------------------- 2. 창 두 개 실행
echo  [2/2] 서버 창과 클라이언트 창을 띄웁니다.
echo.
echo   -----------------------------------------------------------
echo    실행 순서
echo      1) 서버 창에서 먼저 설정    : 1(TCP) 또는 3(UDP) 선택
echo      2) 그다음 클라이언트 창 설정 : 2(TCP) 또는 4(UDP) 선택
echo      3) 양쪽 포트 번호는 반드시 동일하게 입력
echo      4) IP 는 그냥 엔터를 치면 기본값 사용
echo.
echo    채팅 중 사용 가능한 명령
echo      /info   소켓의 실제 주소 확인    /stats  송수신 통계
echo      /help   도움말                   /exit   종료
echo   -----------------------------------------------------------
echo.

REM cmd /k 로 띄워야 프로그램 종료 후에도 창이 남아 결과를 확인 가능
start "서버 (Server)" cmd /k socket.exe

REM 서버가 먼저 대기 상태에 들어가도록 잠깐 기다림
timeout /t 1 /nobreak >nul

start "클라이언트 (Client)" cmd /k socket.exe

echo  두 창을 띄웠습니다. 이 창은 닫으셔도 됩니다.
echo.
pause
