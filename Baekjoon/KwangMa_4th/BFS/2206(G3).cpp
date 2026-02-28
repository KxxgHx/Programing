#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> pp;

int mvx[4] = {1, 0, -1, 0};
int mvy[4] = {0, 1, 0, -1};
int road_map[1001][1001][2];

int bfs(int n, int m)
{
    queue<pair<int, pp>> q;
    q.push({0, {0, 0}});

    while(!q.empty())
    {
        int crash_wall = q.front().first;
        int x = q.front().second.first;
        int y = q.front().second.second;
        q.pop();

        if (x == n - 1 && y == m - 1)
            return road_map[n - 1][m - 1][crash_wall] + 1;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + mvx[i];
            int ny = y + mvy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (road_map[nx][ny][0] == 1)
            {
                if(!crash_wall)
                {
                    road_map[nx][ny][crash_wall + 1] = road_map[x][y][crash_wall] + 1;
                    q.push({1, {nx, ny}});
                }
            }
            else if (road_map[nx][ny][0] == 0)
            {
                if (crash_wall == 1 && road_map[nx][ny][crash_wall])
                    continue;

                road_map[nx][ny][crash_wall] = road_map[x][y][crash_wall] + 1;
                q.push({crash_wall, {nx, ny}});
            }
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char ch;
            cin >> ch;
            road_map[i][j][0] = ch - '0';
        }
    }

    cout << bfs(N, M);

    return 0;
}