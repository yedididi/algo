#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <string>
#include <vector>
using namespace std;

char map[8][8] = {0, };
vector<pair<int, int>> wallLocation;
int iNum[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int jNum[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

void bfs()
{
    queue<tuple<int, int, int>> q; //int i, int j, int mvCount
    q.push(make_tuple(7, 0, 0));

    while (!q.empty())
    {
        int i, j, mvCount;
        tie(i, j, mvCount) = q.front();
        q.pop();

        if ((i == 7 && j == 7) || mvCount == 8)
        {
            cout << 1 << endl;
            return ;
        }

        for (int index = 0; index < 9; index++)
        {
            int newI = i + iNum[index];
            int newJ = j + jNum[index];
            
            bool isCrashed = false; 
            for (vector<pair<int, int>>::iterator itr = wallLocation.begin(); itr != wallLocation.end(); itr++)
            {
                if ((newI == (itr->first + mvCount + 1)) && newJ == itr->second)
                    isCrashed = true;
                if ((newI == (itr->first + mvCount)) && newJ == itr->second)
                    isCrashed = true;
            }
            if (newI < 0 || newI >= 8 || newJ < 0 || newJ >= 8 || isCrashed)
                continue;

            q.push(make_tuple(newI, newJ, mvCount + 1));
        }
    }
    cout << 0 << endl;
}

int main(void)
{
    for (int i = 0; i < 8; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = tmp[j];
            if (tmp[j] == '#')
                wallLocation.push_back(make_pair(i, j));
        }
    }
    bfs();
}