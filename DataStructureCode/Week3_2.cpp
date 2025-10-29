#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    cin >> str;
    string compress;
    int cnt = 1;
    for (size_t i = 1; i <= str.length(); i++){
        if(i<str.length()&&str[i]==str[i-1])
        {
            cnt++;
        }
        else{
            compress.push_back(str[i - 1]);
            compress += to_string(cnt);
            cnt = 1;
        }

    }
    cout << compress;
}