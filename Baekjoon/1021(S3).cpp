#include <iostream>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    deque<int> q;
    int N;
    int index;
    int cnt = 0;

    cin >> N;
    for (int i=0; i < N;i++) {
        q.push_back(i+1);
    }
    int M;
    cin >> M;
    
    int inputnum;
    for (int i = 0; i < M; i++) {
        cin >> inputnum;
        for (int aa = 0; aa < q.size(); aa++) { 
            if(q[aa] == inputnum) {
                index = aa;
                break;
            }
        }
        while(1) {
            
            if (q.front() == inputnum) {
                q.pop_front();
                break;
            }
            else {
                if (index < (q.size()- index)) { 
                    cnt++;
                    q.push_back(q.front());
                    q.pop_front();
                }
                else {
                    cnt++;
                    q.push_front(q.back());
                    q.pop_back();
                }
            }
            if (q.size() == 0) {
                break;
            }
        }
    }

    cout << cnt << " ";
    
	return 0;
}