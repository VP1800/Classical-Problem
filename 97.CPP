#include <iostream>
#include <cstring>  // For memset
using namespace std;

int main() {
    int dp[501];
    int b, n, i, cost, fun, j;

    for (;;) {
        cin >> b >> n;

        if (b == 0 && n == 0)
            return 0;

        memset(dp, 0, sizeof(dp));  // Initialize dp array with 0

        for (i = 0; i < n; i++) {
            cin >> cost >> fun;

            // Update dp array in reverse to avoid overwriting values in the same iteration
            for (j = b - cost; j >= 0; j--) {
                if (dp[j + cost] < dp[j] + fun) {
                    dp[j + cost] = dp[j] + fun;
                }
            }
        }

        int max_fun = 0;
        int min_cost = 0;

        // Find the maximum fun and corresponding minimum cost
        for (i = 0; i <= b; i++) {
            if (dp[i] > max_fun) {
                max_fun = dp[i];
                min_cost = i;
            }
        }

        cout << min_cost << ' ' << max_fun << endl;
    }

    return 0;
}