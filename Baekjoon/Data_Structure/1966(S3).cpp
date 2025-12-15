#include <iostream>
#include <queue>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int testcase;
    cin >> testcase;
    
    int N, M;
    

    while(testcase--){
        int cnt = 0;
        cin >> N >> M;

        queue<pair<int, int>> q;
        priority_queue<int> pq;

        for (int i = 0; i < N; i++)
        {
            int num;
            cin >> num;

            q.push({i, num});
            pq.push(num);
        }
        while(!q.empty()){
            int idx = q.front().first;
            int priority = q.front().second;
            q.pop();

            if (pq.top() == priority){
                pq.pop();
                cnt++;
                if(idx == M){
                    cout << cnt << '\n';
                    break;
                }
            }
            else{
                q.push({idx, priority});
            }
        }
    }
}