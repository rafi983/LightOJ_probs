#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

bool forbidden[26][26][26];
int dist[26][26][26];

struct State {
    int a, b, c;
};

int solve() {
    string start_s, finish_s;
    cin >> start_s >> finish_s;

    int n;
    cin >> n;

    memset(forbidden, 0, sizeof(forbidden));
    memset(dist, -1, sizeof(dist));

    for (int i = 0; i < n; ++i) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        for (char c1 : s1) {
            for (char c2 : s2) {
                for (char c3 : s3) {
                    forbidden[c1 - 'a'][c2 - 'a'][c3 - 'a'] = true;
                }
            }
        }
    }

    int sa = start_s[0] - 'a';
    int sb = start_s[1] - 'a';
    int sc = start_s[2] - 'a';

    int fa = finish_s[0] - 'a';
    int fb = finish_s[1] - 'a';
    int fc = finish_s[2] - 'a';

    if (forbidden[sa][sb][sc]) return -1;
    if (sa == fa && sb == fb && sc == fc) return 0;

    queue<State> q;
    q.push({sa, sb, sc});
    dist[sa][sb][sc] = 0;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        int d = dist[curr.a][curr.b][curr.c];
        if (curr.a == fa && curr.b == fb && curr.c == fc) return d;

        int da[] = {1, -1, 0, 0, 0, 0};
        int db[] = {0, 0, 1, -1, 0, 0};
        int dc[] = {0, 0, 0, 0, 1, -1};

        for (int i = 0; i < 6; ++i) {
            int na = (curr.a + da[i] + 26) % 26;
            int nb = (curr.b + db[i] + 26) % 26;
            int nc = (curr.c + dc[i] + 26) % 26;

            if (!forbidden[na][nb][nc] && dist[na][nb][nc] == -1) {
                dist[na][nb][nc] = d + 1;
                q.push({na, nb, nc});
            }
        }
    }

    return -1;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << ": " << solve() << endl;
    }
    return 0;
}
