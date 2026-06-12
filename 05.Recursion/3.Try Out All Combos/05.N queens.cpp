/**
 * Question: The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 *
Example 1:


Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

 * Approach:
 * 1. Use backtracking to solve the n-queens puzzle.
 * 2. Start with an empty chessboard and try placing queens in each row, ensuring that no two queens threaten each other.
 * 3. Use row, column, and diagonal constraints to validate the queen placements.
 * 4. If a valid configuration is found, add it to the list of solutions.
 *
 * Time Complexity: O(N!), where N is the input parameter representing the size of the chessboard.
 *   - In the worst case, there can be N! possible configurations to check.
 *   - However, with the pruning technique used in backtracking, the actual runtime is much less than N! in most cases.
 *
 * Space Complexity: O(N^2), where N is the input parameter representing the size of the chessboard.
 *   - The space is used to store the chessboard configuration and the auxiliary arrays for tracking the used columns and diagonals.
 */

class Solution {
public:
    vector<vector<string>> ans;

    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();

        // Check column
        for (int r = 0; r < row; r++) {
            if (board[r][col] == 'Q')
                return false;
        }

        // We need to check row-1 to above rows and columns also similarly 
        // Check upper-left diagonal 
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--) {
            if (board[r][c] == 'Q')
                return false;
        }

        // Check upper-right diagonal
        for (int r = row - 1, c = col + 1; r >= 0 && c < n; r--, c++) {
            if (board[r][c] == 'Q')
                return false;
        }

        return true;
    }

    void solve(int row, vector<string>& board) {
        int n = board.size();

        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col)) {
                board[row][col] = 'Q';
                solve(row + 1, board);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        solve(0, board);
        return ans;
    }
};
