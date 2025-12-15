#include <iostream>
using namespace std;


int N,M;
int arr[8];
bool visited[8];

void dfs(int k) {
    if (k == M)
    {
        for (auto i = 0; i < M; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
    else
    {
        for (auto i = 1; i <= N; i++)
        {
            arr[k] = i;
            dfs(k + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    dfs(0);
}