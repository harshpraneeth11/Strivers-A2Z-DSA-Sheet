// Almost same as PreOrder

vector<int> postOrder(Node* root) {
    vector<int> ans;
    Node* curr = root;

    while (curr) {
        if (!curr->right) {
            ans.push_back(curr->data);
            curr = curr->left;
        } else {
            Node* leftmost = curr->right;

            while (leftmost->left && leftmost->left != curr)
                leftmost = leftmost->left;

            if (!leftmost->left) {
                ans.push_back(curr->data);
                leftmost->left = curr;
                curr = curr->right;
            } else {
                leftmost->left = NULL;
                curr = curr->left;
            }
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
