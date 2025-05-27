#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int maxTime = INT_MIN;
int n, m, x;
vector<vector<pair<int, int>>> graph(1001);
vector<vector<pair<int, int>>> reverse_graph(1001);

typedef struct s_node
{
    int currentLocation;
    int sum;

    s_node(int c, int s) : currentLocation(c), sum(s) {}

    bool operator<(const s_node other) const
    {
        return (this->sum > other.sum);
    }

} t_node;

vector<int> bfs(vector<vector<pair<int, int>>> map, int start)
{
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<t_node> q;

    t_node firstNode = {start, 0};
    q.push(firstNode);

    while (!q.empty())
    {
        t_node poppedNode = q.top();
        q.pop();

        if (poppedNode.sum > dist[poppedNode.currentLocation]) continue;

        for (auto itr = map[poppedNode.currentLocation].begin(); itr != map[poppedNode.currentLocation].end(); itr++)
        {
            t_node newNode = {itr->first, poppedNode.sum + itr->second};
            q.push(newNode);
            int nextDist = poppedNode.sum + itr->second;
            if (nextDist < dist[itr->first]) 
            {
                dist[itr->first] = nextDist;
                q.push({nextDist, itr->first});
            }
        }
    }
    return (dist);
}

int main(void)
{
    cin >> n >> m >> x;

    for (int i = 0; i < m; i++)
    {
        int start, end, time;
        cin >> start >> end >> time;

        graph[start].push_back({end, time});
        reverse_graph[end].push_back({start, time});
    }

    vector<int> i_to_x = bfs(graph, x);
    vector<int> x_to_i = bfs(reverse_graph, x);

    for (int i = 1; i <= n; i++)
    {
        maxTime = max(maxTime, i_to_x[i] + x_to_i[i]);
    }
    cout << maxTime << endl;
}