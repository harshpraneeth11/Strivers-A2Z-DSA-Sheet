/*
Question:
Given a binary tree, print its top view.

Approach:

Start BFS with the root node at vertical position 0 .
For each node, if its vertical position is not in the map, store its value in mpp
Add the left child with vertical - 1 and right child with vertical + 1 to the queue.
Extract values from the map (sorted by vertical positions) into a result vector.

Complexity Analysis:
- Since we visit each node once and perform constant time operations for each node, the time complexity of this approach is O(N), where N is the number of nodes in the binary tree.
- The space complexity is O(N), where N is the number of nodes in the binary tree. This space is used to store the nodes in the map during the traversal.

Code:
*/
class Solution {
public:
    vector<int> topView(Node* root) {
        vector<int> ans;
        if (root == NULL) {
            return ans;
        }

        // Use map and queue like this, main thing
        map<int, int> mpp;
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            Node* node = it.first;
            int line = it.second;

            // This is the difference            
            if (mpp.find(line) == mpp.end()) {
                mpp[line] = node->data;
            }

            if (node->left != NULL) {
                q.push({node->left, line - 1});
            }
            if (node->right != NULL) {
                q.push({node->right, line + 1});
            }
        }

        for (auto it : mpp) {
            ans.push_back(it.second);
        }

        return ans;
    }
};
