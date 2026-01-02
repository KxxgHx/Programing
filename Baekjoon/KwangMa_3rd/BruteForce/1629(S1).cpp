#include <iostream>

using namespace std;
typedef long long ll;

long long A, B, C;

ll total(ll x)
{
	if (x == 1)
		return A % C;

	ll temp = total(x / 2);
    
	temp = (temp * temp) % C;

	if (x % 2 == 0)
		return temp;
	else
		return (temp * (A % C)) % C;
	
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> A >> B >> C;

	cout << total(B);
}