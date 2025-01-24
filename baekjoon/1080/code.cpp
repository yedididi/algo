#include <iostream>

using namespace std;

int n, m;
bool mapOne[50][50] = {false, };
bool mapTwo[50][50] = {false, };

void getInput(void)
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> mapOne[i][j]; 
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> mapOne[i][j]; 
    }
}

int main(void)
{
    getInput();

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = 0; j < m - 2; j++)
        {
            if (mapOne[i][j] != mapTwo[i][j])
                flipNumbers(i, j);
        }
    }
}