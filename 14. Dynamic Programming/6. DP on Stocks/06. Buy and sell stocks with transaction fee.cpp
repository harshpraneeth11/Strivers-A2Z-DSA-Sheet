/*
QUESTION:
You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.
Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
Note:
- You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
- The transaction fee is only charged once for each stock purchase and sale.

Example:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

APPROACH:
- This problem can be solved using dynamic programming.
- We need to keep track of whether we are holding a stock or not on each day.
- Define a 2D DP array `dp` where dp[i][hold] represents the maximum profit achievable starting from day i while holding or not holding a stock.
- The base case is dp[n][0] = dp[n][1] = 0, where n is the number of days.
- Iterate through each day i.
- If holding a stock, we can either sell the stock or continue holding.
- If not holding a stock, we can either buy the stock or continue not holding.
- Return dp[0][0], which represents the maximum profit achievable starting from day 0 while not holding a stock.

COMPLEXITY ANALYSIS:
- The time complexity of this approach is O(n), where n is the number of days.
- The space complexity is O(n) due to the dp array.
- Overall, the algorithm runs in O(n) time and O(n) space.

CODE:
*/

// When we are selling, do subtract a fee from it

int getAns(vector<int> &Arr, int ind, int buy, int n, int fee, vector<vector<int>> &dp) {
    if (ind == n) return 0;
    if (dp[ind][buy] != -1) return dp[ind][buy];
        
    int profit;
    
    if (buy == 0) { // We can buy the stock
        profit = max(0 + getAns(Arr, ind + 1, 0, n, fee, dp), -Arr[ind] + getAns(Arr, ind + 1, 1, n, fee, dp));
    }
    
    if (buy == 1) { // We can sell the stock
        profit = max(0 + getAns(Arr, ind + 1, 1, n, fee, dp), Arr[ind] - fee + getAns(Arr, ind + 1, 0, n, fee, dp));
    }
    return dp[ind][buy] = profit;
}

int maximumProfit(int n, int fee, vector<int> &Arr) {
    vector<vector<int>> dp(n, vector<int>(2, -1));
    if (n == 0) return 0; // Edge case: No stocks to trade.
    int ans = getAns(Arr, 0, 0, n, fee, dp);
    return ans;
}

// ______________________________________________________________

int maximumProfit(int n, int fee, vector<int>& arr) {
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        // buy
        dp[i][0] = max( dp[i + 1][0], -arr[i] + dp[i + 1][1] );
        
        // sell
        dp[i][1] = max( dp[i + 1][1], arr[i] - fee + dp[i + 1][0] );
    }
    return dp[0][0];
}

// ______________________________________________________________

int maximumProfit(int n, int fee, vector<int>& arr) {
    int nextBuy = 0, nextSell = 0;

    for (int i = n - 1; i >= 0; i--) {

        int curBuy = max(nextBuy, -arr[i] + nextSell);
        int curSell = max(nextSell, arr[i] - fee + nextBuy);

        nextBuy = curBuy;
        nextSell = curSell;
    }

    return nextBuy;
}
