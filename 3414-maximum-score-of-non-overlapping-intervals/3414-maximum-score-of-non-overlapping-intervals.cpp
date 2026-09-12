class Solution {
public:

    struct State {
        long long score;
        vector<int> ids;
    };

    bool better(State a, State b) {

        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // start, end, weight, original index
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting position
        sort(a.begin(), a.end());

        vector<long long> starts(n);

        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        // Find next non-overlapping interval
        vector<int> next(n);

        for (int i = 0; i < n; i++) {

            next[i] = upper_bound(
                starts.begin(),
                starts.end(),
                a[i][1]
            ) - starts.begin();
        }

        // dp[i][k]
        vector<vector<State>> dp(
            n + 1,
            vector<State>(5)
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: Don't take interval i
                State skip = dp[i + 1][k];

                // Option 2: Take interval i
                State take;

                take.score =
                    a[i][2] + dp[next[i]][k - 1].score;

                take.ids = dp[next[i]][k - 1].ids;

                take.ids.push_back(a[i][3]);

                // Keep indices sorted
                sort(take.ids.begin(), take.ids.end());

                // Choose the better option
                if (better(take, skip))
                    dp[i][k] = take;
                else
                    dp[i][k] = skip;
            }
        }

        return dp[0][4].ids;
    }
};