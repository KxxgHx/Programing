#include <iostream>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int a, b;
	int count = 1;

	cin >> a >> b;

	while (1)
	{
		if (a == b)
			break;
		else if (a > b)
		{
			count = -1;
			break;
		}
		if (b % 2 == 0)
		{
			b = b / 2;
			count++;
		}
		else if (b % 10 == 1)
		{
			b = (b - 1) / 10;
			count++;
		}
		else
		{
			count = -1;
			break;
		}
	}

	cout << count;
}
