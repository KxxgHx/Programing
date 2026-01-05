#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pp;
const int INF = 1e9;
int n, m, r, a, b, l;

vector<pp> graph[102];
int table[102];
int item[102];

int dijkstra(int num)
{
    for (int i = 1; i <= n; i++)
        table[i] = INF;
    priority_queue<pp, vector<pp>, greater<pp>> pq;
    pq.push({0, num});
    table[num] = 0;

    while (!pq.empty())
    {
        int now_cost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (table[now] < now_cost)
            continue;

        for (int i = 0; i < graph[now].size(); i++)
        {
            int next_node = graph[now][i].first;
            int cost = now_cost + graph[now][i].second;

            if (cost < table[next_node])
            {
                table[next_node] = cost;
                pq.push({cost, next_node});
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (table[i] <= m)
            sum += item[i];
    }
    return sum;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int result = 0;

    cin >> n >> m >> r;

    for (int i = 1; i <= n; i++)
    {
        cin >> item[i];
    }
    for (int i = 0; i < r; i++)
    {
        cin >> a >> b >> l;
        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
    }

    for (int i = 1; i <= n; i++)
        result = max(result, dijkstra(i));

    cout << result;
}