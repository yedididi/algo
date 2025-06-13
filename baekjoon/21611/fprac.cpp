#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> map;
vector<pair<int, int>> attackInfo;

void input(void);
void printMap(void);

int n, m;
vector<pair<int, int>> coordinates;
int iNum[4] = {0, 1, 0, -1};
int jNum[4] = {-1, 0, 1, 0};
int explodeCount[4] = {0, 0, 0, 0};

void fillCoordinates(void)
{
    int curI = n / 2;
    int curJ = n / 2;
    int level = 1;

    while (1)
    {
        for (int index = 0; index < 4; index++)
        {
            for (int repeat = 0; repeat < level; repeat++)
            {
                int newI = curI + iNum[index];
                int newJ = curJ + jNum[index];
                coordinates.push_back(make_pair(newI, newJ));
                curI = newI;
                curJ = newJ;
                if (curI == 0 && curJ == 0)
                    return;
            }
            if (index == 1 || index == 3)
                level++;
        }
    }
}

void moveMarbles(void)
{
    queue<int> marbles;
    vector<vector<int>> newMap(n, vector<int>(n, 0));
    
    for (pair<int, int> coord : coordinates)
    {
        if (map[coord.first][coord.second] != 0)
        {
            marbles.push(map[coord.first][coord.second]);
        }
    }
    for (pair<int, int> coord : coordinates)
    {
        if (marbles.empty())
            break;
        newMap[coord.first][coord.second] = marbles.front();
        marbles.pop();
    }
    map = newMap;
}

void blizzardAttack(int direction, int distance)
{
    int attackINum[5] = {100, -1, 1, 0, 0};
    int attackJNum[5] = {100, 0, 0, -1, 1};
    int newI = n / 2;
    int newJ = n / 2;

    for (int i = 0; i < distance; i++)
    {
        newI = newI + attackINum[direction];
        newJ = newJ + attackJNum[direction];

        if (newI < 0 || newJ < 0 || newI >= n || newJ >= n) break; //necessary?

        map[newI][newJ] = 0;
    }
    // cout << "after shooting" << endl;
    // printMap();
    moveMarbles();
}

void explodeMarbles(void)
{
    queue<pair<int, int>> sameMarbles;
    int marbleName = 0;
    int marbleCount = 0;
    bool didItExplode = false;
    
    for (pair<int, int> coord : coordinates)
    {
        if (map[coord.first][coord.second] == 0)
            continue;
        
        if (map[coord.first][coord.second] == marbleName)
        {
            sameMarbles.push(make_pair(coord.first, coord.second));
            marbleCount++;
        }
        else
        {
            if (marbleCount >= 4)
            {
                while (!sameMarbles.empty())
                {
                    map[sameMarbles.front().first][sameMarbles.front().second] = 0;
                    sameMarbles.pop();
                }
                didItExplode = true;
                explodeCount[marbleName] += marbleCount;
            }

            std::queue<pair<int, int>> empty;
            sameMarbles.swap(empty);
            marbleName = map[coord.first][coord.second];
            marbleCount = 1;
            sameMarbles.push(make_pair(coord.first, coord.second));
        }
    }

    if (marbleCount >= 4)
    {
        while (!sameMarbles.empty())
        {
            map[sameMarbles.front().first][sameMarbles.front().second] = 0;
            sameMarbles.pop();
        }
        didItExplode = true;
        explodeCount[marbleName] += marbleCount;
    }

    // cout << "\nafter one explosion" << endl;
    // printMap();
    if (didItExplode == true)
    {
        moveMarbles();
        explodeMarbles();
    }
    else
        return ;
}

void changeMarbles(void)
{
    vector<vector<int>> newMap(n, vector<int>(n, 0));
    queue<int> newMarbles;
    int marbleName = map[coordinates[0].first][coordinates[0].second];
    int marbleCount = 0;
    
    for (pair<int, int> coord : coordinates)
    {
        // cout << "coord: " << coord.first << ", " << coord.second << endl;
        if (map[coord.first][coord.second] == 0)
            continue;
        
        if (map[coord.first][coord.second] == marbleName)
            marbleCount++;
        else
        {
            newMarbles.push(marbleCount);
            newMarbles.push(marbleName);
            marbleName = map[coord.first][coord.second];
            marbleCount = 1;
        }
    }

    if (marbleCount > 0)
    {
        newMarbles.push(marbleCount);
        newMarbles.push(marbleName);
    }

    for (pair<int, int> coord : coordinates)
    {
        if (newMarbles.empty())
            break;
        newMap[coord.first][coord.second] = newMarbles.front();
        newMarbles.pop();
    }
    map = newMap;
}

int main(void)
{
    input();
    fillCoordinates();
    int num = 1;

    for (auto itr = attackInfo.begin(); itr != attackInfo.end(); itr++)
    {
        // cout << "\nno." << num++ << endl;
        blizzardAttack(itr->first, itr->second);
        // cout << "after blizzard attack" << endl;
        // printMap();
        explodeMarbles();
        // cout << "after explode marbles" << endl;
        // printMap();
        changeMarbles();
        // cout << "after change marbles" << endl;
        // printMap();
    }

    cout << explodeCount[1] + 2 * explodeCount[2] + 3 * explodeCount[3] << endl;
}

void input(void)
{
    cin >> n >> m;
    map.resize(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        attackInfo.push_back(make_pair(a, b));
    }
}

void printMap(void)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}