#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

typedef pair<int, int> pp;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int V, E, start;
    cin >> V >> E;
    cin >> start;

    vector<pp> graph[20001];
    vector<int> min_table(V + 1, INF);

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    priority_queue<pp, vector<pp>, greater<pp>> pq;

    pq.push({0, start});
    min_table[start] = 0;

    while(!pq.empty())
    {
        int now_cost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (min_table[now] < now_cost)
            continue;

        for (int i = 0; i < graph[now].size(); i++)
        {
            int next_node = graph[now][i].first;
            int cost = now_cost + graph[now][i].second;

            if (cost < min_table[next_node])
            {
                min_table[next_node] = cost;
                pq.push({cost, next_node});
            }
        }
    }

    for (int i = 1; i <= V; i++)
    {
        if(min_table[i] == INF)
            cout << "INF" << '\n';
        else
            cout << min_table[i] << '\n';
    }
}