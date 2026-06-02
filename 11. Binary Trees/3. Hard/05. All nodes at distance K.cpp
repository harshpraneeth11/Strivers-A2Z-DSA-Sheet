/* QUESTION:

Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.


APPROACH:

To find the nodes that are at a distance k from the target node, we can perform a two-step process:
1. First, traverse the binary tree to build a map of each node to its parent node using BFS. This map will help us later to backtrack from the target node to its ancestors.
2. Next, perform a BFS from the target node to find all nodes at a distance k from it. While doing this, we also mark visited nodes to avoid revisiting the same nodes.

COMPLEXITY ANALYSIS:

Let `n` be the number of nodes in the binary tree.
- Time Complexity: The time complexity of this approach is O(n) since we need to traverse the entire binary tree to build the parent map and perform BFS from the target node.
- Space Complexity: The space complexity is O(n) for the parent map and O(k) for the queue used in BFS. In the worst case, when k approaches n, the space complexity becomes O(n).

CODE:
*/

class Solution {
public:
    // Recursive function to map parent pointers
    void mapParents(TreeNode* node, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (!node) return;
        
        if (node->left) {
            parent[node->left] = node;
            mapParents(node->left, parent);
        }
        
        if (node->right) {
            parent[node->right] = node;
            mapParents(node->right, parent);
        }
    }

    // Main function to find nodes at distance K
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parent;
        mapParents(root, parent);  // Map parent pointers recursively

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int currentDistance = 0;

        while (!q.empty()) {
            if (currentDistance == k) break;
            currentDistance++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

     // node goes to it's parent and again go back to the visited child node, if there is no visisted vector
                if (node->left && !visited[node->left]) {
                    visited[node->left] = true;
                    q.push(node->left);
                }
                if (node->right && !visited[node->right]) {
                    visited[node->right] = true;
                    q.push(node->right);
                }
                if (parent[node] && !visited[parent[node]]) {
                    visited[parent[node]] = true;
                    q.push(parent[node]);
                }
            }
        }

        vector<int> ans;
        while (!q.empty()) {
            ans.push_back(q.front()->val);
            q.pop();
        }
        return ans;
    }
};
