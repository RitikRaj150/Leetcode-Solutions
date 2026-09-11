class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};

        for (int x : digits) {
            cnt[x]++;
        }

        int ans = 0;

        // Last digit must be even
        for (int last = 0; last <= 8; last += 2) {
            if (cnt[last] == 0)
                continue;

            // Use one occurrence of last digit
            cnt[last]--;

            // First digit: 1 to 9
            for (int first = 1; first <= 9; first++) {
                if (cnt[first] == 0)
                    continue;

                cnt[first]--;

                // Second digit: 0 to 9
                for (int second = 0; second <= 9; second++) {
                    if (cnt[second] > 0) {
                        ans++;
                    }
                }

                cnt[first]++;
            }

            cnt[last]++;
        }

        return ans;
    }
};