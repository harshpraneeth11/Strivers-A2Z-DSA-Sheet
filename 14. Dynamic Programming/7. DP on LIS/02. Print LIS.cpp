/*
QUESTION:
Given an integer n and an array of integers, return the Longest Increasing Subsequence which is lexicographically smallest corresponding to the indices of the elements.

COMPLEXITY ANALYSIS:
- The time complexity of this approach is O(n^2), where n is the length of the input array arr.
- The space complexity is O(n) due to the dp and prevmap arrays, as well as the lis vector.
- Overall, the algorithm runs in O(n^2) time and O(n) space.

CODE:
*/

// Here, we use 1D dp vector and while loop helps us to push the elements into ans vector and we reverse it at the end

#include <bits/stdc++.h>
using namespace std;

vector<int> printLIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> dp(n, 1);
    vector<int> parent(n);

    // initialize parent pointers
    for (int i = 0; i < n; i++) parent[i] = i;

    int maxLen = 1;
    int lastIndex = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;   // store previous element
            }
        }

        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIndex = i;
        }
    }

    // reconstruct LIS
    vector<int> lis;
    int i = lastIndex;

    while (parent[i] != i) {
        lis.push_back(nums[i]);
        i = parent[i];
    }
    lis.push_back(nums[i]);

    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> lis = printLIS(nums);
    for (int x : lis) {
        cout << x << " ";
    }
}
