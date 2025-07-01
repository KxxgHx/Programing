#include <iostream>
using namespace std;

int main()
{
	int T;
	int n;
	int Value[100];

	Value[1] = 1;
	Value[2] = 2;
	Value[3] = 4;
	for (int i = 4; i < 11; i++)
	{
		Value[i] = Value[i - 1] + Value[i - 2] + Value[i - 3];
	}
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> n;
		cout << Value[n] << endl;
	}

	
}
