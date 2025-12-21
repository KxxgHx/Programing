#include <iostream>
#include <queue>

using namespace std;

bool arr[501][501];
typedef pair<int, int> pp;

int mvx[4] = {1, 0, -1, 0};
int mvy[4] = {0, 1, 0, -1};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    int picture_count = 0;
    int picture_width = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(!arr[i][j])
                continue;
            picture_count++;
            int compare = 1;
            queue<pp> q;
    
            q.push({j, i});
            arr[i][j] = 0;
            while(!q.empty())
            {
                pp cur = q.front();
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    pp next = {cur.first + mvx[i], cur.second + mvy[i]};
                    if (next.first >= m || next.second >= n || next.first < 0 || next.second < 0)
                        continue;
                    if(!arr[next.second][next.first])
                        continue;
                    
                    q.push(next);
                    arr[next.second][next.first] = 0;
                    compare++;
                }
            }
            picture_width = max(compare, picture_width);
        }
    }
    cout << picture_count << '\n'
         << picture_width;
}