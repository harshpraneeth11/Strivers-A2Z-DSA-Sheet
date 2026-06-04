/*
A segment tree is:
A binary tree where each node stores answer for a segment (subarray)
So instead of recomputing ranges again and again, we reuse precomputed results.

Point update = one update
Without lazy propagation: 
You must update each index separately, O(n log n) worst case
With lazy propagation:
One operation handles full range, O(log n)
Range Update = Add +5 to all elements from index 2 to 6 
Generally same number is added to all

Tree stores:
root → sum of whole array
children → halves
leaves → individual elements

For tree vector : size = 4*n (safe upper bound)   ??

In query, l and r means current segment of the tree node. This is fixed by the structure of the tree
ql, qr → query range (user request). This changes for every query.
At each node, we check overlap is 
No - return 0
full - use precomputed value
partial - go deeper (split into children)
*/

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
// This is constructor. Same name as class: SegmentTree
// No return type (not even void). Automatically called when object is created
    SegmentTree(vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // build tree
    void build(vector<int> &arr, int node, int l, int r) {

// If segment has only 1 element. store it directly in node. This can be a leaf node too
        if (l == r) {
            tree[node] = arr[l];
            return;
        }

        int mid = (l + r) / 2;

        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
/*
If (ql, qr) is bigger, and (l, r) is smaller, aren’t we missing the rest?
Array Index:  1 2 3 4 5 6
Query: [2, 6]
Now suppose we are at node, [l, r] = [3, 4]
For [2,6], recursion will also visit:
[2], [3,4], [5,6]
*/
    // range query [ql, qr]
    int query(int node, int l, int r, int ql, int qr) {
        // no overlap
        if (r < ql || l > qr) return 0;

        // full overlap
        if (ql <= l && r <= qr) return tree[node];

        // partial overlap
        int mid = (l + r) / 2;

        return query(2 * node + 1, l, mid, ql, qr) +
               query(2 * node + 2, mid + 1, r, ql, qr);

        // Query intuition : Take full pieces if possible, otherwise break and combine
    }

    // point update: set arr[idx] = val
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node + 1, l, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, r, idx, val);

        // Update parents : After updating child, fix parent values
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
};

int main() {
    vector<int> arr = {2, 1, 3, 4, 5};

    SegmentTree st(arr);

    cout << "Sum (1 to 3): " << st.query(0, 0, arr.size() - 1, 1, 3) << endl;

    st.update(0, 0, arr.size() - 1, 2, 10); // arr[2] = 10

    cout << "After update (1 to 3): " << st.query(0, 0, arr.size() - 1, 1, 3) << endl;

    return 0;
}
