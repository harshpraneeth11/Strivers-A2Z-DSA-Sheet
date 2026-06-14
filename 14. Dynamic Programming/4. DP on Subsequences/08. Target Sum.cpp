/*
Problem Description:

We are given an array ‘ARR’ of size ‘N’ and a number ‘Target’. Our task is to build an expression from the given array where we 
can place a ‘+’ or ‘-’ sign in front of an integer. We want to place a sign in front of every integer of the array and 
get our required target. We need to count the number of ways in which we can achieve our required target.

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

CODE:
*/

// Memoization

// TC : O(N*K) : There are N*K states therefore at max ‘N*K’ new problems will be solved.
// SC : O(N*K) + O(N) : We are using a recursion stack space(O(N)) and a 2D array ( O(N*K)).

int helper(int idx, int tgt, vector<int>& nums, vector<vector<int>>& memo) {
    if (idx == 0) {
        if (tgt == 0 && nums[0] == 0)      return 2;
        if (tgt == 0 || tgt == nums[0])       return 1;
        return 0;
    }   

    if (memo[idx][tgt] != -1)      return memo[idx][tgt];

    int exclude = helper(idx - 1, tgt, nums, memo);
    
    int include = 0;
    if (nums[idx] <= tgt) include = helper(idx - 1, tgt - nums[idx], nums, memo);
    return memo[idx][tgt] = (exclude + include);
}

int findWays(int n, int tgt, vector<int>& nums) {
    int totalSum = 0;
    for (int i = 0; i < nums.size(); i++) {
        totalSum += nums[i];
    }

    if (totalSum - tgt < 0)       return 0;
    if ((totalSum - tgt) % 2 == 1)       return 0;

    int s2 = (totalSum - tgt) / 2;
    vector<vector<int>> memo(n, vector<int>(s2 + 1, -1));
    return helper(n - 1, s2, nums, memo);
}
__________________________________


// ----------------------------------------------------------------------
// DP (2D version)

const int mod = 1e9 + 7;

int countWays(vector<int>& nums, int targetSum) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(targetSum + 1, 0));

    // base case
    if (nums[0] == 0) {
        dp[0][0] = 2;
    } else {
        dp[0][0] = 1;

        if (nums[0] <= targetSum) {
            dp[0][nums[0]] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int sum = 0; sum <= targetSum; sum++) {
            int notTake = dp[i - 1][sum];
            
            int take = 0;
            if (nums[i] <= sum) {
                take = dp[i - 1][sum - nums[i]];
            }
            dp[i][sum] = (notTake + take) % mod;
        }
    }
    return dp[n - 1][targetSum];
}


// ----------------------------------------------------------------------
// Space Optimized (1D version)

const int mod = 1e9 + 7;

int countWays(vector<int>& nums, int targetSum) {
    int n = nums.size();
    vector<int> prev(targetSum + 1, 0);

    // base case
    if (nums[0] == 0) {
        prev[0] = 2;
    } else {
        prev[0] = 1;

        if (nums[0] <= targetSum) {
            prev[nums[0]] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        vector<int> curr(targetSum + 1, 0);
        for (int sum = 0; sum <= targetSum; sum++) {
            int notTake = prev[sum];

            int take = 0;
            if (nums[i] <= sum) {
                take = prev[sum - nums[i]];
            }
            curr[sum] = (notTake + take) % mod;
        }
        prev = curr;
    }
    return prev[targetSum];
}
