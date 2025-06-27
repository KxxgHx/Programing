#include <iostream>
using namespace std;

int apt(int a, int b);

int main(void)
{
	int T, k, n;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> k >> n;
		cout << apt(k, n)<<endl;
	}
}

int apt(int a, int b)
{
	if (a == 0) //맨 밑의 층일 시에는 b호 만큼의 인원 거주 => b를 리턴
		return b;
	else if (b == 1) //호가 1인 경우에는 층과 관계 없이 1명 거주 => 1을 리턴
		return 1;
	else
		return apt(a - 1, b) + apt(a, b - 1); //문제 해석을 할 시 재귀함수로 이러한 방식으로 나옴
}
