#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int L, C;

void dfs(vector<char> v, int i, string str, int consonants, int vowels){
    str.push_back(v[i]);
    if(v[i] == 'a' || v[i] == 'e' || v[i] == 'i' || v[i] == 'o' || v[i] == 'u')
		vowels++;
	else
        consonants++;
    
    if(str.length() == L)
    {
        if (vowels >= 1 && consonants >= 2)
            cout << str << '\n';
        return;
    }
    for (int k = i + 1; k < C; k++)
        dfs(v, k, str, consonants, vowels);
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> L >> C;

    vector<char> vec(C);

    for (int i = 0; i < C; i++)
        cin >> vec[i];

    sort(vec.begin(), vec.end());

    for (int i = 0; i <= C - L; i++)
        dfs(vec, i, "", 0, 0);
}