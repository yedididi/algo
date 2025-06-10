#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void input(void);

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

int n, m, k;
int minimumAttackPoint = INT_MAX, maximumAttackPoint = INT_MIN;
int potapNum = 0;
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

void attack(void)
{

}

void fix(void)
{

}

int main(void)
{
    input();

    for (int time = 0; time < k; time++)
    {
        pair<int, int> attacker = chooseAttacker();
        cout << "min: " << minimumAttackPoint << ", max:" << maximumAttackPoint << endl;
        cout << attacker.first << ", " << attacker.second << endl;
        // attack();
        // fix();

    }
}

void input(void)
{
    cin >> n >> m >> k;

    t_node initialNode = {0, 0, 0, 0, 0};

    map.resize(n, vector<t_node>(m, initialNode));

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
