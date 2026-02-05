#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> pp;
int N;
int ans = 0;
bool visit[15][15];

int mvx[3] = {-1, 0, 1};
int mvy[3] = {1, 1, 1};

void dfs(int y) {
    if (y == N) {
        ans++;
        return;
    }

    for (int x = 0; x < N; x++) {
        if (visit[y][x]) continue;

        visit[y][x] = true; 
        
        queue<pp> q;

        for (int j = 0; j < 3; j++) { 
            for (int i = 1; i < N; i++) {
                int nx = x + mvx[j] * i;
                int ny = y + mvy[j] * i;

                if (nx >= N || nx < 0 || ny >= N || ny < 0) break;

                if (visit[ny][nx]) continue;

                visit[ny][nx] = true;
                q.push({nx, ny});
            }
        }
        dfs(y + 1);

        while (!q.empty()) {
            pair<int, int> pos = q.front();
            q.pop();
            visit[pos.second][pos.first] = false;
        }
       
        visit[y][x] = false;

    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    dfs(0);

    cout << ans;

    return 0;
}