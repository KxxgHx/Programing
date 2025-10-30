#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> graph[10001];
bool visited[10001];
int cnt;

void dfs(int current){
    visited[current] = true;
    cnt++;
    
    for(int next : graph[current]){
        if(!visited[next])
            dfs(next);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[b].push_back(a);
    }
    
    int max_count = 0;
    int result[10001];
    int result_size = 0;
    
    for (int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++){
            visited[j] = false;
        }
        
        cnt = 0;
        dfs(i);
        
        if(cnt > max_count){
            max_count = cnt;
            result_size = 0;
            result[result_size++] = i;
        }
        else if(cnt == max_count){
            result[result_size++] = i;
        }
    }
    
    for(int i = 0; i < result_size; i++){
        cout << result[i] << ' ';
    }
    
    return 0;
}