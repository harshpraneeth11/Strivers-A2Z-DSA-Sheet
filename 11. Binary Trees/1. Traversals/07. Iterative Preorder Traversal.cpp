/*
Question:
Given the root of a binary tree, return the preorder traversal of its nodes' values.
*/

/* 
Push Root to Stack: Start traversal by pushing the root onto the stack.
Iterative Traversal:
    • Process Node: Pop the top node from the stack and add its value to the result.
    • Right Child: If it exists, push the right child onto the stack.
    • Left Child: If it exists, push the left child onto the stack (it gets processed before the right child).
Return Result: Once the stack is empty, return the preorder traversal result.

TC : O(N) and SC : O(N)
*/ 

      //     1
      //  2     3
      // 4 5   6 7

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        ans.push_back(node->val);

        // first right, then left
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }

    return ans;
}

// 1 2 4 5 3 6 7


      //     1
      //  2     3
      // 4 5   6 7

// 4 5 2 6 7 3 1

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        ans.push_back(node->val);

        // first right, then left
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}


//           1
//        2     3
//       4 5   6 7

// 4 2 5 1 6 3 7

// st = 1
// ans = 4 2  

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr || !st.empty()) {

        // Reach the leftmost node, storing the path in the stack
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }

        // Left subtree is processed, now visit the node
        curr = st.top();
        st.pop();
        ans.push_back(curr->val);

        // Start processing the right subtree
        curr = curr->right;
    }

    return ans;
}
