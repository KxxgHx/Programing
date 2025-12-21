#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	map<int, int> AA;
	int N, M, n;
	cin >> N;
	while (N > 0) //for문으로 사용해도 무방할 것 같음 그냥 while문 쓰고 싶었음
	{
		cin >> n;
		AA[n]++; //while이 실행 될 동안의 value 값을 넣기
		N--;
	}
	cin >> M;
	while (M > 0)
	{
		cin >> n;
		auto comp = AA.find(n); //auto는 우측의 값에 따라 자동으로 자료형을 설계해줌을 인지
	
		if (comp != AA.end()) //비교가 끝까지 돌 지 않았다면 value값을 출력할 수 있도록
			cout << comp->second << ' '; //first => key, second => value
		else
			cout << "0" << ' ';
		M--;
	}
}
