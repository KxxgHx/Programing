#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

vector<ll> vec;
int N, T, S, I, C;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> T;
    for (int i = 0; i < N; i++)
    {
        cin >> S >> I >> C;
        for (int j = 0; j < C; j++)
        {
            ll t = S + I * j;
            vec.push_back(t);
        }
    }

    sort(vec.begin(), vec.end());

    int low = 0;
    int high = vec.size();

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (vec[mid] >= T)
            high = mid;
        else
            low = mid + 1;
    }

    if (low == vec.size())
        cout << -1;
    else
        cout << vec[low] - T;
}