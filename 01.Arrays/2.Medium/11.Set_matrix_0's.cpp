/*
QUESTION:
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

Example 1:
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

Set Matrix Zeros :
Brute force) Traverse each cell.
If a cell contains 0, set all 'non-zero' elements in its entire row and column to -1 using markRow and markCol.
Now, 2nd traversal is replacing every -1 with 0.
TC : O(N*M*(N+M)) + O(N*M) and SC : O(1)

Better approach) Arrays row and col are used to track which rows and columns need to be zeroed.
Traverse the matrix. If any element is 0, mark the corresponding row[i] and col[j] as 1.
Traverse the matrix again. Set matrix[i][j] to 0 if row[i] or col[j] is 1.
TC : O(N*M) and SC : O(N+M)

Optimal approach)
i) Instead of separate arrays for rows and columns, use the first row and column of the matrix itself.
ii) Additionally, use a variable col0 to track whether the first column should be zeroed.
Traverse the matrix. If a cell is 0, set the corresponding row marker (matrix[i][0]) and column marker (matrix[0][j]). If the zero is in the first column, set col0 to 0.
iii) Traverse the matrix from (1,1) to (n-1, m-1). Set matrix[i][j] to 0 if its row or column marker is 0.
iv) If the top-left cell (matrix[0][0]) is 0, zero out the entire first row. If col0 is 0, zero out the entire first column.
TC : O(N*M) and SC : O(1)

*/

// Using row0, col0 both code to be large

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int col0 = 1;

        // Mark rows and columns
        for(int i = 0; i < m; i++) {
            if(matrix[i][0] == 0) col0 = 0;

            for(int j = 1; j < n; j++) {
                if(matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        // Confusion is what if 1st row or 1st col or (0, 0) is zero
        // If 1st col have a 0 or (0, 0) is 0, then col0 becomes 0
        // If 1st row have a 0 and (0, 0) is not 0, then the row's left most element becomes 0, top most is already 0


        // Come from end, as we are using first row and col as markers
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 1; j--) {       // only from n-1 to 1, not 0
                if(matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }

            if(col0 == 0)
                matrix[i][0] = 0;
        }
    }
};
