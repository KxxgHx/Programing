#include <iostream>
#include <map>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    map<string, string, greater<>> m; //내림차순을 하기 위해서는 greater<>을 사용한다는 것(여기서 1회 틀림)
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name, inout;

        cin >> name >> inout; //enter을 넣었어도 leave를 사용 시 쓰레기가 되기에 그냥 덮어버려도 됨
        m[name] = inout;

    }

    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second == "enter") {
            cout << it->first << "\n";
        }
    }
}
