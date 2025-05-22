#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m, start, endNum;
int almostMin = -1;

typedef struct s_node
{
    int nodeNum;
    int sum;

    s_node(int n, int s) : nodeNum(n), sum(s)
    {

    }

    bool operator<(const s_node n) const
    {
        return (this->sum > n.sum);
    }

} t_node;

typedef struct s_mapNode
{
    int nextNodeNum;
    int distance;
} t_mapNode;

int getAlmostMinDist(vector<vector<t_mapNode>> map)
{
    priority_queue<t_node> q;
    bool visited[endNum];

    memset(visited, 0, endNum);

    t_node firstNode = {start, 0};
    q.push(firstNode);

    // priority_queue<t_node> answers;
    while (!q.empty())
    {
        t_node poppedNode = q.top();
        q.pop();

        cout << "nodeNum is " << poppedNode.nodeNum << endl;
        if (poppedNode.nodeNum == endNum)
        {
            cout << "reached endNum, dist is " << poppedNode.sum << endl;
            if (almostMin == -1)
                almostMin = poppedNode.sum;
            else if (almostMin == poppedNode.sum)
                ;
            else
                return (poppedNode.sum);
            // answers.push(poppedNode);
        }

        for (int i = 0; i < map[poppedNode.nodeNum].size(); i++)
        {
            // if (visited[map[poppedNode.nodeNum][i].nextNodeNum] == true)
            //     continue;
            t_node newNode = {map[poppedNode.nodeNum][i].nextNodeNum, map[poppedNode.nodeNum][i].distance + poppedNode.sum};
            q.push(newNode);
            // visited[map[poppedNode.nodeNum][i].nextNodeNum] = true;
        }
    }
    
    // while (!answers.empty())
    // {
    //     t_node poppedNode = answers.top();
    //     answers.pop();

    //     if (almostMin == -1)
    //         almostMin = poppedNode.sum;
    //     else if (almostMin == poppedNode.sum)
    //         ;
    //     else if (almostMin != poppedNode.sum)
    //         return (poppedNode.sum);
    // }
    return (-1);
}

int main(void)
{
    vector<int> answer;
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        
        cin >> start >> endNum;
        vector<vector<t_mapNode>> map(n + 1);
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            map[a].push_back({b, c});
            // map[b].push_back({a, c});
        }
        answer.push_back(getAlmostMinDist(map));
        almostMin = -1;
    }
    for (auto itr = answer.begin(); itr != answer.end(); itr++)
        cout << *itr << endl;
}