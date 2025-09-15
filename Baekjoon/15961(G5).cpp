#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, d, k, c;
    cin >> N >> d >> k >> c;
    
    vector<int> sushi(N);
    vector<int> sushi_cnt(d + 1, 0);
    int typeOfSushi = 0;
    int result = 0;

    for (int i = 0; i < N; i++) {
        cin >> sushi[i];
    }
    
    for (int i = 0; i < k; i++) {
        if (sushi_cnt[sushi[i]] == 0) {
            typeOfSushi++;
        }
        sushi_cnt[sushi[i]]++;
    }
    
    int current_result = typeOfSushi;
    if (sushi_cnt[c] == 0) {
        current_result++;
    }
    result = current_result;
    
    for (int i = k; i < N + k; i++) {
        int dup_sushi = sushi[(i - k) % N];
        sushi_cnt[dup_sushi]--;
        if (sushi_cnt[dup_sushi] == 0) {
            typeOfSushi--;
        }
        
        int plus_sushi = sushi[i % N];
        if (sushi_cnt[plus_sushi] == 0) {
            typeOfSushi++;
        }
        sushi_cnt[plus_sushi]++;
        
        current_result = typeOfSushi;
        if (sushi_cnt[c] == 0) {
            current_result++;
        }
        result = max(result, current_result);
    }

    cout << result;
}