#include <iostream>
#include <queue>
#include <string>

using namespace std;

int n, m, k;
int map[1000][1000];
bool visited[1000][1000][10] = {0, };
int iNum[4] = {1, -1, 0, 0};
int jNum[4] = {0, 0, 1, -1};

enum time_e {DAY = 0, NIGHT = 1};

typedef struct node
{
    int i;
    int j;
    int k; //뚫고 갈 수 있는 벽 개수
    int mvCount;
    bool time;
} t_node;

int bfs()
{
    queue<t_node> q;

    t_node firstNode = {0, 0, k, 1, DAY};
    q.push(firstNode);
    visited[0][0][0] = true;

    while (!q.empty())
    {
        t_node poppedNode = q.front();
        q.pop();

        if (poppedNode.i == n - 1 && poppedNode.j == m - 1)
            return (poppedNode.mvCount);

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.i + iNum[index];
            int newJ = poppedNode.j + jNum[index];

            if (newI < 0 || newI >= n || newJ < 0 || newJ >= m || visited[newI][newJ][k - poppedNode.k])
                continue;

            if (map[newI][newJ] == 1 && poppedNode.k > 0)
            {
                if (poppedNode.time == DAY)
                {
                    t_node crushedWallNode = {newI, newJ, poppedNode.k - 1, poppedNode.mvCount + 1, !poppedNode.time};
                    q.push(crushedWallNode);
                    visited[newI][newJ][k - crushedWallNode.k] = true;
                }
                else if (poppedNode.time == NIGHT)
                {
                    t_node crushedWallNode = {poppedNode.i, poppedNode.j, poppedNode.k, poppedNode.mvCount + 1, !poppedNode.time};
                    q.push(crushedWallNode); 
                }
            }
            else if (map[newI][newJ] == 0)
            {
                t_node justPassingNode = {newI, newJ, poppedNode.k, poppedNode.mvCount + 1, !poppedNode.time};
                q.push(justPassingNode);
                visited[newI][newJ][k - justPassingNode.k] = true;
            }
        }
    }
    return (-1);
}

int main(void)
{
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++)
            map[i][j] = tmp[j] - '0';
    }

    cout << bfs() << endl;
}