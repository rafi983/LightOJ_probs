#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

string S1;
ll s1_pref[10005];
ll len[65];
ll cnt[65];
int max_k;

void precompute() {
    ll n = S1.length();
    s1_pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        s1_pref[i+1] = s1_pref[i] + (S1[i] - '0');
    }

    len[1] = n;
    cnt[1] = s1_pref[n];

    max_k = 1;
    for (int k = 2; k <= 62; ++k) {
        if (len[k-1] > 4e17) {
             break;
        }
        len[k] = 3 * len[k-1];
        cnt[k] = len[k-1] + cnt[k-1];
        max_k = k;
    }
}

ll solve(int k, ll rem_len) {
    ll ans = 0;
    ll sign = 1;

    for (int i = k; i >= 2; --i) {
        if (rem_len <= 0) break;
        if (rem_len >= len[i]) {
            ans += sign * cnt[i];
            rem_len = 0;
            break;
        }

        ll prev_len = len[i-1];
        ll prev_cnt = cnt[i-1];

        if (rem_len <= prev_len) {
            ans += sign * prev_cnt;
            sign *= -1;
            rem_len = prev_len - rem_len;
        } else if (rem_len <= 2 * prev_len) {
            ll cur_rem = rem_len - prev_len;
            ans += sign * prev_cnt;
            ans += sign * cur_rem;
            sign *= -1;
            rem_len = cur_rem;
        } else {
            ans += sign * prev_len;
            ans += sign * prev_cnt;
            sign *= -1;
            rem_len = 3 * prev_len - rem_len;
        }
    }

    if (rem_len > 0) {
        if (rem_len > len[1]) rem_len = len[1];
        ans += sign * s1_pref[(int)rem_len];
    }

    return ans;
}

ll get_ans(ll limit) {
    if (limit <= 0) return 0;
    ll total_ones = 0;
    ll current_pos = 0;

    for (int k = 1; k <= max_k; ++k) {
        if (current_pos + len[k] < limit) {
            total_ones += cnt[k];
            current_pos += len[k];
        } else {
            ll rem = limit - current_pos;
            total_ones += solve(k, rem);
            return total_ones;
        }
    }
    return total_ones;
}

void solve_test_case(int tc) {
    cin >> S1;
    precompute();

    int Q;
    cin >> Q;

    cout << "Case " << tc << ":" << "\n";
    while(Q--) {
        ll L, R;
        cin >> L >> R;
        cout << get_ans(R) - get_ans(L-1) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            solve_test_case(i);
        }
    }
    return 0;
}
