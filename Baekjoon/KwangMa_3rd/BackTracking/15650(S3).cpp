#include <iostream>
using namespace std;


int N,M;
int arr[9];
bool visited[9];

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
            if(!visited[i])
            {
                visited[i] = true;
                arr[k] = i;
                dfs(i + 1, k + 1);
                visited[i] = false;
            }
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