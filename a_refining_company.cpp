#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 505;
int U[MAXN][MAXN];
int R[MAXN][MAXN];
int sumU[MAXN][MAXN];
int sumR[MAXN][MAXN];
int dp[MAXN][MAXN];

void solve(int t) {
    int m, n;
    cin >> m >> n;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> U[i][j];
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> R[i][j];
        }
    }

    for (int i = 1; i <= m; ++i) {
        sumU[i][0] = 0;
        for (int j = 1; j <= n; ++j) {
            sumU[i][j] = sumU[i][j-1] + U[i][j];
        }
    }

    for (int j = 1; j <= n; ++j) {
        sumR[0][j] = 0;
        for (int i = 1; i <= m; ++i) {
            sumR[i][j] = sumR[i-1][j] + R[i][j];
        }
    }

    for (int i = 0; i <= m; ++i) dp[i][0] = 0;
    for (int j = 0; j <= n; ++j) dp[0][j] = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = max(
                dp[i-1][j] + sumU[i][j],



                dp[i][j-1] + sumR[i][j]


            );
        }
    }

    cout << "Case " << t << ": " << dp[m][n] << endl;
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
