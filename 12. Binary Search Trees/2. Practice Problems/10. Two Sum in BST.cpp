/*
Question:
Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

Explanation:
- We are using two stacks, one for the left traversal and one for the right traversal of the BST.
- The next() function returns the next smallest element in the BST by popping the top element from the left stack and pushing all the leftmost nodes in its right subtree to the stack.
- The before() function returns the next largest element in the BST by popping the top element from the right stack and pushing all the rightmost nodes in its left subtree to the stack.
- We use the two pointer approach with the next() and before() functions to find the pair of elements in the BST whose sum is equal to k.

Time Complexity:
- The findTarget() function uses two pointers (one for the left and one for the right traversal of the BST) and performs a two pointer traversal of the BST, taking O(n) time, where n is the number of nodes in the BST.
- The next() and before() functions take O(h) time each, where h is the height of the BST, as they traverse the leftmost and rightmost paths in the BST.

Space Complexity:
- The space complexity is O(h), where h is the height of the BST, as the stacks store the nodes in the leftmost and rightmost paths of the BST.

*/

/*
This line: 
BSTIterator l(root, false);

creates an object l of the BSTIterator class and calls its constructor:
BSTIterator(TreeNode* root, bool rev) {
    reverse = rev;
    pushAll(root);
}

So it is equivalent to: 
BSTIterator l = BSTIterator(root, false);
*/

class BSTIterator {
    stack<TreeNode*> st;
    bool reverse;

    void pushAll(TreeNode* node) {
        while (node) {
            st.push(node);

            if (reverse) node = node->right;
            else node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root, bool rev) {
        reverse = rev;
        pushAll(root);
    }

    bool hasNext() {
        return !st.empty();
    }

    int next() {
        TreeNode* node = st.top();
        st.pop();

        if (reverse) pushAll(node->left);
        else pushAll(node->right);

        return node->val;
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;

        BSTIterator left(root, false);   // smallest -> largest
        BSTIterator right(root, true);   // largest -> smallest

        int l = left.next();
        int r = right.next();

        while (l < r) {
            int sum = l + r;

            if (sum == k) return true;

            else if (sum < k) {
                if (!left.hasNext()) return false;
                l = left.next();
            }
            else {
                if (!right.hasNext()) return false;
                r = right.next();
            }
        }
        
        return false;
    }
};
