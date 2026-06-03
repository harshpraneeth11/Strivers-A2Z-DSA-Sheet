/*
Question:
Given the root of a binary tree, return the length of the diameter of the tree.

Approach 1:
Height Calculation: Use a recursive function calculateHeight to compute the height of a subtree.
Diameter Calculation: For each node, calculate the diameter as the sum of the heights of its left and right subtrees.
Recursive Traversal: Recursively compute the diameter of the left and right subtrees.
TC : O(N^2)
*/ 

// ** leftDiameter means any diamter on the left subtree
// it need not pass through the leftsutbree root
// Diamter means edge lengths, not nodes
// Heights and diameters are clalcualted seperately in apprach 1 with TC : O(N^2)
// In 2nd approach, heights are calculated along with diameter with TC : O(N)

int calculateHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

int diameterOfBinaryTree(TreeNode* root) {
    if (!node) return 0;

    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    int currentDiameter = leftHeight + rightHeight;
  
    int leftDiameter = diameterOfBinaryTree(root->left);
    int rightDiameter = diameterOfBinaryTree(root->right);
    return max(currentDiameter, max(leftDiameter, rightDiameter));
}

// ___________________________________________________

/*
Approach 2:
- The diameter of a binary tree is the length of the longest path between any two nodes in the tree.
- This path may or may not pass through the root.
- To find the diameter of the tree, we can recursively calculate the height of each node's left and right subtrees.
- At each node, we calculate the diameter as the maximum of the following three values:
  - The diameter of the left subtree.
  - The diameter of the right subtree.
  - The sum of the heights of the left and right subtrees plus one (for the current node).
- We update the diameter variable with the maximum diameter encountered during the traversal.

Complexity Analysis:
- Since we visit each node once and perform constant time operations for each node, the time complexity of this approach is O(N), where N is the number of nodes in the binary tree.
- The space complexity is O(H), where H is the height of the binary tree. In the worst case, the tree can be skewed and have a height of N, resulting in O(N) space complexity. In the best case, the tree is balanced and has a height of log(N), resulting in O(log(N)) space complexity.

Code:
*/

int maxDepth(TreeNode* root, int& diameter) {
    if (!node) return 0;

    int left = maxDepth(root->left, diameter);
    int right = maxDepth(root->right, diameter);
    diameter = max(diameter, left + right);
    return max(left, right) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    maxDepth(root, diameter);
    return diameter;
}
