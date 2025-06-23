#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
	int n, m, i;
	map<string,int> a;
	map<string, int> b;
	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		string donthear;
		cin >> donthear;
		a[donthear] = i;
	}
	for (i = 0; i < m; j++)
	{
		string dontsee;
		cin >> dontsee;
		b[dontsee] = i;
	}

	
	
	
}