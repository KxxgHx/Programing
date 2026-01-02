#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef pair<int, int> pp;

const int INF = 1e9;

vector<pp> graph[10001];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, D;
    cin >> N >> D;

    for (int i = 0; i < N; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        if (to <= D)
        {
            graph[from].push_back({to, cost});
        }
    }

    priority_queue<pp, vector<pp>, greater<pp>> pq;

    vector<int> dist(D + 1, INF);

    dist[0] = 0;
    pq.push({0, 0});

    while(!pq.empty())
    {
        int now_dist = pq.top().first;
        int now = pq.top().second;

        pq.pop();

        if (now_dist > dist[now])
            continue;

        if (now + 1 <= D &&dist[now + 1] > now_dist + 1)
        {
            dist[now + 1] = now_dist + 1;
            pq.push({dist[now + 1], now + 1});
        }

        for (int i = 0; i < graph[now].size(); i++)
        {
            int next_node = graph[now][i].first;
            int cost = graph[now][i].second;

            if (dist[next_node] > now_dist + cost)
            {
                dist[next_node] = now_dist + cost;
                pq.push({dist[next_node], next_node});
            }
        }
    }
    cout << dist[D];
}