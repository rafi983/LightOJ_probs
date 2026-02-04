#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long solve(long long n) {
    long long c = n;
    long long c0 = 0;
    long long c1 = 0;

    while (((c & 1) == 0) && (c != 0)) {
        c0++;
        c >>= 1;
    }

    while ((c & 1) == 1) {
        c1++;
        c >>= 1;
    }

    long long p = c0 + c1;

    n |= (1LL << p);

    n &= ~((1LL << p) - 1);

    n |= (1LL << (c1 - 1)) - 1;

    return n;
}

int main() {
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            long long n;
            cin >> n;
            cout << "Case " << i << ": " << solve(n) << endl;
        }
    }
    return 0;
}
