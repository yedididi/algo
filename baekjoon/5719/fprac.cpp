#include <iostream>
#include <queue>
#include <vector>
#include <climits>

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
    // vector<pair<int, int>> history;

    // s_history(int n, int s, vector<pair<int, int>> h = {}) : nodeNum(n), sum(s), history(h) {}

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

void removeShortestPathEdges(vector<vector<t_mapNode>> &map, vector<vector<int>> &prv, int cur) {
    queue<int> q;
    q.push(cur);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int prev : prv[now]) {
            // prev -> now 로 가는 간선을 삭제
            auto &edges = map[prev];
            for (auto it = edges.begin(); it != edges.end(); ) {
                if (it->nextNodeNum == now) {
                    it = edges.erase(it); // 해당 간선 삭제
                } else {
                    ++it;
                }
            }

            q.push(prev);
        }
    }
}



int getMinDist(vector<vector<t_mapNode>> &map)
{
    int minValue = -1;
    priority_queue<t_history> q;
    vector<int> lastNode(n + 1, INT_MAX);
    vector<int> dist(n + 1, INT_MAX);
    vector<vector<int>> prv(n + 1);

    dist[start] = 0;
    t_history firstNode = {start, 0};
    q.push(firstNode);

    while (!q.empty())
    {
        t_history poppedNode = q.top();
        q.pop();

        int cur = poppedNode.nodeNum;
        int cost = poppedNode.sum;

        if (poppedNode.nodeNum == endNum)
        {
            if (minValue == -1)
            {
                minValue = poppedNode.sum;
                //put 1001 
                removeShortestPathEdges(map, prv, endNum);
            }
            else if (minValue == poppedNode.sum)
            {
                //put 1001
                removeShortestPathEdges(map, prv, endNum);
            }
            else
                break;
        }

        for (int i = 0; i < map[poppedNode.nodeNum].size(); i++)
        {
            int next = map[poppedNode.nodeNum][i].nextNodeNum;
            int ncost = map[poppedNode.nodeNum][i].distance;
            t_history newNode = {map[poppedNode.nodeNum][i].nextNodeNum, map[poppedNode.nodeNum][i].distance + poppedNode.sum};
            // newNode.history.push_back(make_pair(poppedNode.nodeNum, i));

            if (dist[next] == dist[cur] + ncost) {
				prv[next].push_back(cur);
			}

			if (dist[next] > dist[cur] + ncost) {
				prv[next].clear();
				prv[next].push_back(cur);
				dist[next] = dist[cur] + ncost;
				// pq.push(make_pair(dist[next], next));
                q.push(newNode);
			}

            // q.push(newNode);
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