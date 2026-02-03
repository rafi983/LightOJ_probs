#include <iostream>

using namespace std;

void solve(int t) {
    int A, B, C;
    cin >> A >> B >> C;
    bool found = false;


    // Match 1: A vs B
    for (int resAB = 0; resAB < 3; resAB++) {
        // Match 2: A vs C
        for (int resAC = 0; resAC < 3; resAC++) {
            // Match 3: B vs C
            for (int resBC = 0; resBC < 3; resBC++) {
                int pA = 0, pB = 0, pC = 0;

                // Process A vs B
                if (resAB == 0) pA += 3;       // A wins
                else if (resAB == 1) pB += 3;  // B wins
                else { pA++; pB++; }           // Draw

                // Process A vs C
                if (resAC == 0) pA += 3;       // A wins
                else if (resAC == 1) pC += 3;  // C wins
                else { pA++; pC++; }           // Draw

                // Process B vs C
                if (resBC == 0) pB += 3;       // B wins
                else if (resBC == 1) pC += 3;  // C wins
                else { pB++; pC++; }           // Draw

                if (pA == A && pB == B && pC == C) {
                    found = true;
                    goto done;
                }
            }
        }
    }

done:
    cout << "Case " << t << ": " << (found ? "perfectus" : "invalidum") << endl;
}

int main() {
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }
    return 0;
}
