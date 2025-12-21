#include <queue>
#include <iostream>	
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N = 0, input = 0;
	priority_queue<int, vector<int>, greater<int>> q;
	cin >> N;	
	for (int i = 0; i < N; i++) {
		cin >> input;
		if (input != 0) {		
			q.push(input);
		}
		else {	
			if (q.size() == 0) {		
				cout << 0 << "\n";
			}
			else {
				cout << q.top() << "\n";	
				q.pop();				
			}
		}
	}
	return 0;
}
