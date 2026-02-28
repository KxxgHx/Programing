#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int city[101][101];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    fill(city[0], city[101], 1e9);

    for (int i = 1; i <= n; i++)
    {
        city[i][i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        city[from][to] = min(city[from][to], cost);
    }

    for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				city[i][j] = min(city[i][j], city[i][k] + city[k][j]);
			}
		}
	}

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(city[i][j] == 1e9)
                cout << "0 ";
            else
                cout << city[i][j] << " ";
        }
        cout << '\n';
    }
}