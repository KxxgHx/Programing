#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    int left, right;
    int result = 0;
    cin >> N;

    vector<int> num;

    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        num.push_back(a);
    }

    sort(num.begin(), num.end());
    for (int i = 0; i < N; i++)
    {
        left = 0;
        right = N - 1;
        while (left < right)
        {
            if (left == i)
            {
                left++;
                continue;
            }
            if (right == i)
            {
                right--;
                continue;
            }
            if (num[left] + num[right] < num[i])
                left++;
            else if (num[left] + num[right] > num[i])
                right--;
            else {
                result++;
                break;
            }
        }
    }
    cout << result;
    return 0;
}