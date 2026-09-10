/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    // Returns {sum of subtree, number of nodes in subtree}
    pair<int, int> dfs(TreeNode* root, int &ans) {
        
        // If there is no node
        if (root == NULL)
            return {0, 0};

        // Get sum and count of left subtree
        auto left = dfs(root->left, ans);

        // Get sum and count of right subtree
        auto right = dfs(root->right, ans);

        // Total sum of current subtree
        int sum = root->val + left.first + right.first;

        // Total number of nodes in current subtree
        int count = 1 + left.second + right.second;

        // Calculate average of current subtree
        int average = sum / count;

        // Check if current node value equals average
        if (root->val == average)
            ans++;

        // Return sum and count to the parent
        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        
        int ans = 0;

        // Start DFS from root
        dfs(root, ans);

        return ans;
    }
};