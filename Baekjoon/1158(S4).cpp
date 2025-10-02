#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, K;
    cin >> N >> K;
    vector<int> vec;
    queue<int> q;
    for (int i = 0; i < N; i++){
        q.push(i + 1);
    }
    while(!q.empty()){
        for (int i = 0; i < K - 1; i++)
        {
            q.push(q.front());
            q.pop();
        }
        vec.push_back(q.front());
        q.pop();
    }
    cout << "<";
    cout << vec[0];
    for (int i = 1; i < N; i++){
        cout << ", " << vec[i];
    }
    cout << ">";
}