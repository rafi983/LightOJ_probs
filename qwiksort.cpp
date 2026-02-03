#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool is_sorted_arr(const vector<int>& a) {
    for (size_t i = 0; i < a.size() - 1; ++i) {
        if (a[i] > a[i+1]) return false;
    }
    return true;
}

void solve(int t) {
    int n;
    if (!(cin >> n)) return;
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i];
    }

    pair<int, int> range_L = {1, n};
    pair<int, int> range_R = {n + 1, 2 * n};

    int m1_start = n / 2 + 1;
    pair<int, int> range_M1 = {m1_start, m1_start + n - 1};

    int m2_start = n - n / 2 + 1;
    pair<int, int> range_M2 = {m2_start, m2_start + n - 1};

    vector<pair<int, int>> seq;

    seq.push_back(range_L);
    seq.push_back(range_R);
    seq.push_back(range_M1);
    if (range_M1 != range_M2) seq.push_back(range_M2);

    seq.push_back(range_L);
    seq.push_back(range_R);
    seq.push_back(range_M1);
    if (range_M1 != range_M2) seq.push_back(range_M2);

    seq.push_back(range_L);
    seq.push_back(range_R);

    vector<pair<int, int>> performed;

    if (is_sorted_arr(a)) {
        cout << "Case " << t << ": 0\n";
        return;
    }

    for (auto op : seq) {
        // Op is 1-based [l, r]
        int l_idx = op.first - 1;
        int r_idx = op.second - 1;

        sort(a.begin() + l_idx, a.begin() + r_idx + 1);
        performed.push_back(op);

        if (is_sorted_arr(a)) break;
    }

    cout << "Case " << t << ": " << performed.size() << "\n";
    for (const auto& op : performed) {
        cout << op.first << " " << op.second << "\n";
    }
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
