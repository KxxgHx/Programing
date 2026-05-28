#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> number;
int result;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    return answer;
}

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

int main()
{
    
}