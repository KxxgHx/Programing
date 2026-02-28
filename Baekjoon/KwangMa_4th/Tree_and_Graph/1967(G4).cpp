#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> pp;

vector<pp> node[10001];
bool visited[10001];
int result = 0;
int leaf = 0;

void dfs(int i, int len)
{
    if (visited[i])
        return;

    visited[i] = true;
    if (result < len)
    {
        result = len;
        leaf = i;
    }

    for (int j = 0; j < node[i].size(); j++)
        dfs(node[i][j].first, len + node[i][j].second);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        node[a].push_back({b, c});
        node[b].push_back({a, c});
    }

    dfs(1, 0);

    result = 0;
    fill(visited, visited + 10001, false);

    dfs(leaf, 0);
    cout << result;
}