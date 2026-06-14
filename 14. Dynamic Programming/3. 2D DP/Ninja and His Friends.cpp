/*
Ninja's Training (DP-7)
There are N days.
Each day has 3 activities (Running, Fighting, Stealth).
points[i][j] = points earned by doing activity j on day i.
You must do exactly one activity per day.
You cannot do the same activity on two consecutive days.
Find the maximum total points.
  
Ninja and His Friends (DP-13)
Given an N × M grid where each cell contains chocolates.
Alice starts at (0,0) and Bob starts at (0,M-1).
In each step, both move to the next row:
  Down-left (i+1, j-1)
  Down (i+1, j)
  Down-right (i+1, j+1)
They collect chocolates from every cell they visit.
If both land on the same cell, count its chocolates only once.
They cannot move outside the grid.
Find the maximum chocolates Alice and Bob can collect together by the time they reach the last row.
*/

class Solution {
public:
    int n, m;

    int dfs(int i, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp) {

        if(j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) return -1e8;

        if(i == n - 1) return (j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2];

        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];

        int ans = 0;

        for(int d1 = -1; d1 <= 1; d1++)
            for(int d2 = -1; d2 <= 1; d2++)
                ans = max(ans, dfs(i+1, j1+d1, j2+d2, grid, dp));

        return dp[i][j1][j2] = ((j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2]) + ans;
    }

    int solve(int N, int M, vector<vector<int>>& grid) {
        n = N; m = M;
        vector dp(n, vector(m, vector<int>(m, -1)));
        return dfs(0, 0, m-1, grid, dp);
    }
};
// _______________________________________________________

class Solution {
public:
    int solve(int n, int m, vector<vector<int>>& grid) {

        vector dp(n, vector(m, vector<int>(m, 0)));

        // Base case
        for(int j1 = 0; j1 < m; j1++) {
            for(int j2 = 0; j2 < m; j2++) {
                dp[n-1][j1][j2] = (j1 == j2) ? grid[n-1][j1] : grid[n-1][j1] + grid[n-1][j2];
            }
        }

        for(int i = n-2; i >= 0; i--) {
            for(int j1 = 0; j1 < m; j1++) {
                for(int j2 = 0; j2 < m; j2++) {
                    
                    int ans = -1e8;
                    for(int d1 = -1; d1 <= 1; d1++) {
                        for(int d2 = -1; d2 <= 1; d2++) {
                            int nj1 = j1 + d1;
                            int nj2 = j2 + d2;
                            if(nj1 >= 0 && nj1 < m && nj2 >= 0 && nj2 < m)
                                ans = max(ans, dp[i+1][nj1][nj2]);
                        }
                    }

                    dp[i][j1][j2] = ((j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2]) + ans;
                }
            }
        }

        return dp[0][0][m-1];
    }
};
