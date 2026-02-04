#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int m, n;
char board[15][15];
int total_cost[15][15];
int reachable_count[15][15];

// Knight move offsets
int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

bool isValid(int r, int c) {
    return r >= 0 && r < m && c >= 0 && c < n;
}

void bfs(int startR, int startC, int k) {
    int dist[15][15];
    for (int i = 0; i < m; ++i) fill(dist[i], dist[i] + n, -1);

    queue<pair<int, int>> q;
    q.push({startR, startC});
    dist[startR][startC] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        int moves = (dist[r][c] + k - 1) / k;

        total_cost[r][c] += moves;
        reachable_count[r][c]++;

        for (int i = 0; i < 8; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            if (isValid(nr, nc) && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
}

void solve(int caseNum) {
    cin >> m >> n;

    vector<pair<int, int>> riders;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (isdigit(board[i][j])) {
                riders.push_back({i, j});
            }
            total_cost[i][j] = 0;
            reachable_count[i][j] = 0;
        }
    }

    for (auto& rider : riders) {
        int r = rider.first;
        int c = rider.second;
        int k = board[r][c] - '0';
        bfs(r, c, k);
    }

    int min_moves = INT_MAX;
    int num_riders = riders.size();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (reachable_count[i][j] == num_riders) {
                if (total_cost[i][j] < min_moves) {
                    min_moves = total_cost[i][j];
                }
            }
        }
    }

    if (min_moves == INT_MAX) min_moves = -1;

    cout << "Case " << caseNum << ": " << min_moves << endl;
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
