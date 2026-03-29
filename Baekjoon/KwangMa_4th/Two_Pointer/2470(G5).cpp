#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

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

    ll minimum = 3e9;

    ll result_A = 0;
    ll result_B = 0;

    sort(vec.begin(), vec.end());

    while (low < high)
    {
        ll temp = vec[low] + vec[high];
        if (abs(temp) < abs(minimum))
        {
            minimum = temp;
            result_A = vec[low];
            result_B = vec[high];
        }

        if (temp < 0)
            low++;
        else
            high--;

    }

    if (result_A > result_B)
        cout << result_B << " " << result_A;
    else
        cout << result_A << " " << result_B;
}