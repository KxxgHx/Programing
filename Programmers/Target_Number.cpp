#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> number;
int result;

int dfs(int idx, int sum)
{
    if(idx == (int)number.size())
    {
        if(sum == result)
            return 1;
        else
            return 0;
    }
    return dfs(idx + 1, sum + number[idx]) + dfs(idx + 1, sum - number[idx]);
}

int solution(vector<int> numbers, int target) {
    number = numbers;
    result = target;
    return dfs(0, 0);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    
    int n;
    cin >> n;
    int target;
    cin >> target;
    number.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> number[i];
    }

    cout << solution(number, target);
}