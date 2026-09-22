class Solution {
public:
    int k;
    vector<vector<int>> tree;
    vector<int> prod;

    void mergeNode(int node) {
        fill(tree[node].begin(), tree[node].end(), 0);

        for (int i = 0; i < k; i++) {
            tree[node][i] += tree[node * 2][i];
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                int r = (prod[node * 2] * j) % k;

                if (r == i)
                    tree[node][i] += tree[node * 2 + 1][j];
            }
        }

        prod[node] = (prod[node * 2] * prod[node * 2 + 1]) % k;
    }

    void build(vector<int>& nums, int node, int l, int r) {
        if (l == r) {
            prod[node] = nums[l] % k;
            tree[node][prod[node]] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);

        mergeNode(node);
    }

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            fill(tree[node].begin(), tree[node].end(), 0);

            prod[node] = val % k;
            tree[node][prod[node]] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, val);
        else
            update(node * 2 + 1, mid + 1, r, pos, val);

        mergeNode(node);
    }

    pair<vector<int>, int> query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return {tree[node], prod[node]};

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        auto left = query(node * 2, l, mid, ql, qr);
        auto right = query(node * 2 + 1, mid + 1, r, ql, qr);

        vector<int> res(k, 0);

        for (int i = 0; i < k; i++)
            res[i] += left.first[i];

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                int rem = (left.second * j) % k;

                if (rem == i)
                    res[i] += right.first[j];
            }
        }

        int p = (left.second * right.second) % k;

        return {res, p};
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();

        tree.assign(4 * n, vector<int>(k, 0));
        prod.assign(4 * n, 1);

        build(nums, 1, 0, n - 1);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            auto res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.first[x]);
        }

        return ans;
    }
};
