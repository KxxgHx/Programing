#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<bool> isPrime(1000001, true); //소수면 true, 아니면 false
    isPrime[0] = isPrime[1] = false;
    int N, M;
    cin >> M >> N;

    for (int i = 2; i * i <= N; i++){
        if(isPrime[i]){
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
    for (int i = M; i <= N; i++)
    {
        if(isPrime[i])
            cout << i << "\n";
    }
}