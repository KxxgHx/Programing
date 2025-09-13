#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, K;
    int minimum = 1e9;
    cin >> N >> K;
    vector<int> vec;

    for (int i = 1; i <= N; i++)
    {
        int a;
        cin >> a;
        if(a == 1)
        {
            vec.push_back(i);
        }
    }
    if(vec.size()<K)
    {
        cout << -1;
        return 0;
    }
    for (int i = 0; i <= vec.size() - K; i++)
    {
        minimum = min(minimum, vec[i + K - 1] - vec[i] + 1);
    }
    cout << minimum;
}