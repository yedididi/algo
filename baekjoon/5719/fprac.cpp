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

    s_node(int n, int s) : nodeNum(n), sum(s) {}

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

typedef struct s_history
{
    int nodeNum;
    int sum;
    vector<pair<int, int>> history;

    s_history(int n, int s, vector<pair<int, int>> h = {}) : nodeNum(n), sum(s), history(h) {}

    bool operator<(const s_history n) const
    {
        return (this->sum > n.sum);
    }
} t_history;

int getAlmostMinDist(vector<vector<t_mapNode>> map)
{
    priority_queue<t_node> q;

    t_node firstNode = {start, 0};
    q.push(firstNode);

    while (!q.empty())
    {
        t_node poppedNode = q.top();
        q.pop();

        // cout << "nodeNum is " << poppedNode.nodeNum << endl;
        if (poppedNode.nodeNum == endNum)
            return (poppedNode.sum);

        for (int i = 0; i < map[poppedNode.nodeNum].size(); i++)
        {
            // cout << "map[" << poppedNode.nodeNum << "][" << i << "].distance is " << map[poppedNode.nodeNum][i].distance << endl;
            if (map[poppedNode.nodeNum][i].distance == 1001)
                continue;
            t_node newNode = {map[poppedNode.nodeNum][i].nextNodeNum, map[poppedNode.nodeNum][i].distance + poppedNode.sum};
            q.push(newNode);
        }
    }
    return (-1);
}

int getMinDist(vector<vector<t_mapNode>> &map)
{
    int minValue = -1;
    priority_queue<t_history> q;

    t_history firstNode = {start, 0};
    q.push(firstNode);

    while (!q.empty())
    {
        t_history poppedNode = q.top();
        q.pop();

        // cout << "nodeNum is " << poppedNode.nodeNum << endl;
        if (poppedNode.nodeNum == endNum)
        {
            // cout << "reached endNum, dist is " << poppedNode.sum << endl;

            if (minValue == -1)
            {
                // cout << "minValue is -1\n";
                minValue = poppedNode.sum;
                for (auto itr = poppedNode.history.begin(); itr != poppedNode.history.end(); itr++)
                    map[itr->first][itr->second].distance = 1001;
            }
            else if (minValue == poppedNode.sum)
            {
                // cout << "minValue is " << minValue << endl;
                for (auto itr = poppedNode.history.begin(); itr != poppedNode.history.end(); itr++)
                    map[itr->first][itr->second].distance = 1001;
            }
            else
                break;
        }

        for (int i = 0; i < map[poppedNode.nodeNum].size(); i++)
        {
            t_history newNode = {map[poppedNode.nodeNum][i].nextNodeNum, map[poppedNode.nodeNum][i].distance + poppedNode.sum, poppedNode.history};
            newNode.history.push_back(make_pair(poppedNode.nodeNum, i));
            q.push(newNode);
        }
    }
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
        }
        getMinDist(map);
        answer.push_back(getAlmostMinDist(map));
        almostMin = -1;
    }
    for (auto itr = answer.begin(); itr != answer.end(); itr++)
        cout << *itr << endl;
}