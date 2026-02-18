#include <iostream>
#include <array>
using namespace std;

int main()
{
    cout << "숫자를 입력하세요 : ";
    int n;
    cin >> n;
    while (n > 10)
    {
        cout << "숫자는 10 이하여야 합니다. 다시 입력하세요 : ";
        cin >> n;
    }
    array<array<int, 10>, 10> arr;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    int maincross = 0;
    int subcross = 0;
    for (int i = 0; i < n; i++)
    {
        maincross += arr[i][i];
        subcross += arr[i][n - i - 1];
    }

    cout << "주대각선 합 : " << maincross << "\n";
    cout << "부대각선 합 : " << subcross << "\n";

    if(maincross == subcross)
        cout << "두 합은 같다";
    else
        cout << "두 합은 다르다";
}