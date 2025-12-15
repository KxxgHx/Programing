#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); //코드 시간 초과 방지를 위해 사용한다라는 것을 외우자
    cin.tie(0); //얘까지가 set

    int n, m;
    cin >> n >> m;

    unordered_set<string> AA;  //O(1)의 TimeComplexity , set은 map과 달리 key값이 필요 X
    vector<string> result;

    for (int i = 0; i < n; i++) { //듣도 못한 사람을 저
        string name;
        cin >> name;
        AA.insert(name);
    }

    for (int i = 0; i < m; i++) { //듣보잡인 것 찾기
        string name;
        cin >> name;
        if (AA.count(name)) {
            result.push_back(name);
        }
    }

    sort(result.begin(), result.end());

    cout << result.size() << '\n';
    for (const string& name : result) {
        cout << name << '\n';
    }

    return 0;
}
