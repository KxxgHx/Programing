#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string str;
int table[5001];

int KMP(string pattern)
{
    fill(table, table + 5001, 0);
    int result = 0;
    int start = 0;

    for (int i = 1; i < pattern.size(); i++)
    {
        while (start > 0 && pattern[i] != pattern[start])
        {
            start = table[start - 1];
        }
        if(pattern[i] == pattern[start])
        {
            table[i] = ++start;
        }
        result = max(result, table[i]);
    }
    return result;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> str;
    int result = 0;
    for (int i = 0; i < str.size(); i++)
        result = max(result, KMP(str.substr(i)));
    cout << result;
}