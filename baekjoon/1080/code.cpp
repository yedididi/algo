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
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++)
            mapOne[i][j] = tmp[j] - '0';
    }

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++)
            mapTwo[i][j] = tmp[j] - '0';
    }
}

void flipNumbers(int startI, int startJ)
{
    for (int i = startI; i < startI + 3; i++)
    {
        for (int j = startJ; j < startJ + 3; j++)
            mapOne[i][j] = !mapOne[i][j];
    }
}

bool checkSame()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mapOne[i][j] != mapTwo[i][j])
                return (false);
        }
    }
    return (true);
}

int main(void)
{
    int flipCount = 0;
    getInput();

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = 0; j < m - 2; j++)
        {
            if (mapOne[i][j] != mapTwo[i][j])
            {
                flipNumbers(i, j);
                flipCount++;
            }
        }
    }
    if (checkSame() == false)
        cout << -1 << endl;
    else
        cout << flipCount << endl;
}