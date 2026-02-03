#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAX_BITS = 60;

struct Node {
    Node* children[2];
    Node() {
        children[0] = children[1] = nullptr;
    }
};

void deleteTrie(Node* root) {
    if (!root) return;
    if (root->children[0]) deleteTrie(root->children[0]);
    if (root->children[1]) deleteTrie(root->children[1]);
    delete root;
}

void insert(Node* root, ll val) {
    Node* curr = root;
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        int bit = (val >> i) & 1;
        if (!curr->children[bit]) {
            curr->children[bit] = new Node();
        }
        curr = curr->children[bit];
    }
}

// Queries the text in subtree to maximize XOR with val
// Returns the suffix XOR value starting from 'bit' down to 0
ll query_max_xor(Node* curr, ll val, int bit) {
    ll xor_val = 0;
    for (int i = bit; i >= 0; --i) {
        int v_bit = (val >> i) & 1;
        int desired = 1 - v_bit;
        if (curr->children[desired]) {
            xor_val |= (1LL << i);
            curr = curr->children[desired];
        } else {
            curr = curr->children[v_bit];
        }
    }
    return xor_val;
}

ll min_cost_global;

// DFS returns vector of values in subtree
vector<ll> dfs(Node* curr, int bit, ll path_val) {
    if (bit < 0) {
        return {path_val};
    }

    vector<ll> l_vec, r_vec;
    if (curr->children[0]) {
        l_vec = dfs(curr->children[0], bit - 1, path_val);
    }
    if (curr->children[1]) {
        r_vec = dfs(curr->children[1], bit - 1, path_val | (1LL << bit));
    }

    if (curr->children[0] && curr->children[1]) {
        bool left_smaller = l_vec.size() < r_vec.size();
        vector<ll>& small = left_smaller ? l_vec : r_vec;
        Node* query_root = left_smaller ? curr->children[1] : curr->children[0];

        for (ll x : small) {
            ll suffix = query_max_xor(query_root, x, bit - 1);
            // Cost = 2^bit - suffix
            ll option = (1LL << bit) - suffix;
            if (option < min_cost_global) min_cost_global = option;
        }
    }

    if (l_vec.size() > r_vec.size()) {
        l_vec.insert(l_vec.end(), r_vec.begin(), r_vec.end());
        return l_vec;
    } else {
        r_vec.insert(r_vec.end(), l_vec.begin(), l_vec.end());
        return r_vec;
    }
}

void solve(int tc) {
    int N;
    if (!(cin >> N)) return;

    vector<ll> A(N);
    for(int i=0; i<N; ++i) cin >> A[i];

    if (N <= 1) {
        cout << "Case " << tc << ": " << 0 << "\n";
        return;
    }

    sort(A.begin(), A.end());
    bool dup = false;
    for(int i=0; i<N-1; ++i) {
        if (A[i] == A[i+1]) {
            dup = true;
            break;
        }
    }

    if (dup) {
        cout << "Case " << tc << ": " << 0 << "\n";
        return;
    }

    A.erase(unique(A.begin(), A.end()), A.end());

    Node* root = new Node();
    for(ll x : A) insert(root, x);

    min_cost_global = 2e18; // Init max

    dfs(root, MAX_BITS - 1, 0);

    if (min_cost_global == 2e18) min_cost_global = 0;

    cout << "Case " << tc << ": " << min_cost_global << "\n";

    deleteTrie(root);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        for(int i=1; i<=T; ++i) solve(i);
    }
    return 0;
}
