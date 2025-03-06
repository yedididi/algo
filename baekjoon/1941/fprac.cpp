#include <iostream>
#include <string>

using namespace std;

char map[5][5] = {0,};
int totalNum = 0;
int princess[7] = {0, };
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};

void input()
{
    for (int i = 0; i < 5; i++)
    {
        string tmp;
        cin >> tmp; 
        for (int j = 0; j < 5; j++)
            map[i][j] = tmp[j];
    }
}

int numToTeam(int i)
{
    return (map[i / 5][i % 5]);
}

bool isSomBigger()
{
    int som = 0;

    for (int i = 0; i < 7; i++)
    {
        if (numToTeam(princess[i]) == 'S')
            som++;
    }

    if (som >= 4)
        return (true);
    return (false);
}

bool isConnected()
{
    for (int i = 0; i < 7; i++)
    {
        bool flag = false;
        int oldI = princess[i] / 5;
        int oldJ = princess[i] % 5;
        for (int index = 0; index < 4; index++)
        {
            int newI = oldI + iNum[index];
            int newJ = oldJ + jNum[index];
            if (newI < 0 || newI >= 5 || newJ < 0 || newJ >= 5)
                continue;
            int newClassNum = (newI * 5) + newJ;
            for (int j = 0; j < 7; j++)
            {
                if (newClassNum == princess[j])
                    flag = true;
            }
        }
        if (flag == false)
            return (false);
    }
    return (true);
}


void getSeven(int depth, int num)
{
    if (depth == 7)
    {
        if (isSomBigger() && isConnected())
            totalNum++;
        return;
    }

    for (int i = num; i < 25; i++)
    {
        princess[depth] = i;
        getSeven(depth + 1, i + 1);
    }
}

int main(void)
{
    input();

    getSeven(0, 0);
    cout << totalNum << endl;
}