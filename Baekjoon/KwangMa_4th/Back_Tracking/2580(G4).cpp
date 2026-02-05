#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> pp;

int sudoku[9][9];
bool check = false;
vector<pp> vec;
int num;

bool num_check(int a, int b)
{
    int target = sudoku[a][b];

    for (int i = 0; i < 9; i++)
    {
        if (target == sudoku[a][i] && i != b) // 행에서 중복
            return false;
        if (target == sudoku[i][b] && i != a) // 열에서 중복
            return false;
    }
    int row = a / 3;
    int column = b / 3;
    for (int i = row * 3; i < row * 3 + 3; i++)
    {
        for (int j = column * 3; j < column * 3 + 3; j++)
        {
            if (target == sudoku[i][j] && i != a && j != b)
                return false;
        }
    }
    return true;
}

void func(int cnt)
{
    if(check)
        return;
    
    if(cnt == num)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << sudoku[i][j] << " ";
            cout << '\n';
        }
        check = true;
        return;
    }

    for (int i = 1; i <= 9; i++)
    {
        int column = vec[cnt].first;
        int row = vec[cnt].second;

        sudoku[column][row] = i;

        if(num_check(column, row))
            func(cnt + 1);

        sudoku[column][row] = 0;
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            cin >> sudoku[x][y];
            if (sudoku[x][y] == 0)
            {
                vec.push_back({x, y});
                num++;
            }
        }
    }
    func(0);
}