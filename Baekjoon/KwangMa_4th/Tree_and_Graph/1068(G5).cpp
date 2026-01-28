#include <iostream>
#include <vector>

using namespace std;

int N, erase_node, root;
int leaf = 0;
vector<int> tree[51];

int dfs(int node)
{
    if(node == erase_node)
        return -1;
    if(!tree[node].size())
    {
        leaf++;
        return 0;
    }
    for (int i = 0; i < tree[node].size(); i++)
    {
        int temp = dfs(tree[node][i]);
        if (temp == -1 && tree[node].size() == 1)
            leaf++;
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        if (num == -1)
            root = i;
        else
            tree[num].push_back(i);
    }
    cin >> erase_node;
    dfs(root);
    cout << leaf;
}