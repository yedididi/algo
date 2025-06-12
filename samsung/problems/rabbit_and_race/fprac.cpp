#include <iostream>
#include <unordered_map>
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
    int minusValue;

    s_rabbitInfo(int i_ = 0, int j_ = 0, int jumpCount_ = 0, int pid_ = 0, int mvDistance_ = 0, int score_ = 0, int lastJumpTime_ = 0, int minusValue_ = 0)
        : i(i_), j(j_), jumpCount(jumpCount_), pid(pid_), mvDistance(mvDistance_), score(score_), lastJumpTime(lastJumpTime_), minusValue(minusValue_) {}

    bool operator<(const s_rabbitInfo &newInfo) const
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
        if ((a.i + a.j) != (b.i + b.j))
            return ((a.i + a.j) < (b.i + b.j));
        if (a.i != b.i)
            return (a.i < b.i);
        if (a.j != b.j)
            return (a.j < b.j);
        return (a.pid < b.pid);
    }
};

int totalNum, hundred, n, m, p;
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};
unordered_map<int, t_rabbitIinfo> rabbitInfo;
int globalTime = 0;
int minusValue = 0;
    priority_queue<t_rabbitIinfo> pq;

int fillPQ(void)
{
    for (const auto &entry : rabbitInfo)
    {
        pq.push(entry.second);
    }
    return (pq.top().pid);
}

int chooseFinalRabbit(void)
{
    priority_queue<t_rabbitIinfo, vector<t_rabbitIinfo>, reverseComp> pq_final;

    for (const auto &entry : rabbitInfo)
    {
        if (entry.second.lastJumpTime == globalTime)
            pq_final.push(entry.second);
    }
    return (pq_final.top().pid);
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
        int pid = pq.top().pid;
        t_rabbitIinfo &chosenRabbit = rabbitInfo[pid];
        pq.pop();

        pair<int, int> finalCoordinate = {-1, -1};

        for (int index = 0; index < 4; index++)
        {
            pair<int, int> newCoordinate = moveRabbits(chosenRabbit.i, chosenRabbit.j, iNum[index], jNum[index], chosenRabbit.mvDistance);

            if ((newCoordinate.first + newCoordinate.second) != (finalCoordinate.first + finalCoordinate.second))
            {
                if ((newCoordinate.first + newCoordinate.second) > (finalCoordinate.first + finalCoordinate.second))
                    finalCoordinate = newCoordinate;
            }
            else if ((newCoordinate.first != finalCoordinate.first))
            {
                if ((newCoordinate.first > finalCoordinate.first))
                    finalCoordinate = newCoordinate;
            }
            else if (newCoordinate.second != finalCoordinate.second)
            {
                if (newCoordinate.second > finalCoordinate.second)
                    finalCoordinate = newCoordinate;
            }
        }

        chosenRabbit.i = finalCoordinate.first;
        chosenRabbit.j = finalCoordinate.second;
        chosenRabbit.score -= (finalCoordinate.first + finalCoordinate.second + 2);
        minusValue += (finalCoordinate.first + finalCoordinate.second + 2);
        chosenRabbit.jumpCount++;
        chosenRabbit.lastJumpTime = globalTime;
        pq.push(chosenRabbit);
        // cout << "chosenRabbit: " << chosenRabbit.pid << " at (" << chosenRabbit.i << ", " << chosenRabbit.j << "), score is " << chosenRabbit.score + minusValue << endl;
    }

    int finalPid = chooseFinalRabbit();
    rabbitInfo[finalPid].score += s;
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

    for (const auto &entry : rabbitInfo)
    {
        if (entry.second.score + minusValue > maxScore)
            maxScore = entry.second.score + minusValue;
        // cout << "Rabbit " << entry.second.pid << " has score: " << entry.second.score + minusValue << endl;
    }
    cout << maxScore << endl;
}

int main(void)
{
    input();
    fillPQ();

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
    cin >> totalNum >> hundred >> n >> m >> p;

    for (int i = 0; i < p; i++)
    {
        int pid, distance;
        cin >> pid >> distance;
        rabbitInfo[pid] = {0, 0, 0, pid, distance, 0, 0, 0};
    }
}
