#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int t, p, r, c;
vector<vector<int>> map;
vector<vector<int>> rotateInfo;
pair<int, int> ratCoordinate;
int globalTime = 0;
int iNums[4][2] = {{-1, 0}, {-1, 0}, {1, 0}, {1, 0}};
int jNums[4][2] = {{0, 1}, {0, -1}, {0, 1}, {0, -1}};

typedef struct s_cheeseInfo
{
    int i, j;
    int tastyness;

    s_cheeseInfo(int i_, int j_, int tastyness_): i(i_), j(j_), tastyness(tastyness_) {}

    bool operator<(const s_cheeseInfo &newNode) const
    {
        int thisDistance = abs(this->i - ratCoordinate.first) + abs(this->j - ratCoordinate.second);
        int newDistance = abs(newNode.i - ratCoordinate.first) + abs(newNode.i - ratCoordinate.second);

        if (thisDistance != newDistance)
            return (thisDistance > newDistance);
        if ((this->i + this->j) != (newNode.i + newNode.j))
            return ((this->i + this->j) < (newNode.i + newNode.j));
        if (this->i != newNode.i)
            return (this->i < newNode.i);
        return (this->j < newNode.j);
    }
} t_cheeseInfo;

typedef struct s_nextCoor
{
    int i, j;
    int startI, startJ;

    s_nextCoor(int i_, int j_, int startI_, int startJ_) : i(i_), j(j_), startI(startI_), startJ(startJ_) {}

} t_nextCoor;

void input(void);

pair<int, int> getDirCoor(int dir)
{
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(p * r, vector<bool>(p * c, 0));

    pair<int, int> firstNode = {ratCoordinate.first, ratCoordinate.second};
    q.push(firstNode);
    visited[ratCoordinate.first][ratCoordinate.second] = true;

    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();

        if (map[poppedNode.first][poppedNode.second] > 0)
            return (make_pair(poppedNode.first, poppedNode.second));
        
        for (int index = 0; index < 2; index++)
        {
            int newI = poppedNode.first + iNums[dir][index];
            int newJ = poppedNode.second + jNums[dir][index];

            if (newI < 0 || newI >= (p * r) || newJ < 0 || newJ >= (p * c)) continue;
            if (visited[newI][newJ]) continue;
            if (map[newI][newJ] == -1) continue;

            visited[newI][newJ] = true;
            q.push(make_pair(newI, newJ));
        }
    }
    return (make_pair(-1, -1));
}

pair<int, int> chooseCheese(void)
{
    priority_queue<t_cheeseInfo> pq;

    for (int dir = 0; dir < 4; dir++)
    {
        pair<int, int> tmpCoor = getDirCoor(dir);
        if (tmpCoor.first == -1 && tmpCoor.second == -1)
            continue;
        t_cheeseInfo tmpInfo = {tmpCoor.first, tmpCoor.second, map[tmpCoor.first][tmpCoor.second]};
        pq.push(tmpInfo);
    }
    if (pq.empty())
        return (make_pair(-1, -1));
    return (make_pair(pq.top().i, pq.top().j));
}

pair<int, int> getNextCoor(pair<int, int> chosenCheese)
{
    int iNum[4] = {-1, 1, 0, 0};
    int jNum[4] = {0, 0, -1, 1};

    vector<vector<bool>> visited(p * r, vector<bool>(p * c, 0));
    queue<t_nextCoor> q;
    visited[ratCoordinate.first][ratCoordinate.second] = true;

    for (int index = 0; index < 4; index++)
    {
        int newI = ratCoordinate.first + iNum[index];
        int newJ = ratCoordinate.second + jNum[index];

        visited[newI][newJ] = true;
        t_nextCoor newNode = {newI, newJ, newI, newJ};
        q.push(newNode);
    }

    while (!q.empty())
    {
        t_nextCoor poppedNode = q.front();
        q.pop();

        if (poppedNode.i == chosenCheese.first && poppedNode.j == chosenCheese.second)
            return (make_pair(poppedNode.startI, poppedNode.startJ));

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.i + iNum[index];
            int newJ = poppedNode.j + jNum[index];

            if (newI < 0 || newI >= (p * r) || newJ < 0 || newJ >= (p * c)) continue;
            if (visited[newI][newJ]) continue;
            if (map[newI][newJ] == -1) continue;

            t_nextCoor nextNode = {newI, newJ, poppedNode.startI, poppedNode.startJ};
            q.push(nextNode);
        }
    }
    return (make_pair(-1, -1));
}

void moveRat(pair<int, int> chosenCheese)
{
    if (chosenCheese.first == -1 && chosenCheese.second == -1)
        return ;

    pair<int, int> nextCoor = getNextCoor(chosenCheese);
    if (nextCoor.first == -1 && nextCoor.second == -1)
        return;
    
    map[nextCoor.first][nextCoor.second] = 0;
    ratCoordinate = nextCoor;
}

void rotateCertainMap(int startI, int startJ)
{
    vector<vector<int>> newMap(map);
    pair<int, int> newRatCoor = ratCoordinate;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + j;
            int newJ = startJ + (p - 1) - i;
            newMap[newI][newJ] = map[oldI][oldJ];

            if (oldI == ratCoordinate.first && oldJ == ratCoordinate.second)
                newRatCoor = make_pair(newI, newJ);
        }
    }

    map = newMap;
    ratCoordinate = newRatCoor;
}

void rotateMap()
{
    for (int bigI = 0; bigI < r; bigI++)
    {
        for (int bigJ = 0; bigJ < c; bigJ++)
        {
            if (globalTime % rotateInfo[bigI][bigJ] == 0)
                rotateCertainMap(bigI * p, bigJ * p);
        }
    }
}

int main(void)
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int k;
    cin >> k;


    for (int testCase = 1; testCase <= k; testCase++)
    {
        input();
        cout << "#" << testCase << " ";
        for (int time = 0; time < t; time++)
        {
            pair<int, int> chosenCheese = chooseCheese();
            moveRat(chosenCheese);
            rotateMap();
            globalTime++;
            cout << ratCoordinate.first << " " << ratCoordinate.second;
        }
        cout << "\n";
    }
}

void input(void)
{
    globalTime = 1;
    cin >> t >> p >> r >> c;

    map.resize(p * r, vector<int>(p * c, 0));
    rotateInfo.resize(r, vector<int>(c, 0));

    for (int i = 0; i < p * r; i++)
    {
        for (int j = 0; j < p * c; j++)
            cin >> map[i][j];
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cin >> rotateInfo[i][j];
    }

    cin >> ratCoordinate.first >> ratCoordinate.second;
}

/*
1
1 2 2 2 
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 6
4 4
4 4
1 1
*/