#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, M;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    sort(A.begin(), A.end()); //Binary Search를 하기 위한 정렬 필수!!

    cin >> M;
    for (int i = 0; i < M; i++)
    {
        int target; //M개의 존재여부 숫자 판별
        cin >> target;
        int low = 0;
        int high = N - 1;
        bool find = false;  //target 존재 시 true, 없으면 false

        while (low <= high) //low>high은 논리적으로 불가능.(투포인터 진행했을 때 학습한 내용과 유사)
        {
            int mid = low + (high - low) / 2;   //중앙 값 설정

            if(A[mid] == target)
            {
                find = true;
                break;
            }
            else if(A[mid] < target)    //target>중앙값이므로 low값을 중앙값보다 1 크게 설정하고 loop 돌기
                low = mid + 1;
            else    //target<중앙값이므로 high값을 중앙값보다 1 작게 설정하고 loop 돌기
                high = mid - 1;
        }
        if(find)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
        
    }
    
}