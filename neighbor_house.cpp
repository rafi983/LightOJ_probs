#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int t) {
    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(3));

    for (int i = 0; i < n; ++i) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    vector<vector<int>> dp(n, vector<int>(3));

    dp[0][0] = cost[0][0];
    dp[0][1] = cost[0][1];
    dp[0][2] = cost[0][2];

    for (int i = 1; i < n; ++i) {
        dp[i][0] = cost[i][0] + min(dp[i-1][1], dp[i-1][2]);
        dp[i][1] = cost[i][1] + min(dp[i-1][0], dp[i-1][2]);
        dp[i][2] = cost[i][2] + min(dp[i-1][0], dp[i-1][1]);
    }

    int min_cost = min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});

    cout << "Case " << t << ": " << min_cost << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}
