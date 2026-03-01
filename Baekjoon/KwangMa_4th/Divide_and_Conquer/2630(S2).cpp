#include <iostream>

using namespace std;

int arr[129][129];
int white = 0;
int blue = 0;

void paper(int x, int y, int k)
{
    bool isCut = false;
    int first_color = arr[x][y];

    for (int i = x; i < x + k; i++)
    {
        for (int j = y; j < y + k; j++)
        {
            if(arr[i][j] != first_color)
            {
                isCut = true;
                break;
            }
        }
    }
    if(isCut)
    {
        paper(x, y, k / 2);
        paper(x, y + k / 2, k / 2);
        paper(x + k / 2, y, k / 2);
        paper(x + k / 2, y + k / 2, k / 2);
    }
    else
    {
        if(first_color == 1)
            blue++;
        else
            white++;
    }
} 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> arr[i][j];
    }
    paper(0, 0, N);

    cout << white << '\n'
         << blue << '\n';

    return 0;
}