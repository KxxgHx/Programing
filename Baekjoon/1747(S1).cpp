#include <iostream>
#include <vector>
#include <string>

#define Max 10000001
using namespace std;

bool Palindrome(int n);

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<bool> isPrime(Max, true);
    
    isPrime[0] = isPrime[1] = false;
    
    int N;
    cin >> N;

    for (int i = 2; i * i < Max; i++){
        if(isPrime[i]){
            for (int j = i * i; j < Max; j += i)
                isPrime[j] = false;
        }
    }
    
    for (int i = N; i < Max; i++){
        if (isPrime[i] && Palindrome(i))
        {
            cout << i;
            break;
        }
    }
    
    return 0;
}

bool Palindrome(int n){
    string s = to_string(n);
    for (int i = 0; i < s.length() / 2; i++){
        if(s[i] != s[s.length() - i - 1])
            return false;
    }
    return true;
}