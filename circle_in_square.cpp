#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void solve(int t) {
    double r;
    cin >> r;

    double pi = 2 * acos(0.0);
    double areaSquare = (2 * r) * (2 * r);
    double areaCircle = pi * r * r;
    double areaShaded = areaSquare - areaCircle;

    cout << "Case " << t << ": " << fixed << setprecision(2) << areaShaded << endl;
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

