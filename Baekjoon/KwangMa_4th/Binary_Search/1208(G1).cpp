#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;

int N, S;
vector<int> vec;
ll result;
map<int, int> m;

void left(int num, int sum)
{
    if (num == N / 2)
    {
        m[sum]++;
        return;
    }
    left(num + 1, sum);
    left(num + 1, sum + vec[num]);
}

void right(int num, int sum)
{
    if(num == N)
    {
        result += m[S - sum];
        return;
    }
    right(num + 1, sum);
    right(num + 1, sum + vec[num]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> S;

    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        vec.push_back(a);
    }
    left(0, 0);
    right(N / 2, 0);

    if(S == 0)
        cout << result - 1;
    else
        cout << result;
    
    return 0;
}