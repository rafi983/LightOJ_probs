#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool check(int limit, int n, int k, const vector<int>& dists) {
    int days = 1;
    int current_dist = 0;
    for (int d : dists) {
        if (current_dist + d > limit) {
            days++;
            current_dist = d;
        } else {
            current_dist += d;
        }
    }
    return days <= k + 1;
}

void solve(int t) {
    int n, k;
    cin >> n >> k;
    vector<int> dists(n + 1);
    int max_val = 0;
    int sum_val = 0;
    for (int i = 0; i <= n; ++i) {
        cin >> dists[i];
        max_val = max(max_val, dists[i]);
        sum_val += dists[i];
    }

    int low = max_val, high = sum_val;
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, n, k, dists)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << "Case " << t << ": " << ans << endl;


    vector<int> schedule;
    int current_idx = 0;
    for (int day = 0; day <= k; ++day) {
        int current_day_dist = 0;
        int segments_taken = 0;


        int max_segments_can_take = ((n + 1) - current_idx) - (k - day);

        while (segments_taken < max_segments_can_take) {
            if (current_day_dist + dists[current_idx] <= ans) {
                 current_day_dist += dists[current_idx];
                 current_idx++;
                 segments_taken++;
            } else {
                break;
            }
        }
        cout << current_day_dist << endl;
    }
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

