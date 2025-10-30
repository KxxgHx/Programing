#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, R;
vector<int> graph[100001];
int visited[100001];
int order_count = 0;

void dfs(int current){
    visited[current] = ++order_count;
    
    for(int next : graph[current]){
        if(!visited[next])
            dfs(next);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N >> M >> R;

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    for (int i = 1; i <= N; i++)
    {
        sort(graph[i].begin(), graph[i].end());
    }
    
    dfs(R);
    
    for (int i = 1; i <= N; i++)
    {
        cout << visited[i] << '\n';
    }
    
    return 0;
}