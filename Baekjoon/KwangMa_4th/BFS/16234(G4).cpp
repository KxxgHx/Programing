#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

typedef pair<int, int> pp;

int mvx[4] = {1, 0, -1, 0};
int mvy[4] = {0, 1, 0, -1};

int N, L, R;
int A[51][51];
bool visited[51][51];

bool bfs(int x, int y)
{
    queue<pp> q;
    vector<pp> country;

    q.push({x, y});
    visited[x][y] = true;
    country.push_back({x, y});

    int sum = A[x][y];

    while (!q.empty())
    {
        pp cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = cur.first + mvx[i];
            int ny = cur.second + mvy[i];

            if (nx < 0 || ny < 0 || nx >= N || ny >= N)
                continue;

            if (visited[nx][ny])
                continue;

            int diff = abs(A[cur.first][cur.second] - A[nx][ny]);

            if (diff >= L && diff <= R)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                country.push_back({nx, ny});
                sum += A[nx][ny];
            }
        }
    }

    if (country.size() > 1)
    {
        int avg = sum / country.size();
        for (pp p : country)
        {
            A[p.first][p.second] = avg;
        }
        return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L >> R;

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            cin >> A[r][c];

    int days = 0;

    while (true)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                visited[i][j] = false;

        bool moved = false;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (!visited[i][j])
                {
                    if (bfs(i, j))
                        moved = true;
                }
            }
        }

        if (!moved)
            break;

        days++;
    }

    cout << days;
}
