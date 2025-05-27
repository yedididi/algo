#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int n, m, x;

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [cost, now] = pq.top(); pq.pop();
        if (cost > dist[now]) continue;

        for (const auto& [next, weight] : graph[now]) {
            int nextDist = cost + weight;
            if (nextDist < dist[next]) {
                dist[next] = nextDist;
                pq.push({nextDist, next});
            }
        }
    }
    return dist;
}

int main() {
    cin >> n >> m >> x;

    vector<vector<pair<int, int>>> graph(n + 1);
    vector<vector<pair<int, int>>> reverse_graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
        reverse_graph[v].push_back({u, cost});  // 간선 반대로 저장
    }

    vector<int> fromX = dijkstra(graph, x);         // x -> i
    vector<int> toX = dijkstra(reverse_graph, x);   // i -> x (역방향)

    int maxTime = 0;
    for (int i = 1; i <= n; ++i) {
        if (fromX[i] == INT_MAX || toX[i] == INT_MAX) continue;
        maxTime = max(maxTime, fromX[i] + toX[i]);
    }

    cout << maxTime << endl;
}
