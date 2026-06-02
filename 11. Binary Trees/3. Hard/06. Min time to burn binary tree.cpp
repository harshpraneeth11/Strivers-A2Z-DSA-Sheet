/* QUESTION:

Given a binary tree and a node data called target. Find the minimum time required to burn the complete binary tree if the 
target is set on fire. It is known that in 1 second, all nodes connected to a given node get burned. That is its left child, right child, and parent.
Note: The tree contains unique values.

Example 1:
Input:
          1
        /   \
      2      3
    /  \      \
   4    5      6
       / \      \
      7   8      9
                   \
                   10

Target Node = 8
Output: 7
Explanation: If the leaf with the value 8 is set on fire:
After 1 sec: 5 is set on fire.
After 2 sec: 2, 7 are set to fire.
After 3 sec: 4, 1 are set to fire.
After 4 sec: 3 is set to fire.
After 5 sec: 6 is set to fire.
After 6 sec: 9 is set to fire.
After 7 sec: 10 is set to fire.
It takes 7s to burn the complete tree.

Approach:
- Store the parent of every node using a traversal, since fire can spread upward as well.
- Find the target node from where the fire starts.
- Perform BFS starting from the target node.
- For each node, spread fire to:
    1. Left child
    2. Right child
    3. Parent
- Use a visited map to avoid revisiting nodes.
- Each BFS level represents 1 second.
- The number of levels required to burn all nodes is the answer.

COMPLEXITY ANALYSIS:
Let `n` be the number of nodes in the binary tree.
- Time Complexity: The time complexity of this approach is O(n) since we perform a BFS starting from the target node, 
visiting all nodes in the binary tree once.
- Space Complexity: The space complexity is O(n) for the queue and the hash map.

CODE:
*/
// unordered_map<Node*, Node*> parent;   Use this to map the nodes with parents
// we got targetNode's value and not node directly. So, find it first
// we used burned variable, instead time = -1 can be used at start.
// if there are only one more level. then time gets chanegd to -1 -> 0 -> 1.

class Solution {
public:

    void mapParents(Node* node, unordered_map<Node*, Node*>& parent) {
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

    Node* findTarget(Node* root, int target) {
        if (!root) return NULL;
        if (root->data == target) return root;

        Node* left = findTarget(root->left, target);
        if (left) return left;

        return findTarget(root->right, target);
    }

    int minTime(Node* root, int target) {

        unordered_map<Node*, Node*> parent;
        mapParents(root, parent);

        // we got targetNode's value and not node directly
        Node* targetNode = findTarget(root, target);

        unordered_map<Node*, bool> visited;
        queue<Node*> q;

        q.push(targetNode);
        visited[targetNode] = true;

        int time = 0;

        while (!q.empty()) {

            int size = q.size();
            bool burned = false;

            for (int i = 0; i < size; i++) {

                Node* node = q.front();
                q.pop();

                // node goes to its parent and again comes back
                // without visited, causing revisits

                if (node->left && !visited[node->left]) {
                    visited[node->left] = true;
                    q.push(node->left);
                    burned = true;
                }

                if (node->right && !visited[node->right]) {
                    visited[node->right] = true;
                    q.push(node->right);
                    burned = true;
                }

                if (parent[node] && !visited[parent[node]]) {
                    visited[parent[node]] = true;
                    q.push(parent[node]);
                    burned = true;
                }
            }

            // Fire spread during this second
            if (burned) time++;
        }

        return time;
    }
};
