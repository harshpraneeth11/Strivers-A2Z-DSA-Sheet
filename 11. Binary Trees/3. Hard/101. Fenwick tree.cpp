/*
Always use 1-based indexing
i += (i & -i) → move upward
i -= (i & -i) → move downward
Range query = prefix(r) - prefix(l-1)

size = n + 1 because we use 1-based indexing
*/

#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
    vector<int> bit;
    int n;

public:
    // constructor
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0); // 1-based indexing
    }

    // build from array (O(n log n))
    FenwickTree(vector<int> &arr) {
        n = arr.size();
        bit.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }

    // update index i by adding val
    void update(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += (i & -i);
        }
    }
/*
We are saying:  “Add val to index i, and all responsible parent nodes”
Example flow: If i = 3:
update bit[3]           jump to bit[4]
jump to bit[8] ...      (until out of range)

Each index stores sum of a block.
So update propagates to all blocks that include this index.
*/

    // prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= (i & -i);
        }
        return sum;
    }

    // range sum [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    vector<int> arr = {2, 1, 3, 4, 5};

    FenwickTree ft(arr);

    cout << "Prefix sum up to 3: " << ft.query(3) << endl;   // 2+1+3 = 6
    cout << "Range sum (2 to 4): " << ft.rangeQuery(2, 4) << endl; // 1+3+4 = 8

    ft.update(3, 2); // arr[3] += 2 → 3 becomes 5

    cout << "After update:" << endl;
    cout << "Prefix sum up to 3: " << ft.query(3) << endl;

    return 0;
}
