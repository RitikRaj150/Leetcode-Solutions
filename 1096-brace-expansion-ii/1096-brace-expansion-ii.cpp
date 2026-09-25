class Solution {
public:
    set<string> ans;

    void dfs(string s) {
        int j = s.find('}');

        if (j == string::npos) {
            ans.insert(s);
            return;
        }

        int i = s.rfind('{', j);

        string left = s.substr(0, i);
        string mid = s.substr(i + 1, j - i - 1);
        string right = s.substr(j + 1);

        string temp = "";

        for (char c : mid) {
            if (c == ',') {
                dfs(left + temp + right);
                temp = "";
            } else {
                temp += c;
            }
        }

        dfs(left + temp + right);
    }

    vector<string> braceExpansionII(string expression) {
        dfs(expression);
        return vector<string>(ans.begin(), ans.end());
    }
};