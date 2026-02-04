#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

const int INF = 1e9;

void solve(int t) {
    int N;
    long long K;
    cin >> N >> K;

    vector<long long> L(N);
    for (int i = 0; i < N; ++i) {
        cin >> L[i];
    }

    sort(L.begin(), L.end());

    // dp[i] = minimum groups for first i people
    vector<int> dp(N + 1, INF);
    dp[0] = 0;

    deque<int> dq;
    int start_ptr = 0;

    for (int i = 1; i <= N; ++i) {

        long long min_val = L[i-1] - 2 * K;
        while (start_ptr < i && L[start_ptr] < min_val) {
            start_ptr++;
        }

        int new_j = i - 3;
        if (new_j >= 0) {
            if (dp[new_j] != INF) {
                while (!dq.empty() && dp[dq.back()] >= dp[new_j]) {
                    dq.pop_back();
                }
                dq.push_back(new_j);
            }
        }

        while (!dq.empty() && dq.front() < start_ptr) {
            dq.pop_front();
        }

        if (!dq.empty()) {
            dp[i] = dp[dq.front()] + 1;
        }
    }

    cout << "Case " << t << ": " << (dp[N] == INF ? -1 : dp[N]) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    return 0;
}
