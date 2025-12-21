#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, C;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> C;

    vector<int> v(N);

    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int low = 1;
    int high = v[N - 1] - v[0];
    int result = 0;
    while (low <= high)
    {
        int search = 1;
        int mid = (low + high) / 2;
        int aa = v[0];
        for (int i = 1; i < N; i++)
        {
            if (v[i] - aa >= mid)
            {
                search++;
                aa = v[i];
            }
        }
        if (search >= C)
        {
            result = max(result, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    cout << result;
}