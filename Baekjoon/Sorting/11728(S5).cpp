#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N, M;
	int idx = 0;
	cin >> N >> M;
	vector<int> A(N);
	vector<int> B(M);
	vector<int> C;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
		int a = A[i];
		C.push_back(a);
	}
	for (int i = 0; i < M; i++)
	{
		cin >> B[i];
		int b = B[i];
		C.push_back(b);
	}
	sort(C.begin(), C.end());
	
	for (int i = 0; i < C.size(); i++)
	{
		cout << C[i] << " ";
	}

}