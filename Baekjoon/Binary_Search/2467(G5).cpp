#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

int N;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    vector<ll> vec(N);

    for (int i = 0; i < N; i++)
        cin >> vec[i];

    ll low = 0;
    ll high = N - 1;

    ll minimum = abs(vec[low] + vec[high]);

    ll result_A = vec[low];
    ll result_B = vec[high];

    while (low < high)
    {
        ll temp = vec[low] + vec[high];
        if (abs(temp) < minimum)
        {
            minimum = abs(temp);
            result_A = vec[low];
            result_B = vec[high];
        }

        if (temp < 0)
            low++;
        else
            high--;

    }

    cout << result_A << " " << result_B;
}