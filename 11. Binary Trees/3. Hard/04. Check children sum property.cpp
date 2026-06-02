/* QUESTION:

Given a Binary Tree. Return true if, for every node X in the tree other than the leaves, its value is equal to the sum of its left subtree's value and its right subtree's value. Else return false.

An empty tree is also a Sum Tree as the sum of an empty tree can be considered to be 0. A leaf node is also considered a Sum Tree.


Example 1:
Input:
    3
  /   \    
 1     2

Output: 1
Explanation:
The sum of left subtree and right subtree is 1 + 2 = 3, which is the value of the root node.
Therefore, the given binary tree is a sum tree.

Approach:
- Recursively calculate the sum of the left and right subtrees.
- If any subtree is not a Sum Tree, propagate failure upward.
- For each node, check whether:
      node->data == leftSubtreeSum + rightSubtreeSum
- If true, return the total sum of the current subtree.
- If false, return a failure marker.
- The tree is a Sum Tree if the root does not return failure.

CODE:
*/

// Time: O(N)
// Space: O(H)

class Solution {
public:
    int solve(Node* root) {
        if (!root) return 0;

        if (!root->left && !root->right) return root->data;

        int leftSum = solve(root->left);
        int rightSum = solve(root->right);

        if (leftSum == -1 || rightSum == -1) return -1;
        if (root->data != leftSum + rightSum) return -1;

        return root->data + leftSum + rightSum;
    }

    bool isSumTree(Node* root) {
        return solve(root) != -1;
    }
};
