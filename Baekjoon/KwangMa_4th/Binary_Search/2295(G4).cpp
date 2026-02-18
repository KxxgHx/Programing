#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sum;
int arr[1001];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            sum.push_back(arr[i] + arr[j]);
        }
    }

    sort(arr, arr + N);
    sort(sum.begin(), sum.end());

    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int mid = arr[i] - arr[j];
            bool check = binary_search(sum.begin(), sum.end(), mid);
            if(check)
            {
                cout << arr[i] << '\n';
                return 0;
            }
            
        }
    }
}