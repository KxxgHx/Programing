#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // 무한대 값 설정

int n, m, start;
vector<pair<int, int>> graph[100001];
int d[100001];
bool visited[100001]; // 방문 체크 배열이 필수적임

// 방문하지 않은 노드 중에서, 가장 최단 거리가 짧은 노드의 번호를 반환
int getSmallestNode() {
    int min_value = INF;
    int index = 0; // 가장 최단 거리가 짧은 노드(인덱스)
    for (int i = 1; i <= n; i++) {
        if (d[i] < min_value && !visited[i]) {
            min_value = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start) {
    // 시작 노드 초기화
    d[start] = 0;
    visited[start] = true;
    
    // 시작 노드와 연결된 노드들의 거리 1차 갱신
    for (int i = 0; i < graph[start].size(); i++) {
        d[graph[start][i].first] = graph[start][i].second;
    }

    // 시작 노드를 제외한 전체 n - 1개의 노드에 대해 반복
    for (int i = 0; i < n - 1; i++) {
        // 현재 최단 거리가 가장 짧은 노드를 꺼내서, 방문 처리
        int now = getSmallestNode(); // 여기서 O(V) 소요
        visited[now] = true;
        
        // 현재 노드와 연결된 다른 노드 확인
        for (int j = 0; j < graph[now].size(); j++) {
            int cost = d[now] + graph[now][j].second;
            if (cost < d[graph[now][j].first]) {
                d[graph[now][j].first] = cost;
            }
        }
    }
}

int main() {
    cin >> n >> m >> start;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    fill(d, d + 100001, INF);
    
    dijkstra(start);

    for (int i = 1; i <= n; i++) {
        if (d[i] == INF) cout << "INFINITY" << '\n';
        else cout << d[i] << '\n';
    }
}