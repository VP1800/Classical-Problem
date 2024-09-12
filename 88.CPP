#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;
bitset<(1<<22)> lookup_table;
void build_lookup_table() {
    vector<vector<int>> v(24);
    v[1] = vector<int>{0};
    for (int i = 3; i <= 23; i++) {
        for (int j = 1; j < i; j += 2) {
            const int k = i - j - 1;
            for (const int t1 : v[j]) {
                for (const int t2 : v[k]) {
                    const int t = (1 << (i - 1)) | (t1 << k) | t2;
                    v[i].push_back(t);
                    lookup_table[t &~ (1 << 22)] = 1;
                }
            }
        }
    }
}
bool is_valid(int l, int x) {
    if (l == 1) return x == 0;
    if (l <= 23) {
        return (x & (1 << (l - 1))) && lookup_table[x &~ (1 << 22)];
    }
    for (int i = 1; i < l; i+= 2) {
        const int j = l - i - 1;
        const int t2 = x & ((1 << j) - 1);
        const int t1 = (x &~ (1 << (l - 1))) >> j;
        if (is_valid(i, t1) && is_valid(j, t2)) return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    build_lookup_table();
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n == 0) {
            cout << "0\n";
            continue;
        }
        const int l = 32 - __builtin_clz(n);
        const int L = ((1 << (l + 1)) - 4) / 3;
        const int H = (1 << l) - (1 << ((l + 1) / 2));
        if (n == H) {
            cout << L << '\n';
            continue;
        }
        vector<int> v(l);
        for (int i = l - 1; i >= 0; i--) {
            v[i] = n & 1;
            n >>= 1;
        }
        for (;;) {
            next_permutation(v.begin(), v.end());
            n = 0;
            for (int i = 0; i < l; i++) {
                n = (n << 1) | v[i];
            }
            if ((n & 3) == 0 && is_valid(l, n)) {
                break;
            }
        }
        cout << n << '\n';
    }
}