Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
You have the following three operations permitted on a word:
Insert a character, Delete a character, Replace a character
 
Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 
Constraints:
0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.


class Solution {
public:
    int solve(int i, int j, string &s, string &t,
              vector<vector<int>> &dp) {

        // word1 exhausted -> insert remaining chars of word2
        if (i == s.size())
            return t.size() - j;

        // word2 exhausted -> delete remaining chars of word1
        if (j == t.size())
            return s.size() - i;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j])
            return dp[i][j] = solve(i + 1, j + 1, s, t, dp);

        int insertOp = 1 + solve(i, j + 1, s, t, dp);
        int deleteOp = 1 + solve(i + 1, j, s, t, dp);
        int replaceOp = 1 + solve(i + 1, j + 1, s, t, dp);

        return dp[i][j] = min({insertOp, deleteOp, replaceOp});
    }

    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        return solve(0, 0, word1, word2, dp);
    }
};

// _____________________________________________________________________

class Solution {
public:
    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // word2 exhausted -> delete remaining chars of word1
        for (int i = 0; i <= n; i++)
            dp[i][m] = n - i;

        // word1 exhausted -> insert remaining chars of word2
        for (int j = 0; j <= m; j++)
            dp[n][j] = m - j;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {

                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                } else {
                    int insertOp  = 1 + dp[i][j + 1];
                    int deleteOp  = 1 + dp[i + 1][j];
                    int replaceOp = 1 + dp[i + 1][j + 1];

                    dp[i][j] = min({insertOp, deleteOp, replaceOp});
                }
            }
        }

        return dp[0][0];
    }
};
// _____________________________________________________________________

class Solution {
public:
    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<int> ahead(m + 1, 0), curr(m + 1, 0);

        // dp[n][j] = m - j
        for (int j = 0; j <= m; j++)
            ahead[j] = m - j;

        for (int i = n - 1; i >= 0; i--) {

            // dp[i][m] = n - i
            curr[m] = n - i;

            for (int j = m - 1; j >= 0; j--) {

                if (word1[i] == word2[j]) {
                    curr[j] = ahead[j + 1];
                } else {

                    int insertOp  = 1 + curr[j + 1];
                    int deleteOp  = 1 + ahead[j];
                    int replaceOp = 1 + ahead[j + 1];

                    curr[j] = min({insertOp, deleteOp, replaceOp});
                }
            }

            ahead = curr;
        }

        return ahead[0];
    }
};
