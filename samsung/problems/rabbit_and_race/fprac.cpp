#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void input(void);

typedef struct s_rabbitInfo
{
    int i, j;
    int jumpCount;
    int pid;
    int mvDistance;
    int score;
    int lastJumpTime;

    s_rabbitInfo(int i_, int j_, int jumpCount_, int pid_, int mvDistance_, int score_, int lastJumpTime_) : i(i_), j(j_), jumpCount(jumpCount_), pid(pid_), mvDistance(mvDistance_), score(score_), lastJumpTime(lastJumpTime_) {}

    bool operator<(const s_rabbitInfo &newInfo)
    {
        if (this->jumpCount != newInfo.jumpCount)
            return (this->jumpCount > newInfo.jumpCount);
        if ((this->i + this->j) != (newInfo.i + newInfo.j))
            return ((this->i + this->j) > (newInfo.i + newInfo.j));
        if (this->i != newInfo.i)
            return (this->i > newInfo.i);
        if (this->j != newInfo.j)
            return (this->j > newInfo.j);
        return (this->pid > newInfo.pid);
    }
} t_rabbitIinfo;

struct reverseComp
{
    bool operator()(const s_rabbitInfo &a, const s_rabbitInfo &b) const
    {
        if (a.jumpCount != b.jumpCount)
            return (a.jumpCount < b.jumpCount);
        if ((a.i + a.j) != (b.i + b.j))
            return ((a.i + a.j) < (b.i + b.j));
        if (a.i != b.i)
            return (a.i < b.i);
        if (a.j != b.j)
            return (a.j < b.j);
        return (a.pid < b.pid);
    }
};

int n, m, p;
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};
vector<t_rabbitIinfo> rabbitInfo;
int globalTime = 0;

int chooseRabbit(void)
{
    priority_queue<t_rabbitIinfo> pq;

    for (vector<t_rabbitIinfo>::iterator itr = rabbitInfo.begin(); itr != rabbitInfo.end(); itr++)
    {
        pq.push(*itr);
    }
    return (pq.top().pid);
}

int chooseFinalRabbit(void)
{
    priority_queue<t_rabbitIinfo, vector<t_rabbitIinfo>, reverseComp> pq;

    for (auto itr = rabbitInfo.begin(); itr != rabbitInfo.end(); itr++)
    {
        if (itr->lastJumpTime == globalTime)
            pq.push(*itr);
    }
    return (pq.top().pid);
}

pair<int, int> moveRabbits(int oldI, int oldJ, int iNum_, int jNum_, int mvDistance)
{
    int newI, newJ;

    if (iNum_ == 1) // down
    {
        mvDistance = mvDistance % (2 * (n - 1));
        if (mvDistance + oldI < n)
            newI = mvDistance + oldI;
        else if ((2 * n) - 2 - mvDistance - oldI < n)
            newI = (2 * n) - 2 - mvDistance - oldI;
        else
            newI = mvDistance + oldI - (2 * n) + 2;
        return (make_pair(newI, oldJ));
    }
    else if (iNum_ == -1) //up
    {
        mvDistance = mvDistance % (2 * (n - 1));
        if (oldI - mvDistance >= 0)
            newI = oldI - mvDistance;
        else if (mvDistance - oldI < n)
            newI = mvDistance - oldI;
        else
            newI = (2 * n) - mvDistance - oldI - 2;
        return (make_pair(newI, oldJ));
    }
    else if (jNum_ == 1) //right
    {
        mvDistance = mvDistance % (2 * (m - 1));
        if (mvDistance + oldJ < m)
            newJ = mvDistance + oldJ;
        else if ((2 * m) - 2 - mvDistance - oldJ < m)
            newJ = (2 * m) - 2 - mvDistance - oldJ;
        else 
            newJ = mvDistance + oldJ - (2 * m) + 2;
        return (make_pair(oldI, newJ));
    }
    else if (jNum_ == -1) // left
    {
        mvDistance = mvDistance % (2 * (m - 1));
        if (oldJ - mvDistance >= 0)
            newJ = oldJ - mvDistance;
        else if (mvDistance - oldJ < m)
            newJ = mvDistance - oldJ;
        else
            newJ = (2 * m) - mvDistance + oldJ - 2;
        return (make_pair(oldI, newJ));
    }

    return (make_pair(-1, -1));
}

void startRace(void)
{
    int k, s;
    cin >> k >> s;

    for (int i = 0; i < k; i++)
    {
        t_rabbitIinfo chosenRabbit = rabbitInfo[chooseRabbit()];
        pair<int, int> finalCoordinate = {-1, -1};

        for (int index = 0; index < 4; index++)
        {
            pair<int, int> newCoordinate = moveRabbits(chosenRabbit.i, chosenRabbit.j, iNum[index], jNum[index], chosenRabbit.mvDistance);

            if ((newCoordinate.first + newCoordinate.second) > (finalCoordinate.first + finalCoordinate.second))
                finalCoordinate = newCoordinate;
            else if (newCoordinate.first > finalCoordinate.first)
                finalCoordinate = newCoordinate;
            else if (newCoordinate.second > finalCoordinate.second)
                finalCoordinate = newCoordinate;
        }
        chosenRabbit.i = finalCoordinate.first;
        chosenRabbit.j = finalCoordinate.second;
        chosenRabbit.score -= (finalCoordinate.first + finalCoordinate.second);
        chosenRabbit.lastJumpTime = globalTime;
    }
    t_rabbitIinfo finalChosenRabbit = rabbitInfo[chooseFinalRabbit()];
    finalChosenRabbit.score += s;
}

void changeDistance(void)
{
    int pid, l;
    cin >> pid >> l;

    rabbitInfo[pid].mvDistance *= l;
}

void printBiggestScore(void)
{
    int maxScore = INT_MIN;

    for (auto itr = rabbitInfo.begin(); itr != rabbitInfo.end(); itr++)
    {
        if (itr->score > maxScore)
            maxScore = itr->score;
    }
    cout << maxScore << endl;
}

int main(void)
{
    input();

    while (1)
    {
        int instructionNumber;
        cin >> instructionNumber;

        if (instructionNumber == 200)
            startRace();
        if (instructionNumber == 300)
            changeDistance();
        if (instructionNumber == 400)
            break;
        globalTime++;
    }
    printBiggestScore();
}

void input(void)
{
    cin >> n >> m >> p;
    t_rabbitIinfo sampleInfo = {0, 0, 0, 0, 0, 0, 0};
    rabbitInfo.resize(p, sampleInfo);

    for (int i = 0; i < p; i++)
    {
        int pid, distance;
        cin >> pid >> distance;
        rabbitInfo[pid] = {0, 0, 0, pid, distance, 0, 0};
    }
}