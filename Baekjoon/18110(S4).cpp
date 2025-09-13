#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int cut = round(n * 0.15);
    double sum = 0;
    int count = 0;

    for (int i = cut; i < n - cut; i++) {
        sum += a[i];
        count++;
    }
    
    // 0.5를 더해 내림하여 반올림 효과를 냅니다.
    int sol = (count > 0) ? floor(sum / count + 0.5) : 0;
    
    cout << sol;

    return 0;
}