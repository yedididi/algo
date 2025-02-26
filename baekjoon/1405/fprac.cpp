#include <iostream>

using namespace std;

int n;
long double possibility[4];
long double total = 0;

int iNum[4] = {0, 0, -1, 1};
int jNum[4] = {1, -1, 0, 0};

void input(void)
{
    cin >> n;

    for (int i = 0; i < 4; i++)
    {
        long double tmp;
        cin >> tmp;
        possibility[i] = tmp / 100.;
    }
}

void dfs(int oldI, int oldJ, int depth, long double percentage, bool visited[50][50])
{
    if (depth == n)
    {
        total += percentage;
        return ;
    }

    for (int index = 0; index < 4; index++)
    {
        int newI = oldI + iNum[index];
        int newJ = oldJ + jNum[index];

        if (visited[newI][newJ])
            continue ;

        visited[newI][newJ] = true;
        dfs(newI, newJ, depth + 1, (percentage * possibility[index]), visited);
        visited[newI][newJ] = false;
    }
}

int main(void)
{
    bool visited[50][50] = {0, };

    input();
    visited[20][20] = true;
    dfs(20, 20, 0, 1., visited);
    cout.precision(10);
    cout << total << endl;
}