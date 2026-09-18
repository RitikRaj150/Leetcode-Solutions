class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        vector<int> first(26, -1), last(26, -1);

        for (int i = 0; i < s.size(); i++) {
            int x = s[i] - 'a';

            if (first[x] == -1)
                first[x] = i;

            last[x] = i;
        }

        vector<pair<int, int>> v;

        for (int i = 0; i < 26; i++) {
            if (first[i] == -1)
                continue;

            int l = first[i];
            int r = last[i];
            bool ok = true;

            for (int j = l; j <= r; j++) {
                int x = s[j] - 'a';

                if (first[x] < l) {
                    ok = false;
                    break;
                }

                r = max(r, last[x]);
            }

            if (ok)
                v.push_back({l, r});
        }

        sort(v.begin(), v.end(), [](auto a, auto b) {
            return a.second < b.second;
        });

        vector<string> ans;
        int end = -1;

        for (auto p : v) {
            if (p.first > end) {
                ans.push_back(s.substr(p.first, p.second - p.first + 1));
                end = p.second;
            }
        }

        return ans;
    }
};