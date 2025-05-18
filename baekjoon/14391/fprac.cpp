#include <iostream>

using namespace std;

int n, m;
int map[5][5];
bool result[5][5];

int main(void)
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int tmp;

            cin >> tmp;
            map[i][j] = tmp - '0';
        }
    }

    for (int i = 0; i < (1 << (n * m)); i++)
    {
        for (int num = 0; num < (n * m); num++)
        {
            result[num / n][num % n] = (i & (1 << num)) ? 1 : 0;
        }
    }
}