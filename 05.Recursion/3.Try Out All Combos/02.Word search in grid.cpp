/*QUESTION:
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false


TC : O(M × N × 4 × 3^(L-1))
Usually written as: O(M × N × 3^L)
Why?
We can start from every cell: M × N
From the first character, there are at most 4 directions: 4
After moving to a neighboring cell, we cannot go back to the previous cell (it's marked visited), so each next step has at most 3 choices: 
3 × 3 × 3 ... (L-1 times) = 3^(L-1)

CODE:*/

class Solution {
public:
    // {i, j} are in the board and [idx] is in word
    bool dfs(int i, int j, int idx, vector<vector<char>>& board, string& word) {

        // All characters matched
        if (idx == word.size()) return true;

        int m = board.size();
        int n = board[0].size();

        // Out of bounds or character mismatch
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[idx])
            return false;

        // The letter matched, so lets make this visited (!) and check next letter
        char ch = board[i][j];
        board[i][j] = '!';

        // Explore all 4 directions
        bool found =
            dfs(i + 1, j, idx + 1, board, word) ||
            dfs(i - 1, j, idx + 1, board, word) ||
            dfs(i, j + 1, idx + 1, board, word) ||
            dfs(i, j - 1, idx + 1, board, word);

        // Backtrack
        board[i][j] = ch;

        return found;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        // Try starting the word from every cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(i, j, 0, board, word)) return true;
            }
        }

        return false;
    }
};
