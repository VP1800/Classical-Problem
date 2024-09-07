#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// lt[i][j] -> first occurrence of character j + 'a', starting from position i
vector<vector<int>> build_lookup_table(string s) {
    vector<vector<int>> result(s.size());
    vector<int> cur(26, -1);
    for (int i = s.size() - 1; i >= 0; i--) {
        cur[s[i] - 'a'] = i;
        result[i] = cur;
    }
    return result;
}
void rec(const string& s1, const string& s2,
         const vector<vector<int>>& lt1, const vector<vector<int>>& lt2,
         const vector<vector<int>>& dp, int lcs, int i, int j, string& cur) {
    if (lcs == 0) {
        cout << cur << '\n';
        return;
    }
    for (int k = 0; k < 26; k++) {
        if (lt1[i][k] >= 0 && lt2[j][k] >= 0 &&
            dp[lt1[i][k]][lt2[j][k]] == lcs) {
            cur.push_back(k + 'a');
            rec(s1, s2, lt1, lt2, dp, lcs - 1,
                lt1[i][k] + 1, lt2[j][k] + 1, cur);
            cur.pop_back();
        }
    }
}
void do_testcase() {
    string s1, s2; cin >> s1 >> s2;
    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    int lcs = 0;
    for (int i = s1.size() - 1; i >= 0; i--) {
        for (int j = s2.size() - 1; j >= 0; j--) {
            if (s1[i] == s2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            dp[i][j] = max(dp[i][j], max(dp[i+1][j], dp[i][j+1]));
            lcs = max(lcs, dp[i][j]);
        }
    }
    string cur;
    rec(s1, s2, build_lookup_table(s1), build_lookup_table(s2),
        dp, lcs, 0, 0, cur);
}
int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        do_testcase();
        cout << '\n';
    }
}