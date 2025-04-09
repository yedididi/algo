#include <iostream>
#include <queue>

using namespace std;

int n, m, goalI, goalJ;
int map[1000][1000];
int answer[1000][1000] = {-1, };
bool visited[1000][1000] = {0, };
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};

typedef struct s_node
{
    int i;
    int j;
    int distance;
} t_node;

void bfs()
{
    queue<t_node> q;
    t_node firstNode = {goalI, goalJ, 0};
    q.push(firstNode);
    visited[goalI][goalJ] = true;

    while (!q.empty())
    {
        t_node poppedNode = q.front();
        q.pop();
        answer[poppedNode.i][poppedNode.j] = poppedNode.distance;

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.i + iNum[index];
            int newJ = poppedNode.j + jNum[index];

            if (newI < 0 || newI > n || newJ < 0 || newJ > m || visited[newI][newJ])
                continue;

            if (map[newI][newJ] == 0)
                answer[newI][newJ] = 0;
            else
            {
                t_node newNode = {newI, newJ, poppedNode.distance + 1};
                q.push(newNode);
            }
            visited[newI][newJ] = true;
        }
    }
}

void printMaps()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == 0)
                cout << "0 ";
            else
                cout << answer[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(void)
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 2)
            {
                goalI = i;
                goalJ = j;
            }
            answer[i][j] = -1;
        }
    }

    bfs();
    printMaps();
}

