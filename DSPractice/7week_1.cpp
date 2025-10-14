#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> vec;
vector<int> RLE;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    int Max = 0;
    cout << "넣을 숫자의 갯수를 입력하세요 : ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        vec.push_back(a);
        if (Max < vec[i])
            Max = vec[i];
    }
    int cnt = 0;
    int temp = 0;
    while (temp <= Max + 1) {
        for (int i = 0; i < n; i++)
        {
            if (vec[i] == temp)
                cnt++;
        }
        RLE.push_back(cnt);
        RLE.push_back(temp);
        temp++;
        cnt = 0;
    }
    cout << "[";
    for (int i = 0; i < RLE.size() - 1; i++) {
        cout << RLE[i] << ", ";
    }
    cout << RLE[RLE.size() - 1] << "]";
}