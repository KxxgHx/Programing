#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll X, Y;
    cin >> X >> Y;
    ll Z = (Y * 100 / X);

    if(Z >= 99)
    {
        cout << -1;
        return 0;
    }
    
    int low = 0;
    int high = 1e9;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int temp = (Y + mid) * 100 / (X + mid);

        if (Z < temp)
            high = mid - 1;
        else
            low = mid + 1;
    }

    cout << low;
}