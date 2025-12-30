#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // 무한대 값 설정

// 노드 수, 간선 수, 시작 노드
int n, m, start;
// 각 노드에 연결되어 있는 노드에 대한 정보를 담는 리스트 (노드 번호, 비용)
vector<pair<int, int>> graph[100001];
// 최단 거리 테이블 만들기
int d[100001];

void dijkstra(int start) {
    // 우선순위 큐 선언 (최소 힙: 비용이 적은 것이 위로 올라옴)
    // <비용, 노드번호> 순서로 저장 (pair의 첫 번째 원소 기준으로 정렬되므로)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 시작 노드로 가기 위한 최단 경로는 0으로 설정하여, 큐에 삽입
    pq.push({0, start});
    d[start] = 0;

    while (!pq.empty()) {
        // 가장 최단 거리가 짧은 노드에 대한 정보 꺼내기
        int dist = pq.top().first; // 현재까지의 비용
        int now = pq.top().second; // 현재 노드
        pq.pop();

        // 현재 노드가 이미 처리된 적이 있는 노드라면 무시 (더 짧은 경로를 이미 찾은 경우)
        if (d[now] < dist) continue;

        // 현재 노드와 연결된 다른 인접한 노드들을 확인
        for (int i = 0; i < graph[now].size(); i++) {
            int cost = dist + graph[now][i].second; // 현재 노드를 거쳐서 가는 비용
            
            // 현재 노드를 거쳐서 다른 노드로 이동하는 거리가 더 짧은 경우
            if (cost < d[graph[now][i].first]) {
                d[graph[now][i].first] = cost;
                // 값이 갱신될 때만 큐에 넣음
                pq.push({cost, graph[now][i].first});
            }
        }
    }
}

int main() {
    // 입력 예시
    cin >> n >> m >> start;

    // 모든 간선 정보를 입력받기
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        // a번 노드에서 b번 노드로 가는 비용이 c라는 의미
        graph[a].push_back({b, c});
    }

    // 최단 거리 테이블을 모두 무한으로 초기화
    fill(d, d + 100001, INF);

    // 다익스트라 알고리즘을 수행
    dijkstra(start);

    // 모든 노드로 가기 위한 최단 거리를 출력
    for (int i = 1; i <= n; i++) {
        if (d[i] == INF) cout << "INFINITY" << '\n';
        else cout << d[i] << '\n';
    }
}