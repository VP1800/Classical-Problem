#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> calc(const vector<int>& v) {
    vector<int> result(v.size());
    vector<int> least_last(v.size() + 1, 1000000);
    least_last[0] = -1000000;
    for (int i = 0; i < v.size(); i++) {
        const auto it =
          upper_bound(least_last.begin(), least_last.end(), v[i]);
        *it = v[i];
        result[i] = it - least_last.begin();
    }
    return result;
}
void do_testcase() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> lis1 = calc(v);
    reverse(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](auto& x) { x *= -1; });
    vector<int> lis2 = calc(v);
    reverse(lis2.begin(), lis2.end());
    // Put the array back the way it was before, for output purposes
    reverse(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](auto& x) { x *= -1; });
    vector<int> result;
    const int lis = *max_element(lis1.begin(), lis1.end());
    for (int i = 0; i < n; i++) {
        if (lis1[i] + lis2[i] == lis + 1) {
            result.push_back(v[i]);
        }
    }
    cout << result.size() << '\n';
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++) {
        if (i) cout << ' ';
        cout << result[i];
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    for (int i = 0; i < 10; i++) {
        do_testcase();
    }
}
