#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;
int num;

void post_order(int start, int end)
{
    if (start >= end)
        return;
    if(start == end - 1)
    {
        cout << tree[start] << '\n';
        return;
    }
    int idx = start + 1;
    while (idx < end)
    {
        if (tree[start] < tree[idx])
            break;
        idx++;
    }

    post_order(start + 1, idx);
    post_order(idx, end);
    cout << tree[start] << '\n';

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
    while (cin >> num)
    {
        tree.push_back(num);
    }
        

    post_order(0, tree.size());

    return 0;
}