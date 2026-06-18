/*
QUESTION:
You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete at most two transactions.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Example:
Input: prices = [3, 3, 5, 0, 0, 3, 1, 4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3 - 0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4 - 1 = 3.

APPROACH:
- This problem can be solved using dynamic programming.
- We need to keep track of the number of transactions completed so far (cap) and whether we are holding a stock or not on each day.
- Define a 3D DP array `dp` where dp[i][hold][cap] represents the maximum profit achievable starting from day i while holding or not holding a stock and having completed cap transactions.
- The base case is dp[n][0][0] = dp[n][0][1] = dp[n][0][2] = dp[n][1][0] = dp[n][1][1] = dp[n][1][2] = 0, where n is the number of days.
- Iterate through each day i in reverse order.
- If holding a stock, we can either sell the stock or continue holding.
- If not holding a stock, we can either buy the stock or continue not holding.
- Return dp[0][0][0], which represents the maximum profit achievable starting from day 0 while not holding a stock and having completed 0 transactions.

COMPLEXITY ANALYSIS:
- The time complexity of this approach is O(n), where n is the number of days.
- The space complexity is O(n) due to the dp array.
- Overall, the algorithm runs in O(n) time and O(n) space.

CODE:
*/

// Refer to problem 04 for explanation

// _____________________________________________________________________________

/* Most optimized in O(1) SC

buy1 = max of all -p         or min abs value
sell1 = max of all -p1+p2    p1 is min abs value and p2 is curr value
buy2 = max of that prev transaction + min abs value of curr
sell2 = max of prev transaction + max of curr transaction

buy1 = buy2 and sell1 = sell2 if there is no 2nd transaction that is giving profit
and ignore buy1, sell1 will give the 2nd transaction limits and buy2, sell2 gives total value

prices = [3,3,5,0,0,3,1,4]

buy1  sell1  buy2  sell2
------------------------
-3      0     -3     0
-3      0     -3     0
-3      2     -3     2
 0      2      2     2
 0      2      2     2
 0      3      2     5
 0      3      2     5
 0      4      2     6
 
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int buy1 = INT_MIN;
        int sell1 = 0;

        int buy2 = INT_MIN;
        int sell2 = 0;

        for (int p : prices) {
            buy1 = max(buy1, -p);
            sell1 = max(sell1, buy1 + p);

            buy2 = max(buy2, sell1 - p);
            sell2 = max(sell2, buy2 + p);
        }

        return sell2;
    }
};
// _______________________________________________________

int getAns(vector<int>& Arr, int n, int ind, int buy, int cap, vector<vector<vector<int>>>& dp) {
    // Base case: If we reach the end of the array or run out of allowed transactions, return 0.
    if (ind == n || cap == 0)
        return 0;

    // If the result is already calculated, return it.
    if (dp[ind][buy][cap] != -1)
        return dp[ind][buy][cap];

    int profit;

    if (buy == 0) { // We can buy the stock
        profit = max(0 + getAns(Arr, n, ind + 1, 0, cap, dp),
                     -Arr[ind] + getAns(Arr, n, ind + 1, 1, cap, dp));
    }

    if (buy == 1) { // We can sell the stock
        profit = max(0 + getAns(Arr, n, ind + 1, 1, cap, dp),
                     Arr[ind] + getAns(Arr, n, ind + 1, 0, cap - 1, dp));
    }

    // Store and return the calculated profit.
    return dp[ind][buy][cap] = profit;
}

int maxProfit(vector<int>& prices, int n) {
    // Creating a 3D DP array of size [n][2][3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));

    // Call the recursive function to calculate maximum profit
    return getAns(prices, n, 0, 0, 2, dp);
}
____________________

// Tabulation
int maxProfit(vector<int>& Arr, int n) {
    // Creating a 3D DP array of size [n+1][2][3] initialized to 0
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

    // Base case: dp array is already initialized to 0, covering the base case.

    for (int ind = n - 1; ind >= 0; ind--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (buy == 0) { // We can buy the stock
                    dp[ind][buy][cap] = max(0 + dp[ind + 1][0][cap],
                                           -Arr[ind] + dp[ind + 1][1][cap]);
                }

                if (buy == 1) { // We can sell the stock
                    dp[ind][buy][cap] = max(0 + dp[ind + 1][1][cap],
                                           Arr[ind] + dp[ind + 1][0][cap - 1]);
                }
            }
        }
    }

    // The result is stored in dp[0][0][2] which represents maximum profit after the final transaction.
    return dp[0][0][2];
}
____________________________

// Space Optimization
int maxProfit(vector<int>& Arr, int n) {
    // Create two 2D arrays to store the profit information, one for the current state and one for the ahead state.
    vector<vector<int>> ahead(2, vector<int>(3, 0));
    vector<vector<int>> cur(2, vector<int>(3, 0));

    for (int ind = n - 1; ind >= 0; ind--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (buy == 0) { // We can buy the stock
                    cur[buy][cap] = max(0 + ahead[0][cap], 
                                        -Arr[ind] + ahead[1][cap]);
                }

                if (buy == 1) { // We can sell the stock
                    cur[buy][cap] = max(0 + ahead[1][cap],
                                        Arr[ind] + ahead[0][cap - 1]);
                }
            }
        }
        // Update the ahead state with the current state for the next iteration.
        ahead = cur;
    }

    return ahead[0][2];
}
