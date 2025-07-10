#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int count = 0;
    while (n>=0){
        if(n%5==0){
            count += n/5;
            cout << count;
            return 0;
        }

        n-=3;
        count++;

    }
    cout << -1 ;
}
