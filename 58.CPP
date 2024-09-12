#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
void do_testcase() {
    int t0, t1, n; cin >> t0 >> t1 >> n;
    // first -> time of event
    // second -> delta of # of people
    using Event = pair<int, int>;
    vector<Event> v;
    while (n--) {
        int a, b; cin >> a >> b;
        v.emplace_back(2 * a, 1);
        v.emplace_back(2 * b + 1, -1);
    }
    v.emplace_back(2 * t0, 0);
    v.emplace_back(2 * t1, 0);
    sort(v.begin(), v.end());
    int m = 10000, M = 0, cur = 0;
    for (int i = 0; i < v.size();) {
        int j = i;
        while (j < v.size() && v[j].first == v[i].first) j++;
        while (i < j) {
            cur += v[i].second;
            i++;
        }
        if (v[i - 1].first >= 2 * t0 && v[i - 1].first <= 2 * t1) {
            m = min(m, cur);
            M = max(M, cur);
        }
    }
    m = min(m, M);  // account for the empty case
    cout << m << ' ' << M << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    for (int i = 0; i < 10; i++) {
        do_testcase();
    }
}