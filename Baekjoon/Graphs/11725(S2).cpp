#include <iostream>
#include <vector>
using namespace std;

int node [100001]; 
vector<int> v[100001];
int N;
int parent, son;
void dfs(int x, int y)
{
	node[x] = y;
	for (auto next : v[x])
	{
		if (!node[next])
			dfs(next,x);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N;
	for (int i = 1; i < N; i++)
	{
		cin >> parent >> son;
		v[parent].push_back(son);
		v[son].push_back(parent);
	}

	dfs(1, 1);

	for (int i = 2; i <= N; i++)
	{
		cout << node[i] << "\n";
	}

}