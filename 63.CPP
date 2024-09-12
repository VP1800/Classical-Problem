#include <iostream>
#include <cstring>  // For memset
using namespace std;

int main()
{
    int d;
    int i, n, k, j, x;
    bool must[38];
    int dp[38][39];

    cin >> d;
    for (i = 0; i < d; i++)
    {
        cin >> n >> k;

        // Initialize the must array to false
        memset(must, 0, sizeof(must));

        for (j = 0; j < k; j++)
        {
            cin >> x;
            must[x - 1] = true;
        }

        // DP state: character | #opening - #closing
        memset(dp, 0, sizeof(dp));

        dp[0][1] = 1;  // Initial condition: 1 opening bracket

        for (j = 1; j < 2 * n; j++)
        {
            // Add opening bracket
            for (k = 1; k <= 38; k++)
                dp[j][k] += dp[j - 1][k - 1];

            // Add closing bracket if possible
            if (!must[j])
            {
                for (k = 0; k < 38; k++)
                    dp[j][k] += dp[j - 1][k + 1];
            }
        }

        // Output the result for valid sequences
        cout << dp[2 * n - 1][0] << endl;
    }

    return 0;
}