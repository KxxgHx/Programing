#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    stack<int> s;
    vector<char> vec;
    int cnt = 1;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        while (cnt <= x)
        {
            s.push(cnt++);
            vec.push_back('+');
        }
        if (s.top() == x)
        {
            s.pop();
            vec.push_back('-');
        }
        else
        {
            cout << "NO";
            return 0;
        }
    }
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << '\n';
    }
}