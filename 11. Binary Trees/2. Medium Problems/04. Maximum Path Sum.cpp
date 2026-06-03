/*
Question:
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them.
A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.
*/

// Time Complexity: O(N)
// Visit each node exactly once.
// Space Complexity: O(H)
// Recursion stack stores at most H nodes.
// H = log N for a balanced tree.

class Solution {
public:
    int maxi = INT_MIN;

    int dfs(TreeNode* root) {
        if (!root) return 0;

        int left = max(0, dfs(root->left));
        int right = max(0, dfs(root->right));

        // Path passing through current node
        maxi = max(maxi, left + right + root->val);

        // Return best downward path
        return root->val + max(left, right);
    }

    int maxPathSum(TreeNode* root) {
        dfs(root);
        return maxi;
    }
};
