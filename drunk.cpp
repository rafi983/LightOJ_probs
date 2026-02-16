#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool hasCycle(int u, vector<vector<int>>& adj, vector<int>& visited) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (visited[v] == 1) {
            return true;
        }
        if (visited[v] == 0) {
            if (hasCycle(v, adj, visited)) {
                return true;
            }
        }
    }
    visited[u] = 2;
    return false;
}

void solve(int t) {
    int m;
    if (!(cin >> m)) return;

    map<string, int> nameToId;
    int idCounter = 0;
    vector<pair<string, string>> edges;

    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        if (nameToId.find(u) == nameToId.end()) nameToId[u] = idCounter++;
        if (nameToId.find(v) == nameToId.end()) nameToId[v] = idCounter++;
        edges.push_back({u, v});
    }

    int n = idCounter;
    vector<vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[nameToId[edge.first]].push_back(nameToId[edge.second]);
    }

    vector<int> visited(n, 0);
    bool possible = true;
    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            if (hasCycle(i, adj, visited)) {
                possible = false;
                break;
            }
        }
    }

    cout << "Case " << t << ": " << (possible ? "Yes" : "No") << endl;
}

int main() {
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    return 0;
}
