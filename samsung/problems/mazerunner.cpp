#include <iostream>
#include <vector>

using namespace std;

int playerTotalCount;
pair<int, int> exitCoordinate;
vector<pair<int, int>> playerCoordinates;
vector<vector<int>> map(11, vector<int>(11, 0));
int totalMoveCount = 0;
int n, k;

void input(void);
void printMap(void);

void movePlayers(void)
{
    int iNum[4] = {0, 0, -1, 1};
    int jNum[4] = {-1, 1, 0, 0};

    for (int i = playerCoordinates.size() - 1; i >= 0; i--)
    {
        int oldI = playerCoordinates[i].first;
        int oldJ = playerCoordinates[i].second;
        int minimumToExit = abs(oldI - exitCoordinate.first) + abs(oldJ - exitCoordinate.second);
        pair<int, int> minimumCoorinate = {oldI, oldJ};

        for (int index = 0; index < 4; index++)
        {
            int newI = oldI + iNum[index];
            int newJ = oldJ + jNum[index];
            int distanceToExit = abs(newI - exitCoordinate.first) + abs(newJ - exitCoordinate.second);

            if (newI < 1 || newI > n || newJ < 1 || newJ > n)
                continue;
            if (map[newI][newJ] > 0 && map[newI][newJ] < 10)
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
            map[oldI][oldJ] = 0;
            playerTotalCount--;
            playerCoordinates.erase(playerCoordinates.begin() + i);
        }
        else
        {
            map[oldI][oldJ] = 0;
            playerCoordinates[i].first = minimumCoorinate.first;
            playerCoordinates[i].second = minimumCoorinate.second;
        }
    }

    for (int i = 0; i < playerCoordinates.size(); i++)
    {
        map[playerCoordinates[i].first][playerCoordinates[i].second] = 'P';
        totalMoveCount++;
    }
}

void rotateSquare(void)
{
    int startI = 0, startJ = 0;
    int squareSize = 2;

    while (1)
    {
        for (int i = exitCoordinate.first - (squareSize - 1); i < exitCoordinate.first; i++)
        {
            for (int j = exitCoordinate.second - (squareSize - 1); j < exitCoordinate.second; j++)
            {
                //이 정사각형 안에 참가자가 있는지 확인
                for (int playerNum = 0; playerNum < playerCoordinates.size(); playerNum++)
                {
                    if (playerCoordinates[playerNum].first >= i && playerCoordinates[playerNum].first <= (i + squareSize - 1) &&
                        playerCoordinates[playerNum].second >= j && playerCoordinates[playerNum].second <= (j + squareSize - 1))
                        {
                            startI = i;
                            startJ = j;
                            break;
                        }
                }
                if (startI != 0)
                    break;
            }
            if (startI != 0)
                break;
        }
        if (startI != 0)
            break;
        squareSize++;
    }

    cout << startI << ", " << startJ << ", " << squareSize << endl;
    vector<vector<int>> newMap(map);

    //rotate
    for (int i = startI; i < startI + squareSize; i++)
    {
        for (int j = startJ; j < startJ + squareSize; j++)
        {
            // newMap[startI + (j - startJ)][(startJ + squareSize - 1) - (i - startI)] = map[i][j];
            if (map[i][j] == 'E')
            {
                exitCoordinate.first = startI + (j - startJ);
                exitCoordinate.second = (startJ + squareSize - 1) - (i - startI);
                cout << "changed Exit coordinate is " <<  "(" << exitCoordinate.first << ", " << exitCoordinate.second << ")\n";
            }
            else if (map[i][j] == 'P')
            {
                for (vector<pair<int, int>>::iterator itr = playerCoordinates.begin(); itr != playerCoordinates.end(); itr++)
                {
                    if (itr->first == i && itr->second == j)
                    {
                        itr->first = startI + (j - startJ);
                        itr->second = (startJ + squareSize - 1) - (i - startI);

                        cout << "changed player coordinate is " <<  "(" << itr->first << ", " << itr->second << ")\n";
                    }
                }
            }
            else if (1 <= map[i][j] && map[i][j] <= 9)
            {
                map[i][j]--;
                cout << "changed num to " <<  map[i][j] << "\n";
            }
            newMap[startI + (j - startJ)][(startJ + squareSize - 1) - (i - startI)] = map[i][j];
        }
    }
    map = newMap;
}

int main(void)
{
    input();

    for (int time = 0; time < k; time++)
    {
        cout << "\ntime " << time << ", initial state:\n";
        printMap();

        movePlayers();

        cout << "\ntime " << time << ", after moving:\n";
        printMap();

        if (playerTotalCount == 0)
            break;
        rotateSquare();

        cout << "\ntime " << time << ", after rotate:\n";
        printMap();
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
            map[i][j] = tmp;
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

void printMap(void)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i][j] == 'E')
                cout << "E";
            else if (map[i][j] == 'P')
                cout << "P";
            else
                cout << map[i][j];
            cout << " ";
        }
        cout << "\n";
    }
}