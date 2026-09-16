class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1000000007;

        int N = n + k - 1;
        int R = 2 * k;

        vector<vector<long long>> dp(N + 1, vector<long long>(R + 1));

        for (int i = 0; i <= N; i++) {
            dp[i][0] = 1;

            for (int j = 1; j <= min(i, R); j++) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            }
        }

        return dp[N][R];
    }
};
