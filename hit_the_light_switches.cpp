#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 10005;

vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], sccID[MAXN];
bool onStack[MAXN];
stack<int> stk;
int timer, sccCount;
int inDegreeSCC[MAXN];

void tarjan(int u) {
    disc[u] = low[u] = ++timer;
    stk.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        sccCount++;
        while (true) {
            int v = stk.top();
            stk.pop();
            onStack[v] = false;
            sccID[v] = sccCount;
            if (u == v) break;
        }
    }
}

void solve(int t) {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i <= N; ++i) {
        adj[i].clear();
        disc[i] = -1;
        low[i] = -1;
        onStack[i] = false;
        sccID[i] = 0;
        inDegreeSCC[i] = 0;
    }
    while (!stk.empty()) stk.pop();

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    timer = 0;
    sccCount = 0;

    for (int i = 1; i <= N; ++i) {
        if (disc[i] == -1) {
            tarjan(i);
        }
    }

    for(int i = 1; i <= sccCount; ++i) inDegreeSCC[i] = 0;

    for (int u = 1; u <= N; ++u) {
        for (int v : adj[u]) {
            if (sccID[u] != sccID[v]) {
                inDegreeSCC[sccID[v]]++;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= sccCount; ++i) {
        if (inDegreeSCC[i] == 0) {
            ans++;
        }
    }

    cout << "Case " << t << ": " << ans << endl;
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
