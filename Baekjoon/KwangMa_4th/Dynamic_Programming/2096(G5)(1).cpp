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
    vector<vector<int>> max_vec(2, vector<int>(3, 0));
    vector<vector<int>> min_vec(2, vector<int>(3, 0));
    int x = 0;

    cin >> N;
    int a, b, c;

    for (int i = 0; i < N; i++)
    {
        cin >> a >> b >> c;
        max_vec[x][0] = max(max_vec[1 - x][0], max_vec[1 - x][1]) + a;
        max_vec[x][1] = max(max_vec[1 - x][0], max(max_vec[1 - x][1], max_vec[1 - x][2])) + b;
        max_vec[x][2] = max(max_vec[1 - x][1], max_vec[1 - x][2]) + c;
        min_vec[x][0] = min(min_vec[1 - x][0], min_vec[1 - x][1]) + a;
        min_vec[x][1] = min(min_vec[1 - x][0], min(min_vec[1 - x][1], min_vec[1 - x][2])) + b;
        min_vec[x][2] = min(min_vec[1 - x][1], min_vec[1 - x][2]) + c;
        x = 1 - x;
    }
    int maximum = max(max_vec[1 - x][0], max(max_vec[1 - x][1], max_vec[1 - x][2]));
    int minimum = min(min_vec[1 - x][0], min(min_vec[1 - x][1], min_vec[1 - x][2]));

    cout << maximum << ' ' << minimum;
}