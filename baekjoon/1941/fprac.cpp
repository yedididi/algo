#include <iostream>
#include <string>
#include <queue>

using namespace std;

char map[5][5] = {0,};
int totalNum = 0;
int princess[7] = {0, };
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};

typedef struct s_node 
{
    int i;
    int j;
    int depth;
} t_node;

void input()
{
    for (int i = 0; i < 5; i++)
    {
        string tmp;
        cin >> tmp; 
        for (int j = 0; j < 5; j++)
            map[i][j] = tmp[j];
    }
}

int numToTeam(int i)
{
    return (map[i / 5][i % 5]);
}

bool isSomBigger()
{
    int som = 0;

    for (int i = 0; i < 7; i++)
    {
        if (numToTeam(princess[i]) == 'S')
            som++;
    }

    if (som >= 4)
        return (true);
    return (false);
}

bool isConnected()
{
    bool connectMap[5][5] = {0,};
    bool visited[5][5] = {0,};
    int connectedNum = 0;

    for (int i = 0; i < 7; i++)
    {
        connectMap[princess[i] / 5][princess[i] % 5] = true; 
    }

    queue<t_node> q;
    t_node firstNode = {princess[0] / 5, princess[0] % 5, 0};
    q.push(firstNode);

    while (!q.empty())
    {
        t_node poppedNode = q.front();
        q.pop();

        if (connectedNum == 7)
            return (true);

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.i + iNum[index];
            int newJ = poppedNode.j + jNum[index];

            if (newI < 0 || newI >= 5 || newJ < 0 || newJ >= 5)
                continue;

            if (visited[newI][newJ])
                continue;

            if (connectMap[newI][newJ])
            {
                connectedNum++;
                visited[newI][newJ] = true;
                t_node newNode = {newI, newJ, poppedNode.depth + 1};
                q.push(newNode);
            }
        }
    }
    return (false);
}


void getSeven(int depth, int num)
{
    if (depth == 7)
    {
        if (isSomBigger() && isConnected())
            totalNum++;
        return;
    }

    for (int i = num; i < 25; i++)
    {
        princess[depth] = i;
        getSeven(depth + 1, i + 1);
    }
}

int main(void)
{
    input();

    getSeven(0, 0);
    cout << totalNum << endl;
}
