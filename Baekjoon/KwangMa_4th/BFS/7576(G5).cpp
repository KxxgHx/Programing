#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pp;

int mvx[4] = {1, 0, -1, 0};
int mvy[4] = {0, 1, 0, -1};

int M, N;
int result = 0;

int box[1001][1001];
queue<pp> q;

void bfs()
{
    while(!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + mvx[i];
            int ny = y + mvy[i];

            if(nx < 0 || ny < 0 || nx >= M || ny >= N)
                continue;

            if(box[ny][nx] == 0)
            {
                box[ny][nx] = box[y][x] + 1;
                q.push({ny, nx});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> M >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> box[i][j];
            if(box[i][j] == 1)
                q.push({i, j});
        }
    }

    bfs();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if(box[i][j] == 0)
            {
                cout << -1;
                return 0;
            }
            result = max(result, box[i][j]);
        }
    }

    cout << result - 1; //처음부터 있는 것이 0일이기에 1 빼고 출력
}
