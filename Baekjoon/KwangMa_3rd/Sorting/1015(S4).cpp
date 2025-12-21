#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}

	sort(a.begin(), a.end());

	vector<int> b(n);
	for (int i = 0; i < n; ++i)
		b[a[i].second] = i;

	for (auto& p : b) {
		cout << p << ' ';
	}
	cout << '\n';
}

