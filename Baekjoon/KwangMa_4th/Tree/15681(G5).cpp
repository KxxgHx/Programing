#include <iostream>
#include <vector>

using namespace std;

int N, R, Q;
vector<int> tree[100001];
int dp[100001];
vector<bool> visited;

void dfs(int curNode, int parent)
{

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> R >> Q;
    fill_n(dp, dp + 100001, 1);

    for (int i = 0; i < N - 1; i++)
    {
        int U, V;
        cin >> U >> V;
        tree[U].push_back(V);
        tree[V].push_back(U);
    }

    dfs(R, -1);
    
    for (int i = 0; i < Q; i++)
    {
        int U;
        cin >> U;
        
    }
}