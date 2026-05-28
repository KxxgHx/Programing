#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

struct Node {
    int x, y, dist;
};

int solution(vector<vector<int>> maps) {
    int n = maps.size();
    int m = maps[0].size();
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<Node> q;

    q.push({0, 0, 1});
    visited[0][0] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.x == n - 1 && cur.y == m - 1) return cur.dist;

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (maps[nx][ny] == 0 || visited[nx][ny]) continue;

            visited[nx][ny] = true;
            q.push({nx, ny, cur.dist + 1});
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> maps(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maps[i][j];

    cout << solution(maps) << "\n";
    return 0;
}