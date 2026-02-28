#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    stack<char> st;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' &&str[i] <= 'Z')
        {
            cout << str[i];
            continue;
        }

        if(str[i] == '(')
            st.push(str[i]);
        else if(str[i] == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                cout << st.top();
                st.pop();
            }
            st.pop();
        }
        else if(str[i] == '*' || str[i] == '/')
        {
            while (!st.empty() && (st.top() == '*' || st.top() == '/'))
            {
                cout << st.top();
                st.pop();
            }
            st.push(str[i]);
        }
        else if (str[i] == '+' || str[i] == '-')
        {
            while (!st.empty() && st.top() != '(')
            {
                cout << st.top();
                st.pop();
            }
            st.push(str[i]);
        }

        
    }
    while(!st.empty())
    {
        cout << st.top();
        st.pop();
    }
}