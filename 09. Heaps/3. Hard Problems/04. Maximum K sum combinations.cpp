/*
Question:
Given two integer arrays A and B of size N each. A sum combination is made by adding 
one element from array A and another element from array B. Return the maximum K valid 
distinct sum combinations from all the possible sum combinations. Output array must be 
sorted in non-increasing order.

Example:
Input:
N = 2
K = 2
A[] = {3, 2}
B[] = {1, 4}
Output: {7, 6}
Explanation: 
7 -> (A: 3) + (B: 4)
6 -> (A: 2) + (B: 4)
*/

/*

:

Approach (K Maximum Sum Combinations)
Sort A and B in decreasing order
Use max heap to explore best sums first
Start from (0,0)
Push next states: (i+1, j), (i, j+1)
Use vis to avoid duplicates

TC : O(K log K)
SC : O(K)
*/

//         0,0
//     1,0       0,1
// 2,0   1,1   1,1  0,2
// We might cover 1,1 twice

vector<int> maxCombinations(int N, int K, vector<int> &A, vector<int> &B) {
    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end(), greater<int>());

    priority_queue<pair<int, pair<int,int>>> pq;
    set<pair<int,int>> vis;

    pq.push({A[0] + B[0], {0, 0}});
    vis.insert({0, 0});

    vector<int> ans;

    while (K-- && !pq.empty()) {
        auto [sum, pos] = pq.top();
        pq.pop();

        int i = pos.first;
        int j = pos.second;

        ans.push_back(sum);

        // move in A direction
        if (i + 1 < N && !vis.count({i + 1, j})) {
            pq.push({A[i + 1] + B[j], {i + 1, j}});
            vis.insert({i + 1, j});
        }

        // move in B direction
        if (j + 1 < N && !vis.count({i, j + 1})) {
            pq.push({A[i] + B[j + 1], {i, j + 1}});
            vis.insert({i, j + 1});
        }
    }

    return ans;
}
