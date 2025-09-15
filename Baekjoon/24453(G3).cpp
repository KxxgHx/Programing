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
    
    // 특수 케이스
    if (N == 1) {
        cout << max(0, M - Y);
        return 0;
    }
    
    int ans = 1e9;
    int left = 1;
    int right = 1;
    int error_count = 0; 
    

    while (right <= N) {
        //오른쪽 포인터가 가리키는 줄 확인
        if (err[right]) {
            error_count++; 
        }
        
        //현재 윈도우가 조건을 만족하는지 확인하고 최적화
        // 조건: 길이 >= X이면서 오류 개수 >= Y
        while (left <= right && right - left + 1 >= X && error_count >= Y)
        {
            //최소 오류 개수 갱신
            ans = min(ans, error_count);
            
            // 왼쪽 포인터를 오른쪽으로 이동하여 더 작은 구간 탐색
            if (err[left]) {
                error_count--;  // 제거되는 줄에 오류가 있었다면 오류 개수 감소
            }
            left++;
        }

        //오른쪽 포인터를 다음 줄로 이동
        right++;
    }
    
    if (ans == 1e9) 
    {
        cout << 0; 
    }
    else 
    {
        cout << M - ans;
    }
    
    return 0;
}