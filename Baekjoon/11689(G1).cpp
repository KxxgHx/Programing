#include <iostream>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin >> n;
    ll result = n; //오일러 피 함수 결과 값
    ll temp = n; //n을 나누며 변형시킬 변수

    //2부터 root(temp)까지의 소인수 판별
    for (ll p = 2; p * p <= temp; p++){
        if (temp % p == 0){ //p가 temp의 소인수라면
            while (temp % p == 0)
                temp /= p;
            result -= result / p; //오일러 피 공식 result *= (1-1/p) 적용
        }
    }
    //루프에서 나왔음에도 temp가 1보다 크면 소인수 하나가 남은 것이므로 예외처리
    if (temp > 1)
    {
        result -= result / temp;
    }
    cout << result;
}