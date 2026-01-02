#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int first[9];
int arr[9];
bool visited[9];

void dfs(int k) {
    if (k == M)
    {
        for (int i = 0; i < M; i++)
            cout << arr[i] << " ";
        cout << "\n";
        return;
    }

    int last_val = 0;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && first[i] != last_val)
        {
            visited[i] = true;
            arr[k] = first[i];
            last_val = arr[k];
            
            dfs(k + 1);
            
            visited[i] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> first[i];

    sort(first, first + N);

    dfs(0);
}