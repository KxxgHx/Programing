#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> result;

    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;

        if (result.empty() || result.back() < a)
            result.push_back(a);
        
        else
        {
            int idx = lower_bound(result.begin(), result.end(), a) - result.begin();
            result[idx] = a;
        }
    }

    cout << result.size();
}