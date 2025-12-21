#include <iostream>
using namespace std;

int N, M;
int arr[1025][1025];
int Sum[1025][1025];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
            Sum[i][j] = arr[i][j] + Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1];
        }
    }

    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int result = Sum[x2][y2] - Sum[x1 - 1][y2]- Sum[x2][y1 - 1] + Sum[x1 - 1][y1 - 1];

        cout << result << '\n';
    }

    return 0;
}
