/*
QUESTION:
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
- '?' Matches any single character.
- '*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

APPROACH:
- This problem can be solved using dynamic programming.
- Let dp[i][j] represent whether the substring of s up to index i can be matched with the substring of p up to index j.
- If s[i] equals p[j] or p[j] is '?', the characters match and we move diagonally to check the next characters.
- If p[j] is '*', we have two options:
  1. Move vertically up (skip the '*').
  2. Move horizontally left (count '*' as matching zero characters).
- Base cases: When both i and j are -1, return true. When only j is -1, check if the remaining characters in p are all '*'.
- Return dp[n-1][m-1], where n is the length of s and m is the length of p.

COMPLEXITY ANALYSIS:
- The time complexity of this approach is O(n * m), where n is the length of string s and m is the length of string p.
- The space complexity is O(n * m) due to the dp array.
- Overall, the algorithm runs in O(n * m) time and O(n * m) space.

CODE:
*/
/*
Wild Card Matching : 
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

Regular Expression Matching :
'.' Matches any single character
'*' Matches zero or more of the preceding element
*/

bool allStars(int i, string& p) {
    for (int j = i; j >= 0; j--) {
        if (p[j] != '*') return false;
    }
    return true;
}

int fmemo(int i, int j, string& s, string& p, vector<vector<int>>& dp) {
    if (i < 0 && j < 0) return true;
    if (j < 0 && i >= 0) return false;
    if (i < 0 && j >= 0) {
        if (allStars(j, p)) return true;
        return false;
    }
    
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == p[j] || p[j] == '?')
        return dp[i][j] = fmemo(i - 1, j - 1, s, p, dp);
    else {
        if (p[j] == '*')
            return dp[i][j] = (fmemo(i - 1, j, s, p, dp) || fmemo(i, j - 1, s, p, dp));
        return dp[i][j] = false;
    }
}

bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return fmemo(n - 1, m - 1, s, p, dp);
}

// ________________________________________________________

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true;

        // Pattern vs empty string
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*')
                dp[0][j] = dp[0][j - 1];
            else
                break;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
                else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }
};
