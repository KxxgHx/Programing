#include <iostream>
#include <vector>

using namespace std;

int ans;
int n, k;

vector <int> kit;
bool visited[8];

void dfs(int cnt, int total) {
	if (total < 500)
		return;
	if (cnt == kit.size()) {
		ans++;
		return;
	}

	for (int i = 0; i < kit.size(); i++) {
		if (!visited[i]) {
			visited[i] = true;
			dfs(cnt + 1, total + kit[i] - k);
			visited[i] = false;
		}
	}
}

int main() {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int c; cin >> c;
		kit.push_back(c);
	}

	dfs(0, 500);

	cout << ans;
}