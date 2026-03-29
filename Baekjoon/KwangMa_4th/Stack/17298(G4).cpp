#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

stack<int> s;
int result[10000001];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<int> input(N);

    for (int i = 0; i < N; i++)
        cin >> input[i];

    for (int i = N - 1; i >= 0; i--)
    {
        while (!s.empty() && s.top() <= input[i])
            s.pop();
        
        if(s.empty())
            result[i] = -1;
        else
            result[i] = s.top();

        s.push(input[i]);
    }

    for (int i = 0; i < N; i++)
        cout << result[i] << " ";
}