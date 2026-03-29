#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack<int> stc;
    queue<char> q;

    int num = 1;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        while (num <= a)
        {
            stc.push(num++);
            q.push('+');
        }
        if(a == stc.top())
        {
            stc.pop();
            q.push('-');
        }
        else
        {
            cout << "NO";
            return 0;
        }
    }

    while(!q.empty())
    {
        cout << q.front() << '\n';
        q.pop();
    }
}