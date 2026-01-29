#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> pp;

int V;

vector<pp> tree[100001];
bool visited[100001];
int max_dist;
int max_node;

void dfs(int i, int dist)
{
    if(visited[i])
        return;

    if (max_dist < dist)
    {
        max_dist = dist;
        max_node = i;
    }
    visited[i] = true;

    for (int j = 0; j < tree[i].size(); j++)
    {
        int next_i = tree[i][j].first;
        int next_dist = tree[i][j].second;
        dfs(next_i, next_dist + dist);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> V;

    for (int i = 0; i < V; i++)
    {
        int num, a, b;
        cin >> num;
        cin >> a;
        while (a != -1)
        {
            cin >> b;
            tree[num].push_back({a, b});
            tree[a].push_back({num, b});
            cin >> a;
        }
    }
    dfs(1, 0);
    memset(visited, false, sizeof(visited));

    max_dist = 0;
    dfs(max_node, 0);
    cout << max_dist;
}