#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int map[130][130];

typedef struct s_node 
{
    int i;
    int j;
    int sum;

    s_node(int newI, int newJ, int newSum): i(newI), j(newJ), sum(newSum) {}

    bool operator<(const s_node &other) const
    {
        return (this->sum > other.sum);
    }
} t_node;

int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};
bool visited[130][130];
int newMap[130][130];

void dist()
{
    priority_queue<t_node> pq;

    t_node firstNode(0, 0, map[0][0]);
    pq.push(firstNode);

    while (!pq.empty())
    {
        t_node poppedNode = pq.top();
        pq.pop();

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.i + iNum[index];
            int newJ = poppedNode.j + jNum[index];

            if (newI < 0 || newI >= n || newJ < 0 || newJ >= n || visited[newI][newJ])
                continue;
            if (newMap[newI][newJ] <= poppedNode.sum + map[newI][newJ])
                continue;
            
            newMap[newI][newJ] = poppedNode.sum + map[newI][newJ];
            t_node newNode(newI, newJ, poppedNode.sum + map[newI][newJ]);
            pq.push(newNode);
        }
    }
}
void printMinNum(int num)
{
    dist();
    cout << "Problem " << num << ": " << newMap[n - 1][n - 1] << endl;
}

int main(void)
{
    int num = 1;

    while (1)
    {
        cin >> n;

        if (n == 0) break;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j]; 
                visited[i][j] = false;
                newMap[i][j] = 2147483647;
            }
        }

        printMinNum(num);
        num++;
    }
}