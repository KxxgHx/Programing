#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
typedef pair<int, int> pp;

vector<pp> graph[200005];
int V, E;

void dijkstra(int start, vector<int>& table)
{
    fill(table.begin(), table.end(), INF);
    
    priority_queue<pp, vector<pp>, greater<pp>> pq;
    
    pq.push({0, start});
    table[start] = 0;

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
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> V >> E;

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int v1, v2;
    cin >> v1 >> v2;

    vector<int> dist_1(V + 1);
    vector<int> dist_v1(V + 1);
    vector<int> dist_v2(V + 1);

    dijkstra(1, dist_1);
    dijkstra(v1, dist_v1);
    dijkstra(v2, dist_v2);

    long long path1 = INF;
    long long path2 = INF;

    if (dist_1[v1] != INF && dist_v1[v2] != INF && dist_v2[V] != INF) {
        path1 = (long long)dist_1[v1] + dist_v1[v2] + dist_v2[V];
    }

    if (dist_1[v2] != INF && dist_v2[v1] != INF && dist_v1[V] != INF) {
        path2 = (long long)dist_1[v2] + dist_v2[v1] + dist_v1[V];
    }

    long long result = min(path1, path2);

    if (result >= INF) cout << -1 << '\n';
    else cout << result << '\n';

    return 0;
}