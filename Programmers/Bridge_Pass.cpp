#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int solution(vector<int> stones, int k) 
{
    int low = 1;
    int high = 0;
    for (int s : stones) 
        high = max(high, s);
    
    int answer = 0;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // (low + high)/2에 비해 오버플로우 발생 가능성 줄어듦
        
        int not_linked = 0; // 연속으로 건널 수 없는 돌의 갯수
        bool crossed = true;
        for (int s : stones) {
            if (s < mid) // 건널 수 없는 경우
                not_linked++;
            else 
                not_linked = 0; // 건널 수 있으니 다시 초기화 후 연산
            
            if (not_linked >= k) // 연속 k개 이상 시 건널 수 없음 -> 사용 불가
            { 
                crossed = false; 
                break; 
            }
        }

        if (crossed) // mid 값이 건널 수 있음 -> 범위를 큰 사이즈로 시도
        {
            answer = mid;
            low = mid + 1;
        } 
        else // mid 값이 건널 수 없음 -> 범위를 작은 사이즈로 시도
        {
            high = mid - 1;
        }
    }
    
    return answer;
}

int main() //10 3               
//2 4 5 3 2 1 4 2 5 1
{
    int n, k;
    cin >> n >> k;
    vector<int> stones(n);

    for (int i = 0; i < n; i++) 
        cin >> stones[i];

    cout << solution(stones, k) << "\n";
}