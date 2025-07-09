#include <iostream>

using namespace std;

int main()
{
	int fibarray[41] = { 0,1,1 };
	int N;
	int unknown;

	for (int i = 3; i < 41; i++)
	{
		fibarray[i] = fibarray[i - 1] + fibarray[i - 2];
	}

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> unknown;
		if (unknown == 0)
			cout << 1 << ' ' << 0 << endl;
		else if (unknown == 1)
			cout << 0 << ' ' << 1 << endl;
		else
			cout << fibarray[unknown - 1] << ' ' << fibarray[unknown] << endl;
	}

}
