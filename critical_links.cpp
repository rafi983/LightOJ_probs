#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
int disc[MAXN], low[MAXN];
int timer;
vector<pair<int, int>> bridges;

void findBridges(int u, int p = -1) {
    disc[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == p) continue;

        if (disc[v]) {
            // Back edge
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree edge
            findBridges(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) {
                if (u < v) bridges.push_back({u, v});
                else bridges.push_back({v, u});
            }
        }
    }
}

void solve(int t) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        adj[i].clear();
        disc[i] = 0;
        low[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int u, k;
        scanf("%d (%d)", &u, &k);
        for (int j = 0; j < k; ++j) {
            int v;
            scanf("%d", &v);
            adj[u].push_back(v);
        }
    }

    bridges.clear();
    timer = 0;

    for (int i = 0; i < n; ++i) {
        if (!disc[i]) {
            findBridges(i);
        }
    }

    sort(bridges.begin(), bridges.end());

    printf("Case %d:\n", t);
    printf("%d critical links\n", (int)bridges.size());
    for (auto& bridge : bridges) {
        printf("%d - %d\n", bridge.first, bridge.second);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}
