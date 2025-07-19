#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int N, cnt = 0;
vector<pair<string, int>> v;
vector<string> a;
string s, tmp;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) //확장자만 남겨 a에 넣기
	{
		cin >> s;
		s.erase(0, s.find('.') + 1);
		a.push_back(s);

	}
	sort(a.begin(), a.end());

	tmp = a[0];
	for (int i = 0; i < a.size(); i++)
	{
		if (tmp == a[i]) cnt++; //동일 확장자 개수 카운트
		else if (tmp != a[i]) //다른 확장자일 시 확장자 명 및 카운트 수 a에 넣음
		{
			v.push_back(pair<string, int>(tmp, cnt));
			tmp = a[i];
			cnt = 1;
		}
	}
	v.push_back(pair<string, int>(tmp, cnt));

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].first << " " << v[i].second << endl;
	}
}
