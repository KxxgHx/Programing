#include <iostream>
#include <vector>

using namespace std;

int N, M, u, v;
int cnt = 1;
vector<int> graph[1001];
bool visited[1001];

void dfs(int current){
    visited[current] = true;
    for(int next:graph[current]){
        if(!visited[next])
            dfs(next);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);

    for (int i = 1; i <= N; i++)
    {
        if(!visited[i])
        {
            cnt++;
            dfs(i);
        }
    }
    cout << cnt;
}