#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	string name;
	unordered_map<string, int> person;
	for (int i = 0; i < N; i++)
	{
		cin >> name;
		person[name]++;
	}
	for (int i = 0; i < N - 1; i++)
	{
		cin >> name;
		person[name]--;
	}
	for (auto length = person.begin(); length != person.end(); length++)
	{
		if (length->second != 0)
			cout << length->first << endl;
	}
}
