#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    vector<vector<int>> max_vec(2, vector<int>(3, 0));
    vector<vector<int>> min_vec(2, vector<int>(3, 0));
    int x, y, z;
    int k = 0;

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> x >> y >> z;
        max_vec[k][0] = max(max_vec[1 - k][0], max_vec[1 - k][1]) + x;
        max_vec[k][1] = max(max(max_vec[1 - k][0], max_vec[1 - k][1]), max_vec[1 - k][2]) + y;
        max_vec[k][2] = max(max_vec[1 - k][1], max_vec[1 - k][2]) + z;
        min_vec[k][0] = min(min_vec[1 - k][0], min_vec[1 - k][1]) + x;
        min_vec[k][1] = min(min(min_vec[1 - k][0], min_vec[1 - k][1]), min_vec[1 - k][2]) + y;
        min_vec[k][2] = min(min_vec[1 - k][1], min_vec[1 - k][2]) + z;
        k = 1 - k;
    }
    int minimum = min(min(min_vec[1 - k][0], min_vec[1 - k][1]), min_vec[1 - k][2]);
    int maximum = max(max(max_vec[1 - k][0], max_vec[1 - k][1]), max_vec[1 - k][2]);

    cout << maximum << ' ' << minimum;
}
    
