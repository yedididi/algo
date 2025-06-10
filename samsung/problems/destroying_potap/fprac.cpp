#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void input(void);
void printMap();

typedef struct s_node
{
    int i, j;
    int attackPoint;
    int lastAttackTime;
    int lastAttackedTime;

    s_node(int i_, int j_, int attackPoint_, int lastAttackTime_, int lastAttackedTime_) : i(i_), j(j_), attackPoint(attackPoint_), lastAttackTime(lastAttackTime_), lastAttackedTime(lastAttackedTime_) {}

    bool operator<(const s_node newNode) const
    {
        if (this->attackPoint != newNode.attackPoint)
            return (this->attackPoint > newNode.attackPoint);
        if (this->lastAttackTime != newNode.lastAttackTime)
            return (this->lastAttackTime < newNode.lastAttackTime);
        if ((this->i + this->j) != (newNode.i + newNode.j))
            return ((this->i + this->j) < (newNode.i + newNode.j));
        return (this->i < newNode.i);
    }
} t_node;

struct maxComp
{    
    bool operator()(const s_node a, const s_node b) const
    {
        if (a.attackPoint != b.attackPoint)
            return (a.attackPoint < b.attackPoint);
        if (a.lastAttackTime != b.lastAttackTime)
            return (a.lastAttackTime > b.lastAttackTime);
        if ((a.i + a.j) != (b.i + b.j))
            return ((a.i + a.j) > (b.i + b.j));
        return (a.i > b.i);
    }
};

typedef struct s_laserNode
{
    int i, j;
    int beforeI, beforeJ;
} t_laserNode;

int n, m, k, globalTime;
int minimumAttackPoint = INT_MAX, maximumAttackPoint = INT_MIN;
int potapNum = 0;
int iNum[4] = {0, 1, 0, -1};
int jNum[4] = {1, 0, -1, 0};
vector<vector<t_node>> map;

pair<int, int> chooseAttacker(void)
{
    priority_queue<t_node> pq;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint == minimumAttackPoint)
                pq.push(map[i][j]);
        }   
    }
    pair<int, int> attacker = make_pair(pq.top().i, pq.top().j);
    map[attacker.first][attacker.second].attackPoint += (n + m);
    return (attacker);
}

pair<int, int> chooseAttackee(void)
{
    priority_queue<t_node, vector<t_node>, maxComp> pq;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint == maximumAttackPoint)
                pq.push(map[i][j]);
        }
    }

    pair<int, int> attackee = make_pair(pq.top().i, pq.top().j);
    return (attackee);
}

bool tryLaserAttack(pair<int, int> attacker, pair<int, int> attackee)
{
    queue<pair<int, int>> q;
    pair<int, int> firstNode = {attacker.first, attacker.second};
    vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, 0));
    pair<int, int> parent[n][m];

    visited[attacker.first][attacker.second] = true;
    q.push(firstNode);
    parent[attacker.first][attacker.second] = make_pair(-1, -1);


    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();

        if (poppedNode.first == attackee.first && poppedNode.second == attackee.second)
        {
            //attacker까지 최단경로로 도달함, 이제 공격!
            map[attackee.first][attackee.second].attackPoint -= map[attacker.first][attacker.second].attackPoint;
            map[attackee.first][attackee.second].lastAttackedTime = globalTime;

            int currentI = parent[attackee.first][attackee.second].first;
            int currentJ = parent[attackee.first][attackee.second].second;

            map[attacker.first][attacker.second].lastAttackTime = globalTime;
            // cout << "attackee.first: " << attackee.first << ", attackee.second: " << attackee.second << "\n";
            // cout << "attacker.first: " << attacker.first << ", attacker.second: " << attacker.second << "\n";
            // cout << "start coordinates:" << attackee.first << ", " << attackee.second << "\n";
            
            while (1)
            {
                // cout << "\n*****INSIDE WHILE*********, currentI:" << currentI << ", currentJ:" << currentJ;
                map[currentI][currentJ].lastAttackedTime = globalTime;
                // cout << ", lastAttackedTime: " << map[currentI][currentJ].lastAttackedTime << "\n";

                if (currentI == attacker.first && currentJ == attacker.second)
                    break;

                map[currentI][currentJ].attackPoint -= (map[attacker.first][attacker.second].attackPoint / 2);

                int tmpCurrentI = parent[currentI][currentJ].first;
                int tmpCurrentJ = parent[currentI][currentJ].second;

                if (tmpCurrentI == -1 && tmpCurrentJ == -1)
                    break;
                
                currentI = tmpCurrentI;
                currentJ = tmpCurrentJ;
            }
            return (true);
        }

        for (int index = 0; index < 4; index++)
        {
            int newI = (poppedNode.first + iNum[index] + n) % n;
            int newJ = (poppedNode.second + jNum[index] + m) % m;

            if (map[newI][newJ].attackPoint <= 0) continue;
            if (visited[newI][newJ]) continue;
            
            pair<int, int> newNode = {newI, newJ};
            q.push(newNode);
            visited[newI][newJ] = true;
            parent[newI][newJ] = poppedNode;
        }
    }
    return (false);
}

void attack(void)
{
    int iNum[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int jNum[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    pair<int, int> attacker = chooseAttacker();
    pair<int, int> attackee = chooseAttackee();

    // cout << "\nafter choosing\n";
    // printMap();


    if (tryLaserAttack(attacker, attackee) == true)
        return;

    map[attackee.first][attackee.second].attackPoint -= map[attacker.first][attacker.second].attackPoint;
    map[attackee.first][attackee.second].lastAttackedTime = globalTime;
    
    map[attacker.first][attacker.second].lastAttackTime = globalTime;

    for (int index = 0; index < 8; index++)
    {
        int newI = (attackee.first + iNum[index] + n) % n;
        int newJ = (attackee.second + jNum[index] + m) % m;

        if (map[newI][newJ].attackPoint > 0)
        {
            map[newI][newJ].attackPoint -= (map[attacker.first][attacker.second].attackPoint / 2);
            map[newI][newJ].lastAttackedTime = globalTime;
        }
    }
    // cout << "didn't attack with laser\n";
}

void fix(void)
{
    maximumAttackPoint = INT_MIN;
    minimumAttackPoint = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint <= 0)
            {
                map[i][j].attackPoint = 0;
                continue;
            }
            
            if (map[i][j].lastAttackedTime != globalTime && map[i][j].lastAttackTime != globalTime)
                map[i][j].attackPoint++;
            
            maximumAttackPoint = max(maximumAttackPoint, map[i][j].attackPoint);
            minimumAttackPoint = min(minimumAttackPoint, map[i][j].attackPoint);
        }
    }
}

void printBiggestAttackPoint(void)
{
    maximumAttackPoint = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint > 0)
                maximumAttackPoint = max(maximumAttackPoint, map[i][j].attackPoint);
        }
    }
    cout << maximumAttackPoint << endl;
}

int main(void)
{
    input();

    for (int time = 1; time <= k; time++)
    {
        globalTime = time;
        attack();

        // cout << "\nafter attack\n";
        // printMap();

        if (potapNum == 1)
            break;

        fix();

        // cout << "\nafter fix\n";
        // printMap();
    }
    printBiggestAttackPoint();
}

void input(void)
{
    cin >> n >> m >> k;

    t_node initialNode = {0, 0, 0, 0, 0};

    map.resize(n + 1, vector<t_node>(m + 1, initialNode));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int tmp;
            cin >> tmp;

            if (tmp > 0)
                potapNum++;
            maximumAttackPoint = max(maximumAttackPoint, tmp);
            if (tmp != 0)
                minimumAttackPoint = min(minimumAttackPoint, tmp);
            map[i][j] = {i, j, tmp, 0, 0};
        }
    }
}

void printMap()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j].attackPoint << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}