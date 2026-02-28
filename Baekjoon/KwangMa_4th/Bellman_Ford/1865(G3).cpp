#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> pp;

vector<pair<pp, int>> vec;
int dist[501];

void bellmanFord(int n)
{
    for (int i = 1; i <= n; i++)
        dist[i] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            int from = vec[j].first.first;
            int to = vec[j].first.second;
            int cost = vec[j].second;

            if (dist[from] + cost < dist[to])
                dist[to] = dist[from] + cost;
        }
    }

    for (int i = 0; i < vec.size(); i++)
    {
        int from = vec[i].first.first;
        int to = vec[i].first.second;
        int cost = vec[i].second;

        if (dist[from] + cost < dist[to])
        {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int TC;
    cin >> TC;

    while (TC--)
    {
        vec.clear();

        int n, m, w;
        cin >> n >> m >> w;

        for (int i = 0; i < m; i++)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            vec.push_back({{from, to}, cost});
            vec.push_back({{to, from}, cost});
        }

        for (int i = 0; i < w; i++)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            vec.push_back({{from, to}, -cost});
        }

        bellmanFord(n);
    }
}