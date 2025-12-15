#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<int> lesson(N);

    ll total = 0;
    int maximum = 0;

    for (int i = 0; i < N; i++)
    {
        cin >> lesson[i];
        total += lesson[i];

        maximum = max(maximum, lesson[i]);
    }
    int low = maximum; //입력 값의 최댓값을 최소
    int high = total; //총 합을 최소값으로 선언
    int blue_size = high; //blueray의 최소값을 찾기 위해 최대치인 총합으로 설정

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int blue_count = 1;
        ll minimum_sum = 0;

        for (int i = 0; i < N; i++)
        {
            int aa = lesson[i];

            if (aa + minimum_sum <= mid)
                minimum_sum += aa;
            else
            {
                blue_count++;
                minimum_sum = aa;
            }
        }
        if(blue_count <= M)
        {
            blue_size = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    cout << blue_size;
}