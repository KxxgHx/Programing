#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> vec[2000];
vector<bool> visited;

bool result = false;

void dfs(int cur, int cnt)
{
    if (result) return; 

    if(cnt == 4)
    {
        result = true;
        return;
    }

    visited[cur] = true;

    
    for (int i = 0; i < vec[cur].size(); i++)
    {
        int next_node = vec[cur][i];
        
        if(!visited[next_node])
        {
            dfs(next_node, cnt + 1);
        }
    }
    
    visited[cur] = false; 
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    visited.resize(N, false);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    for (int i = 0; i < N; i++)
    {
        if(result) break; 

        dfs(i, 0);
    }

    if(result)
        cout << 1;
    else
        cout << 0;
}