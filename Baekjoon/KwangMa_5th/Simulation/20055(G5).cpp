#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, cnt, result;
vector<int> belt;
vector<bool> isVisit;

// 벨트와 로봇이 실제로 한 칸씩 회전
void reverse_Belt() {
    // 벨트 내구도 회전
    int last_belt = belt.back();
    belt.pop_back();
    belt.insert(belt.begin(), last_belt);

    // 로봇 위치 회전
    bool last_robot = isVisit.back();
    isVisit.pop_back();
    isVisit.insert(isVisit.begin(), last_robot);

    // 회전 후 내리는 위치에 로봇이 있다면 즉시 제거
    isVisit[N - 1] = false;
}

// 로봇이 스스로 한 칸 이동
void move_Robot() {
    for (int i = N - 2; i >= 0; i--) {
        if (isVisit[i]) {
            // 다음 칸에 로봇이 없고 내구도가 1 이상이면 이동
            if (!isVisit[i + 1] && belt[i + 1] >= 1) {
                isVisit[i] = false;
                belt[i + 1]--;
                if (belt[i + 1] == 0) cnt++;

                // 이동한 칸이 내리는 위치가 아니면 로봇 표시
                if (i + 1 != N - 1) {
                    isVisit[i + 1] = true;
                }
                // 내리는 위치라면 isVisit[i+1]은 false 상태 유지 (내림 처리)
            }
        }
    }
}

//올리는 위치에 로봇 올리기
void initial_Robot() {
    if (!isVisit[0] && belt[0] >= 1) {
        isVisit[0] = true;
        belt[0]--;
        if (belt[0] == 0) cnt++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < 2 * N; i++) {
        int temp;
        cin >> temp;
        belt.push_back(temp);
        isVisit.push_back(false);
    }

    while (cnt < K) {
        result++;
        
        reverse_Belt();
        move_Robot();
        initial_Robot();
    }

    cout << result << '\n';

    return 0;
}