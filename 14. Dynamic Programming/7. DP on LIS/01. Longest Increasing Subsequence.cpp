/*
QUESTION:
Given an integer array nums, return the length of the longest strictly increasing subsequence.

COMPLEXITY ANALYSIS:
- The time complexity of this approach is O(n^2), where n is the length of the input array nums.
- The space complexity is O(n) due to the dp array.
- Overall, the algorithm runs in O(n^2) time and O(n) space.

CODE:
*/

// Memoization
// dp[i] = length of the Longest Increasing Subsequence that ends exactly at index i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(int i, vector<int>& nums, vector<int>& dp) {
        if (dp[i] != -1) return dp[i];

        int best = 1; // every element alone is LIS of length 1

        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                best = max(best, solve(j, nums, dp) + 1);
            }
        }
        return dp[i] = best;
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, nums, dp));
        }

        return ans;
    }
};
_____________________________________

// Tabulation
// dp[i] = length of the Longest Increasing Subsequence that ends exactly at index i
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);  // each element is LIS of length 1

    int ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}
___________________________

