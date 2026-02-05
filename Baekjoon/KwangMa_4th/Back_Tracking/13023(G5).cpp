#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> vec[2001];
vector<bool> visited;

bool result = false;

void dfs(int cur, int cnt)
{
    if(cnt == M)
    {
        result = true;
        return;
    }
    visited[cur] = true;
    for (int i = 0; i < vec[cnt].size(); i++)
    {
        int next_node = vec[cnt][i];
        if(visited[next_node])
            continue;
        dfs(next_node, cnt + 1);

        visited[next_node] = false;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    visited.resize(M + 1, false);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    for (int i = 0; i < N; i++)
    {
        if(visited[i] == false)
        {
            dfs(i, 0);
            visited[i] = false;
        }
    }

    if(result)
        cout << 1;
    else
        cout << 0;
}