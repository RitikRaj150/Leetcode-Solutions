class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k);
        vector<long long> dp(k);

        for (int x : nums) {
            vector<long long> ndp(k);

            // Start a new subarray with nums[i]
            ndp[x % k]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int nr = (r * (x % k)) % k;
                    ndp[nr] += dp[r];
                }
            }

            dp = ndp;

            // Add all subarrays ending here
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};