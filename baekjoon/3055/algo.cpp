#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

int r, c;
char map[50][50] = {0, };
bool visited[50][50] = {false, };
int beaverI, beaverJ;
int mapLevel = 0;

int iNum[4] = {1, -1, 0, 0};
int jNum[4] = {0, 0, 1, -1};

void mvWater(void)
{
    // for (int i = 0; i < r; i++)
    // {
    //     for (int j = 0; j < c; j++)
    //     {
    //         if (map[i][j] == '*')
    //         {
    //             for (int index = 0; index < 4; index++)
    //             {
    //                 int newI = i + iNum[index];
    //                 int newJ = j + jNum[index];

    //                 if (map[newI][newJ] == '.')
    //                     map[newI][newJ] = '*';
    //             }
    //         }
    //     }
    // }

    queue<tuple<int, int>> water;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[i][j] == '*')
                water.push(make_tuple(i, j));  
        }
    }

    while (!water.empty())
    {
        int poppedI, poppedJ;
        tie(poppedI, poppedJ) = water.front();
        water.pop();

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedI + iNum[index];
            int newJ = poppedJ + jNum[index];

            if (newI < 0 || newI >= r || newJ < 0 || newJ >= c)
                continue;
            if (map[newI][newJ] == '.')
                map[newI][newJ] = '*';
        }
    }
}

// void printMap(int playerI, int playerJ)
// {
//     cout << "\n";
//     for (int i = 0; i < r; i++)
//     {
//         for (int j = 0; j < c; j++)
//         {
//             if (i == playerI && j == playerJ)
//                 cout << 'S';
//             else
//                 cout << map[i][j];
//         }
//         cout << "\n";
//     }
// }

void bfs(int startI, int startJ)
{
    queue<tuple<int, int, int>> q; //int i, int j, int time
    q.push(make_tuple(startI, startJ, 0));
    mvWater();

    while (!q.empty())
    {
        int poppedI, poppedJ, poppedTime;
        tie(poppedI, poppedJ, poppedTime) = q.front();
        q.pop();

        if (poppedI == beaverI && poppedJ == beaverJ)
        {
            cout << poppedTime << endl;
            return ;
        }

        if (poppedTime > mapLevel)
        {
            mvWater();
            mapLevel++;
        }

        for (int index = 0; index < 4; index++)
        {
            int newI, newJ;
            
            newI = poppedI + iNum[index];
            newJ = poppedJ + jNum[index];

            if (newI < 0 || newI >= r || newJ < 0 || newJ >= c || visited[newI][newJ] == true)
                continue;

            if (map[newI][newJ] == '.' || map[newI][newJ] == 'D')
            {
                // printMap(newI, newJ);
                visited[newI][newJ] = true;
                q.push(make_tuple(newI, newJ, poppedTime + 1));
            }
        }
    }
    cout << "KAKTUS\n";
}

int main(void)
{
    int startI, startJ;
    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < c; j++)
        {
            if (tmp[j] == 'D')
            {
                beaverI = i;
                beaverJ = j;
            }
            if (tmp[j] == 'S')
            {
                startI = i;
                startJ = j;
                map[i][j] = '.';
                continue;
            }
            map[i][j] = tmp[j];
        }
    }
    bfs(startI, startJ);
}