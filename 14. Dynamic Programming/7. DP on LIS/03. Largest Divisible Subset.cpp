/*
QUESTION:
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
- answer[i] % answer[j] == 0, or
- answer[j] % answer[i] == 0
If there are multiple solutions, return any of them.

Approach :
Sort the array so that for any valid divisible pair, the smaller number comes before the larger one.
Let dp[i] = length of the largest divisible subset ending at nums[i].
For every i, check all j < i:
If nums[i] % nums[j] == 0, then nums[i] can extend the subset ending at j.
Update dp[i] = max(dp[i], dp[j] + 1).
Store the parent index of each element to reconstruct the subset.
Start from the index with maximum dp value and follow parent pointers to build the answer.

Time Complexity: O(n²)
Space Complexity: O(n)

CODE:
*/

/*
The current element needs to be divisible by the prev, it is enough
1, 2, 4, 8, 16
If 16 is divisible by 8, then the earlier elements are simply factors of 8, so they will also be divisible by 16
It is good to do using tabulation, we can also do using memoization, but it is lengthy code
*/

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    int maxLen = 1;
    int lastIdx = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 &&
                dp[j] + 1 > dp[i]) {

                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }

        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIdx = i;
        }
    }

    vector<int> ans;
    while (lastIdx != -1) {
        ans.push_back(nums[lastIdx]);
        lastIdx = parent[lastIdx];
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
