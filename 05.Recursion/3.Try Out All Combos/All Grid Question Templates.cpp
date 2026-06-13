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

// Visited had to be made again 1 na ?

// Type 1 : Check a path exists or not

// DFS approach
// TC : O(n²)
// SC : O(n²)   (recursion stack + visited)

bool dfs(int i, int j, vector<vector<int>>& m, int n) {

    if (i < 0 || i >= n || j < 0 || j >= n || m[i][j] == 0)
        return false;

    if (i == n - 1 && j == n - 1)
        return true;

    m[i][j] = 0;   // visited

    bool found =
        dfs(i + 1, j, m, n) || dfs(i, j - 1, m, n) ||
        dfs(i, j + 1, m, n) || dfs(i - 1, j, m, n);

    return found;
}

bool pathExists(vector<vector<int>>& m, int n) {
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return false;
    return dfs(0, 0, m, n);
}

// BFS approach
// TC: O(n²)
// SC: O(n²)

bool pathExists(vector<vector<int>>& m, int n) {

    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return false;

    queue<pair<int,int>> q;
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    q.push({0, 0});
    vis[0][0] = true;

    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};

    while (!q.empty()) {

        auto [i, j] = q.front();
        q.pop();

        if (i == n - 1 && j == n - 1) return true;

        for (int k = 0; k < 4; k++) {

            int ni = i + dr[k];
            int nj = j + dc[k];

            if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                m[ni][nj] == 1 && vis[ni][nj] == 0) {
                vis[ni][nj] = true;
                q.push({ni, nj});
            }
        }
    }
    return false;
}
// _____________________________________________________________________________________

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
// _____________________________________________________________________

// Type 3 : Count all path (4 directions)
int solve(int i, int j, vector<vector<int>>& m, int n) {

    if (i == n - 1 && j == n - 1) return 1;
    
    if (i < 0 || i >= n || j < 0 || j >= n || m[i][j] == 0) return 0;

    m[i][j] = 0;   // mark visited
    int paths = 0;

    paths += solve(i + 1, j, m, n); // D
    paths += solve(i, j - 1, m, n); // L
    paths += solve(i, j + 1, m, n); // R
    paths += solve(i - 1, j, m, n); // U

    m[i][j] = 1;   // backtrack
    return paths;
}

int countPaths(vector<vector<int>>& m, int n) {
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return 0;
    return solve(0, 0, m, n);
}
// _______________________________________________________________________

// Type 4 : Count all Paths (Right, Down only)

// Recursive counting 
// Here, there will be no cycles. So, no need of visited array.
int solve(int i, int j, int n) {

    if (i == n - 1 && j == n - 1) return 1;
    if (i >= n || j >= n) return 0;
    return solve(i + 1, j, n) + solve(i, j + 1, n);
}

// Memoization (EXpected)
int solve(int i, int j, vector<vector<int>>& dp, int m, int n) {
    if (i == m - 1 && j == n - 1) return 1;
    if (i >= m || j >= n) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solve(i + 1, j, dp, m, n) + solve(i, j + 1, dp, m, n);
}

// Tabulation
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[m - 1][n - 1] = 1;

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {

            if (i == m - 1 && j == n - 1) continue;

            int down = 0;
            int right = 0;

            if (i + 1 < m) down = dp[i + 1][j];
            if (j + 1 < n) right = dp[i][j + 1];
            dp[i][j] = down + right;
        }
    }
    return dp[0][0];
}

// Space optimized using curr, prev can also be done here.

// _______________________________________________________

// Type 5 : Shortest path distance
int shortestDistance(vector<vector<int>>& m, int n) {

    if (m[0][0] == 0 || m[n-1][n-1] == 0)
        return -1;

    queue<pair<int,int>> q;
    vector<vector<int>> dist(n, vector<int>(n, -1));

    q.push({0, 0});
    dist[0][0] = 0;

    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};

    while (!q.empty()) {

        auto [r, c] = q.front();
        q.pop();

        if (r == n-1 && c == n-1)
            return dist[r][c];

        for (int k = 0; k < 4; k++) {

            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < n &&
                nc >= 0 && nc < n &&
                m[nr][nc] == 1 &&
                dist[nr][nc] == -1) {

                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return -1;
}
// _____________________________________________________________________

// Type 6 : Shortest path
struct Node {       // main thing, store this node in BFS queue
    int i, j;
    string path;
};

string shortestPath(vector<vector<int>>& m, int n) {

    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return "";

    queue<Node> q;
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    q.push({0, 0, ""});
    vis[0][0] = true;

    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};
    char dir[] = {'D', 'L', 'R', 'U'};

    while (!q.empty()) {

        auto cur = q.front();
        q.pop();

        if (cur.i == n - 1 && cur.j == n - 1) return cur.path;

        for (int k = 0; k < 4; k++) {

            int ni = cur.i + dr[k];
            int nj = cur.j + dc[k];

            if (ni >= 0 && ni < n && nj >= 0 && nj < n && 
                m[ni][nj] == 1 && vis[ni][nj] == 0) {

                vis[ni][nj] = true;
                q.push({ni, nj, cur.path + dir[k]});
            }
        }
    }

    return "";
}
// _____________________________________________________________________

// Type 7 : Minimum Cost Path - Dijkstra

/*
1 3 1
1 5 1
4 2 1

Unweighted Grid  → BFS
Weighted Grid    → Dijkstra
Let: V = n*m, E ≈ 4*n*m
Time  = O(V log V) = O(n*m*log(n*m))
Space = O(n*m)
*/

int minimumCostPath(vector<vector<int>>& grid) {

    int n = grid.size();
    int m = grid[0].size();

    priority_queue<     
        pair<int,pair<int,int>>,
        vector<pair<int,pair<int,int>>>,
        greater<pair<int,pair<int,int>>>
    > pq;       // {value, {row, col}}

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    dist[0][0] = grid[0][0];

    pq.push({grid[0][0], {0, 0}});

    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};

    while (!pq.empty()) {

        auto [cost, pos] = pq.top();
        pq.pop();

        auto [r, c] = cos;

        if (r == n - 1 && c == m - 1) return cost;
        if (cost > dist[r][c]) continue;

        for (int k = 0; k < 4; k++) {

            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int newCost = cost + grid[nr][nc];
                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    pq.push({newCost, {nr, nc}});
                }
            }
        }
    }

    return -1;
}
