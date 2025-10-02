#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while(T--)
    {
        string str;
        stack<char> aa;
        int i = 0;
        cin >> str;

        for (i = 0; i < str.size(); i++)
        {
            if(str[i] == '(')
                aa.push('(');
            else
            {
                if(aa.empty())
                    break;
                aa.pop();
            }
        }

        if (i == str.size() && aa.empty())
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
}