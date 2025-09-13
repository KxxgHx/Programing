#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;
    vector<int> vec(N);
    for (int i = 0; i < N; i++)
    {
        cin >> vec[i];
    }
    int left = 0, right = 0;
    int cnt = 0;
    int minimum = 1e9;

    while(left<=right&&right<N)
    {
        if(vec[right] == 1)
            cnt++;
        right++;
        while(cnt>=K)
        {
            minimum = min(minimum, right - left);
            if(vec[left] == 1)
                cnt--;
            left++;
        }
    }
    if(minimum == 1e9)
        cout << -1;
    else
        cout << minimum;
}