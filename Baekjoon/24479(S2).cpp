#include <iostream>
#include <vector>

using namespace std;

int N, M, u, v;
vector<int> graph[100001];
bool visited[100001];

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
    int R;
    cin >> N >> M >> R;

    for (int i = 0; i < N; i++)
    {
        cin >> u >> v;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    dfs(1);
    for (int i = 1; i <= M; i++)
    {
        if(visited[i])
        {
            cout << i;
        }
        else
        {
            cout << 0;
            dfs(i);
        }
    }
}