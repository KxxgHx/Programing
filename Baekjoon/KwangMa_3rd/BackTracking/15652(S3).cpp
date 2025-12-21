#include <iostream>
using namespace std;


int N,M;
int arr[8];
bool visited[8];

void dfs(int num, int k) {
    if (k == M)
    {
        for (int i = 0; i < M; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
    else
    {
        for (int i = num; i <= N; i++)
        {
            arr[k] = i;
            dfs(i, k + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    dfs(1,0);
}