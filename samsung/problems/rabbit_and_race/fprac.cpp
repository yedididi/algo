#include <iostream>
#include <vector>

using namespace std;

void input(void);

typedef struct s_rabbitInfo
{
    int i, j;
    int jumpCount;
    int pid;
    int mvDistance;
    int score;
} t_rabbitIinfo;

int n, m, p;
vector<t_rabbitIinfo> rabbitInfo;



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
    }
    printBiggestScore();
}

void input(void)
{
    cin >> n >> m >> p;
    t_rabbitIinfo sampleInfo = {0, 0, 0, 0, 0, 0};
    rabbitInfo.resize(p, sampleInfo);

    for (int i = 0; i < p; i++)
    {
        int pid, distance;
        cin >> pid >> distance;
        rabbitInfo[pid] = {0, 0, 0, pid, distance, 0};
    }
}