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
    vector<int> ice(1000001);
    int maxXi = 0;
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        int Gi, Xi;
        cin >> Gi >> Xi;
        ice[Xi] = Gi;
        if (Xi > maxXi)
        {
            maxXi = Xi;
        }
    }
    for (int i = 0; i < 2 * K; i++)
    {
        sum += ice[i];
    }
    int result = 0;
    result = sum;
    int left = 0;
    for (int right = 2 * K + 1; right <= maxXi; right++)
    {
        sum += ice[right];
        sum -= ice[left];
        result = max(result, sum);
        left++;
    }
    cout << result;
}
