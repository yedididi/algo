#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int playerTotalCount;
pair<int, int> exitCoordinate;
vector<pair<int, int>> playerCoordinates;
vector<vector<int>> map(11, vector<int>(11, 0));
int totalMoveCount = 0;
int n, k;

void input(void);
void printMap(void);
void movePlayers(void);
void rotateSquare(void);

int main(void)
{
    input();

    for (int time = 1; time <= k; time++)
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
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];

    for (int i = 0; i < playerTotalCount; i++)
    {
        int a, b;
        cin >> a >> b;
        playerCoordinates.push_back({a, b});
    }

    int a, b;
    cin >> a >> b;
    exitCoordinate = {a, b};
}

void printMap(void)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            bool printed = false;

            if (exitCoordinate == make_pair(i, j))
            {
                cout << "E ";
                printed = true;
            }
            else
            {
                for (auto &p : playerCoordinates)
                {
                    if (p.first == i && p.second == j)
                    {
                        cout << "P ";
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed)
                cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void movePlayers(void)
{
    int iNum[4] = {0, 0, -1, 1};
    int jNum[4] = {-1, 1, 0, 0};

    for (int i = playerCoordinates.size() - 1; i >= 0; i--)
    {
        int oldI = playerCoordinates[i].first;
        int oldJ = playerCoordinates[i].second;
        int minDist = abs(oldI - exitCoordinate.first) + abs(oldJ - exitCoordinate.second);
        pair<int, int> nextPos = {oldI, oldJ};

        for (int d = 0; d < 4; d++)
        {
            int newI = oldI + iNum[d];
            int newJ = oldJ + jNum[d];

            if (newI < 1 || newI > n || newJ < 1 || newJ > n) continue;
            if (map[newI][newJ] >= 1 && map[newI][newJ] <= 9) continue;

            int dist = abs(newI - exitCoordinate.first) + abs(newJ - exitCoordinate.second);
            if (dist <= minDist)
            {
                minDist = dist;
                nextPos = {newI, newJ};
            }
        }

        if (nextPos == exitCoordinate)
        {
            playerCoordinates.erase(playerCoordinates.begin() + i);
            playerTotalCount--;
            totalMoveCount++;
        }
        else
        {
            if (nextPos != playerCoordinates[i])
                totalMoveCount++;
            playerCoordinates[i] = nextPos;
        }
    }
}

void rotateSquare(void)
{
    int squareSize = 2;
    int startI = -1, startJ = -1;

    while (true)
    {
        for (int i = 1; i <= n - squareSize + 1; ++i)
        {
            for (int j = 1; j <= n - squareSize + 1; ++j)
            {
                if (!(exitCoordinate.first >= i && exitCoordinate.first < i + squareSize &&
                      exitCoordinate.second >= j && exitCoordinate.second < j + squareSize))
                    continue;

                for (auto &p : playerCoordinates)
                {
                    if (p.first >= i && p.first < i + squareSize &&
                        p.second >= j && p.second < j + squareSize)
                    {
                        startI = i;
                        startJ = j;
                        goto FOUND;
                    }
                }
            }
        }
        squareSize++;
    }
FOUND:

    vector<vector<int>> newMap = map;

    // 임시 저장용: 플레이어 회전 대상자
    vector<pair<int, int>> newPlayers;
    for (auto &p : playerCoordinates)
    {
        if (p.first >= startI && p.first < startI + squareSize &&
            p.second >= startJ && p.second < startJ + squareSize)
        {
            int localI = p.first - startI;
            int localJ = p.second - startJ;
            int newI = startI + localJ;
            int newJ = startJ + squareSize - 1 - localI;
            newPlayers.push_back({newI, newJ});
        }
    }

    // 출구 회전
    if (exitCoordinate.first >= startI && exitCoordinate.first < startI + squareSize &&
        exitCoordinate.second >= startJ && exitCoordinate.second < startJ + squareSize)
    {
        int localI = exitCoordinate.first - startI;
        int localJ = exitCoordinate.second - startJ;
        int newI = startI + localJ;
        int newJ = startJ + squareSize - 1 - localI;
        exitCoordinate = {newI, newJ};
    }

    // 내구도 회전 및 감소
    for (int i = 0; i < squareSize; ++i)
    {
        for (int j = 0; j < squareSize; ++j)
        {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + j;
            int newJ = startJ + squareSize - 1 - i;

            int durability = map[oldI][oldJ];
            if (durability >= 1 && durability <= 9)
                durability--;

            newMap[newI][newJ] = durability;
        }
    }

    // map 갱신
    map = newMap;

    // playerCoordinates 갱신
    vector<pair<int, int>> updated;
    for (auto &p : playerCoordinates)
    {
        if (p.first >= startI && p.first < startI + squareSize &&
            p.second >= startJ && p.second < startJ + squareSize)
        {
            updated.push_back(newPlayers.back());
            newPlayers.pop_back();
        }
        else
        {
            updated.push_back(p);
        }
    }
    playerCoordinates = updated;
}
