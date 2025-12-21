#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    map<string, string> value;
    string a, b;

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> a >> b;

        value[a] = b;
    }

    for (int i = 0; i < M; i++) {
        cin >> a;

        cout << value[a] << '\n';
    }

    return 0;
}
