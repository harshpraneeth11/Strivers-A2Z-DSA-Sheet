/*QUESTION:
Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at 
(N - 1, N - 1). Find all possible paths that the rat can take to reach from source to destination. 
The directions in which the rat can move are 'U'(up), 'D'(down), 'L' (left), 'R' (right). 
Value 0 at a cell in the matrix represents that it is blocked and rat cannot move to it 
while value 1 at a cell in the matrix represents that rat can be travel through it.

Example 1:

Input:
N = 4
m[][] = {{1, 0, 0, 0},
         {1, 1, 0, 1}, 
         {1, 1, 0, 0},
         {0, 1, 1, 1}}
Output:
DDRDRR DRDDRR
Explanation:
The rat can reach the destination at 
(3, 3) from (0, 0) by two paths - DRDDRR 
and DDRDRR, when printed in sorted order 
we get DDRDRR DRDDRR.


CODE:*/

// ___________________________________________________________________________

// Type 2 : Print all paths
// There can be more than 1 possible case
bool isValid(int i, int j, vector<vector<int>>& m, int n) {
    if (i < 0 || i >= n || j < 0 || j >= n || m[i][j] == 0)
        return false;
    return true;
}

void solve(int i, int j, string temp, vector<string>& ans, vector<vector<int>>& m, int n) {
    if (i == n - 1 && j == n - 1) {
        ans.push_back(temp);
        return;
    }

    if (!isValid(i, j, m, n))
        return;

    m[i][j] = 0;

    solve(i, j - 1, temp + 'L', ans, m, n);
    solve(i, j + 1, temp + 'R', ans, m, n);
    solve(i - 1, j, temp + 'U', ans, m, n);
    solve(i + 1, j, temp + 'D', ans, m, n);

    m[i][j] = 1;
}

vector<string> findPath(vector<vector<int>>& m, int n) {
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0)
        return {};

    vector<string> ans;
    string temp = "";
    solve(0, 0, temp, ans, m, n);
    return ans;
}
