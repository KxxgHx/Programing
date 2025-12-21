#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int types[4];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int S, P;
    int cnt = 0;
    string str;
    int a = 0, c = 0, g = 0, t = 0;
    
    cin >> S >> P;
    cin >> str;
    for (int i = 0; i < 4; i++)
    {
        cin >> types[i];
    }
    for (int i = 0; i < P; i++)
    {
        if(str[i]=='A')
            a++;
        else if(str[i]=='C')
            c++;
        else if(str[i]=='G')
            g++;
        else
            t++;
    }
    if (a >= types[0] &&c >= types[1] &&g >= types[2] &&t >= types[3])
        cnt++;
    for (int i = P; i < S; i++)
    {
        if(str[i-P]=='A')
            a--;
        else if(str[i-P]=='C')
            c--;
        else if(str[i-P]=='G')
            g--;
        else if(str[i-P]=='T')
            t--;
        if(str[i]=='A')
            a++;
        else if(str[i]=='C')
            c++;
        else if(str[i]=='G')
            g++;
        else
            t++;
        if (a >= types[0] &&c >= types[1] &&g >= types[2] &&t >= types[3])
            cnt++;
        
    }
    cout << cnt;
}