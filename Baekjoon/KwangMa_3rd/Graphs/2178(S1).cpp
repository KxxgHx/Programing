#include <iostream>
#include <queue>

using namespace std;
int visited[101][101];
int N, M, result;
string input[101];
int mvx[4] = {1, 0, -1, 0};
int mvy[4] = {0, 1, 0, -1};
typedef pair<int, int> pp;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> input[i];
    }
    queue<pp> q;
    visited[0][0] = 1;
    q.push({0, 0});

    while(!q.empty())
    {
        pp cur = q.front();
        q.pop();
        if (cur.second == (N - 1) && cur.first == (M - 1))
            break;
        for (int i = 0; i < 4; i++)
        {
            pp next = {cur.first + mvx[i], cur.second + mvy[i]};
            if (next.first >= M || next.second >= N || next.first < 0 || next.second < 0)
                continue;
            if(visited[next.second][next.first])
                continue;
            if(input[next.second][next.first] == '0')
                continue;
            visited[next.second][next.first] = visited[cur.second][cur.first] + 1;
            q.push(next);
        }
    }

    cout << visited[N - 1][M - 1] << '\n';
}