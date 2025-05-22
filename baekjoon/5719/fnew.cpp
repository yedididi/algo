#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int to, cost;
};

int n, m, start, endNum;
vector<vector<Edge>> graph;
vector<vector<int>> prevNode;

// Dijkstra로 최단 거리 및 prev 저장
vector<int> dijkstra() {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, now] = pq.top();
        pq.pop();

        if (cost > dist[now]) continue;

        for (auto& edge : graph[now]) {
            int next = edge.to;
            int newCost = cost + edge.cost;

            if (newCost < dist[next]) {
                dist[next] = newCost;
                pq.push({newCost, next});
                prevNode[next].clear();
                prevNode[next].push_back(now);
            } else if (newCost == dist[next]) {
                prevNode[next].push_back(now);
            }
        }
    }
    return dist;
}

vector<bool> visited;

void removeShortestPaths(int cur) {
    if (visited[cur]) return;
    visited[cur] = true;

    for (int prev : prevNode[cur]) {
        auto& edges = graph[prev];
        for (auto it = edges.begin(); it != edges.end(); ) {
            if (it->to == cur) {
                it = edges.erase(it);  // 간선 삭제
            } else {
                ++it;
            }
        }
        removeShortestPaths(prev);
    }
}


int main() {
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        cin >> start >> endNum;
        graph.assign(n, vector<Edge>());
        prevNode.assign(n, vector<int>());

        for (int i = 0; i < m; i++) {
            int u, v, p;
            cin >> u >> v >> p;
            graph[u].push_back({v, p});
        }

        // 1. 최소 거리 구하고 경로 저장
        vector<int> dist = dijkstra();
        // 2. 최단 경로 간선 제거
        visited.assign(n, false);
        removeShortestPaths(endNum);
        // 3. 다시 Dijkstra
        vector<int> newDist = dijkstra();

        if (newDist[endNum] == INT_MAX)
            cout << -1 << endl;
        else
            cout << newDist[endNum] << endl;
    }
    return 0;
}
