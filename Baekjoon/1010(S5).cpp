#include<iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;


	for (int i = 0; i < T; i++) {
		int n, m;
		cin >> n >> m;

		long ans = 1;
		int a = 1;
		for (int j = m; j > m - n; j--) {
			ans *= j;
			ans /= a;
			a++;
		}

		cout << ans << "\n";
	}
	return 0;
}