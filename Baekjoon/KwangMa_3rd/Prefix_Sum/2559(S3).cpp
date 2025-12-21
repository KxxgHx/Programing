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
    cin >> N >> K;
    vector<int> vec(N + 1);

    for (int i = 1; i <= N; i++)
    {
        int input;
        cin >> input;
        vec[i] = vec[i - 1] + input;
    }

    int maximum = -100000000;

    for (int i = K; i <= N; i++)
    {
        maximum = max(maximum, vec[i] - vec[i - K]);
    }
    cout << maximum;
}