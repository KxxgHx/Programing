#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

string str;
string prefix;
string suffix;

vector<int> get_jump(string& p) {
    int m = p.size();
    vector<int> pi(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];
        if (p[i] == p[j])
            pi[i] = ++j;
    }
    return pi;
}


vector<int> find_pattern(string& s, string& p) {
    vector<int> positions;
    vector<int> jump = get_jump(p);
    int n = s.size();
    int m = p.size();
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j])
            j = jump[j - 1];
        
        if (s[i] == p[j]) {
            if (j == m - 1) {
                positions.push_back(i - m + 1);
                j = jump[j];
            }
            else {
                j++;
            }
        }
    }
    return positions;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> str >> prefix >> suffix;

    int pre_size = prefix.size();
    int suf_size = suffix.size();

    vector<int> pre_pos = find_pattern(str, prefix);
    vector<int> suf_pos = find_pattern(str, suffix);

    unordered_set<string> distinct_strings;

    for (int start : pre_pos) {
        for (int end_start : suf_pos) {

            int total_len = (end_start + suf_size) - start;

            if (total_len < pre_size || total_len < suf_size) continue;

            distinct_strings.insert(str.substr(start, total_len));
        }
    }

    cout << distinct_strings.size();

    return 0;
}