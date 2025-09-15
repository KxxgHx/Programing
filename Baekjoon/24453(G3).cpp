#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, M;
    cin >> N >> M;
    
    vector<bool> err(N + 1, false);
    
    for (int i = 0; i < M; i++) {
        int a;
        cin >> a;
        err[a] = true;
    }
    
    int X, Y;
    cin >> X >> Y;
    
    // 특수 케이스: N이 1인 경우
    if (N == 1) {
        cout << max(0, M - Y);
        return 0;
    }
    
    int ans = 1e9;
    int left = 1;
    int right = 1;
    int error_count = 0;
    
    // 투 포인터 알고리즘
    while (right <= N) {
        // 오른쪽 포인터 확장
        if (err[right]) {
            error_count++;
        }
        
        // 현재 구간이 최소 길이 X 이상이고 오류 개수가 Y 이상인 경우
        while (right - left + 1 >= X && error_count >= Y) {
            ans = min(ans, error_count);
            
            // 왼쪽 포인터 이동
            if (err[left]) {
                error_count--;
            }
            left++;
        }
        
        right++;
    }
    
    // 결과 출력
    if (ans == 1e9) {
        cout << 0;
    } else {
        cout << M - ans;
    }
    
    return 0;
}