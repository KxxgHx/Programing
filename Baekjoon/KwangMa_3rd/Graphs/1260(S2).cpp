#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> vec[1001];
bool visited[1001];
int N, M, V;

void dfs(int v)
{
    visited[v] = true;
    cout << v << " ";
    for (int next : vec[v])
    {
        if(!visited[next])
            dfs(next);
    }
}
void bfs(int v)
{
    queue<int> q;
    q.push(v);
    fill(visited, visited + N + 1, false);
    visited[v] = true;
    cout << v << " ";
    while(!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int next : vec[a])
        {
            if(!visited[next])
            {
                visited[next] = true;
                cout << next << " ";
                q.push(next);
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> V;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for (int i = 1; i <= N; i++)
        sort(vec[i].begin(), vec[i].end());

    dfs(V);
    cout << '\n';
    bfs(V);
    cout << '\n';
}