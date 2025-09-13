#include <iostream>

using namespace std;
int maxvalue = -1000000001;
int minvalue = 1000000001;
int oper[4];
int num[11];
int N;
int resultvalue(int value, int cnt);


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> oper[i];
	}
	
	resultvalue(num[0], 1);

	cout << maxvalue << "\n" << minvalue << "\n";

	return 0;
}
int resultvalue(int value, int cnt)
{
	if (N == cnt)
	{
		if (maxvalue < value)
			maxvalue = value;
		if (minvalue > value)
			minvalue = value;
		return maxvalue, minvalue;
	}
	for (int i = 0; i < 4; i++)
	{
		if (oper[i] > 0)
		{
			oper[i]--;
			if (i == 0)
				resultvalue(value + num[cnt], cnt + 1);
			else if (i == 1)
				resultvalue(value - num[cnt], cnt + 1);
			else if (i == 2)
				resultvalue(value * num[cnt], cnt + 1);
			else
				resultvalue(value / num[cnt], cnt + 1);

			oper[i]++;
		}
	}
	return 0;
}