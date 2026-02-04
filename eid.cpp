#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_X = 10005;
const int BASE = 1000000000;

struct BigInt {
    vector<int> digits;

    BigInt(long long v = 0) {
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % BASE);
            v /= BASE;
        }
    }

    void multiply(int v) {
        long long carry = 0;
        for (size_t i = 0; i < digits.size() || carry; ++i) {
            if (i == digits.size()) digits.push_back(0);
            long long current = (long long)digits[i] * v + carry;
            digits[i] = current % BASE;
            carry = current / BASE;
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    void print() {
        if (digits.empty()) {
            cout << 0;
            return;
        }
        cout << digits.back();
        for (int i = digits.size() - 2; i >= 0; --i) {
            cout << setfill('0') << setw(9) << digits[i];
        }
    }
};

int max_powers[MAX_X];
bool is_prime[MAX_X];

void sieve() {
    fill(is_prime, is_prime + MAX_X, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p < MAX_X; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i < MAX_X; i += p)
                is_prime[i] = false;
        }
    }
}

void solve(int t) {
    int n;
    cin >> n;

    memset(max_powers, 0, sizeof(max_powers));

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int p = 2; p * p <= x; ++p) {
            if (x % p == 0) {
                int count = 0;
                while (x % p == 0) {
                    x /= p;
                    count++;
                }
                if (count > max_powers[p]) {
                    max_powers[p] = count;
                }
            }
        }
        if (x > 1) {
            if (1 > max_powers[x]) {
                max_powers[x] = 1;
            }
        }
    }

    BigInt result(1);

    for (int p = 2; p < MAX_X; ++p) {
        if (is_prime[p] && max_powers[p] > 0) {
            int multiplier = 1;
            for(int k=0; k<max_powers[p]; ++k) {
                multiplier *= p;
            }
            result.multiply(multiplier);
        }
    }

    cout << "Case " << t << ": ";
    result.print();
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    return 0;
}
