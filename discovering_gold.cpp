#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

void solve(int t) {
    int n;
    cin >> n;
    vector<int> gold(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> gold[i];
    }

    vector<double> expected(n + 1);
    expected[n] = gold[n];

    for (int i = n - 1; i >= 1; --i) {
        double sum_next_expected = 0;
        int valid_moves = 0;
        for (int dice = 1; dice <= 6; ++dice) {
            if (i + dice <= n) {
                sum_next_expected += expected[i + dice];
                valid_moves++;
            }
        }
        expected[i] = gold[i] + (sum_next_expected / valid_moves);
    }

    cout << "Case " << t << ": " << fixed << setprecision(10) << expected[1] << endl;
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

