#include <iostream>
#include <queue>

using namespace std;
typedef pair<int, int> pp;

int N, K;
bool visited[100001];

int bfs()
{
    priority_queue<pp, vector<pp>, greater<pp>> q;
    q.push({0, N});
    visited[N] = true;
    while(!q.empty())
    {
        int time = q.top().first;
        int X = q.top().second;
        q.pop();

        if(X == K)
            return time;

        if (X * 2 < 100001 && !visited[X * 2]) // 순간이동
        {
            q.push({time, X * 2});
            visited[X * 2] = true;
        }
        if (X + 1 < 100001 && !visited[X + 1])
        {
            q.push({time + 1, X + 1});
            visited[X + 1] = true;
        }
        if (X - 1 >= 0 && !visited[X - 1])
        {
            q.push({time + 1, X - 1});
            visited[X - 1] = true; 
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    cout << bfs();

    return 0;
}