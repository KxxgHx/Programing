#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pp;
const int INF = 1e9;

vector<pp> graph[10001];
int N, M, X;
int from, to, cost;
int min_table[10001];
int Cost[10001];

int dijkstra(int start, int X)
{
    fill(min_table, min_table + 10001, INF);
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
    return min_table[X];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int result = -1;

    cin >> N >> M >> X;

    for (int i = 0; i < M; i++)
    {
        cin >> from >> to >> cost;
        graph[from].push_back({to, cost});
    }

    for (int i = 1; i <= N; i++)
    {
        Cost[i] = dijkstra(i, X);
    }

    dijkstra(X, X);

    for (int i = 1; i <= N; i++)
    {
        Cost[i] += min_table[i];
        result = max(result, Cost[i]);
    }

    cout << result;
}