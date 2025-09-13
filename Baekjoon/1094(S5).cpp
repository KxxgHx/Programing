#include <iostream>

using namespace std;

int count(int num)
{
	int a = 0;
	while (num != 0)
	{
		if (num % 2 == 1)
		{
			a++;
		}
		num = num / 2;
	}
	return a;
}
int main()
{
	int input;
	int output;
	cin >> input;
	output = count(input);
	cout << output;
}