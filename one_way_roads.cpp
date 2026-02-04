#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int cost;
};

vector<Edge> adj[105];

int solve(int startNode, int firstNeighborIndex, int n) {
    int totalCost = 0;

    // First step
    Edge firstEdge = adj[startNode][firstNeighborIndex];
    int current = firstEdge.to;
    totalCost += firstEdge.cost;

    int prev = startNode;

    for (int i = 0; i < n - 1; ++i) {
        for (auto& edge : adj[current]) {
            if (edge.to != prev) {
                totalCost += edge.cost;
                prev = current;
                current = edge.to;
                break;
            }
        }
    }
    return totalCost;
}

void solveCase(int t) {
    int n;
    cin >> n;

    for (int i = 0; i <= n; ++i) adj[i].clear();

    for (int i = 0; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, w});
    }

    int cost1 = solve(1, 0, n);
    int cost2 = solve(1, 1, n);

    cout << "Case " << t << ": " << min(cost1, cost2) << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solveCase(i);
    }
    return 0;
}
