/*
QUESTION:
Given an array of positive integers, find the maximum length of a Bitonic subsequence.
A subsequence of an array is called Bitonic if it is first strictly increasing and then strictly decreasing.

Approach (Longest Bitonic Subsequence)
1. Compute LIS (Longest Increasing Subsequence) ending at every index i.
    lis[i] = length of the longest increasing subsequence ending at i.
2. Compute LDS (Longest Decreasing Subsequence) starting from every index i.
    lds[i] = length of the longest decreasing subsequence starting at i.
3. Treat each index i as the peak of a bitonic subsequence.
    Length of bitonic subsequence with peak at i:
    lis[i] + lds[i] - 1
    Subtract 1 because nums[i] is counted in both LIS and LDS.
4. Take the maximum value over all indices.
5. (If required by the problem) only consider indices where:
    lis[i] > 1 && lds[i] > 1
    so that the sequence has both an increasing and a decreasing part.

Time Complexity: O(n²)
Space Complexity: O(n)

CODE:
*/

// Tabulation
int LongestBitonicSequence(vector<int>& nums) {
    int n = nums.size();
    vector<int> lis(n, 1), lds(n, 1);

    // LIS ending at i
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    // LDS starting at i
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[j] < nums[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, lis[i] + lds[i] - 1);
    }

    return ans;
}

// _________________________________________________________________

// Memoization
class Solution {
public:
    int LIS(int i, vector<int>& nums, vector<int>& dp1) {
        if (dp1[i] != -1) return dp1[i];

        int ans = 1;

        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i]) {
                ans = max(ans, 1 + LIS(prev, nums, dp1));
            }
        }

        return dp1[i] = ans;
    }

    int LDS(int i, vector<int>& nums, vector<int>& dp2) {
        if (dp2[i] != -1) return dp2[i];

        int ans = 1;

        for (int next = i + 1; next < nums.size(); next++) {
            if (nums[next] < nums[i]) {
                ans = max(ans, 1 + LDS(next, nums, dp2));
            }
        }

        return dp2[i] = ans;
    }

    int LongestBitonicSequence(vector<int> nums) {
        int n = nums.size();

        vector<int> dp1(n, -1); // LIS ending at i
        vector<int> dp2(n, -1); // LDS starting at i

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int inc = LIS(i, nums, dp1);
            int dec = LDS(i, nums, dp2);

            ans = max(ans, inc + dec - 1);
        }

        return ans;
    }
};
