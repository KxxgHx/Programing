#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

bool check(string a, string b){
    int i=0;
    if (a.length()==b.length()){
        for (int i=0;i<a.length();i++){
            if (a[i]!=b[i])
                return a[i]<b[i];
        }
    }
    return a.length()<b.length();
}


int main(){
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    string arr[n];

    for(int i=0;i<n;i++)
        cin >> arr[i];
    
    sort(arr, arr+n, check);

    cout << arr[0] << '\n';
    for(int i=1;i<n;i++){
        if(arr[i]==arr[i-1])
            continue;
        cout << arr[i] << '\n';
    }

   return 0;
}