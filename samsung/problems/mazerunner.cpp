#include <iostream>
#include <vector>

using namespace std;

int playerTotalCount;
pair<int, int> exitCoordinate;
vector<pair<int, int>> playerCoordinates;
vector<vector<int>> map(11, vector<int>(11, 0));
int totalMoveCount = 0;
int n, k;

// int iNum[4] = {0, -1, 0, 1};
// int jNum[4] = {-1, 0, 1, 0};

void input(void);

void movePlayers(void)
{
    int iNum[4] = {0, 0, -1, 1};
    int jNum[4] = {-1, 1, 0, 0};

    for (int i = playerCoordinates.size() - 1; i >= 0; i--)
    {
        int minimumToExit = INT_MAX;
        pair<int, int> minimumCoorinate;
        int oldI = playerCoordinates[i].first;
        int oldJ = playerCoordinates[i].second;
        map[oldI][oldJ] = 0;

        for (int index = 0; index < 4; index++)
        {
            int newI = oldI + iNum[index];
            int newJ = oldJ + jNum[index];
            int distanceToExit = abs(newI - exitCoordinate.first) + abs(newJ - exitCoordinate.second);

            if (newI < 1 || newI > n || newJ < 1 || newJ > n)
                continue;

            if (distanceToExit < minimumToExit)
            {
                minimumToExit = distanceToExit;
                minimumCoorinate.first = newI;
                minimumCoorinate.second = newJ;
            }
        }
        if (minimumCoorinate.first == exitCoordinate.first && minimumCoorinate.second == exitCoordinate.second)
        {
            playerTotalCount--;
            playerCoordinates.erase(playerCoordinates.begin() + i);
        }
        else
        {
            playerCoordinates[i].first = minimumCoorinate.first;
            playerCoordinates[i].second = minimumCoorinate.second;
        }
    }

    for (int i = 0; i < playerCoordinates.size(); i++)
    {
        map[playerCoordinates[i].first][playerCoordinates[i].second] = 'P';
    }
}

void rotateSquare(void)
{

}

int main(void)
{
    input();

    for (int time = 0; time < k; time++)
    {
        movePlayers();
        if (playerTotalCount == 0)
            break;
        rotateSquare();
    }

    cout << totalMoveCount << "\n" << exitCoordinate.first << " " << exitCoordinate.second << endl;
}   

void input(void)
{
    cin >> n >> playerTotalCount >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int tmp;
            cin >> tmp;
            map[i][j] = tmp - '0';
        }
    }

    for (int i = 0; i < playerTotalCount; i++)
    {
        int a, b;
        cin >> a >> b;
        playerCoordinates.push_back(make_pair(a, b));
        map[a][b] = 'P';
    }

    int a, b;
    cin >> a >> b;
    exitCoordinate.first = a;
    exitCoordinate.second = b;
    map[a][b] = 'E';
}