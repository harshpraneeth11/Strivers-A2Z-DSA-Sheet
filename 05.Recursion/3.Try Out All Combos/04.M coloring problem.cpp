/*QUESTION:
Given an undirected graph and an integer M. The task is to determine if the graph can be colored with 
at most M colors such that no two adjacent vertices of the graph are colored with the same color. 
Here coloring of a graph means the assignment of colors to all vertices. Print 1 if it is possible 
to colour vertices and 0 otherwise.

Approach:
We can solve this problem using backtracking.
1. Create a helper function called 'isPossible' that takes the graph, an array of colors assigned to vertices, the number of vertices, the color to be assigned, and the current vertex.
   - Iterate through all the adjacent vertices of the current vertex.
   - If an adjacent vertex is already colored with the same color, return false.
   - If there is no conflict, continue checking other adjacent vertices.
   - If all adjacent vertices have different colors or are uncolored, return true.
2. Create another helper function called 'solve' that takes the graph, the number of colors, the number of vertices, an array of colors assigned to vertices, and the current vertex.
   - If all vertices have been assigned colors, return true.
   - Iterate through all possible colors from 1 to M.
   - If it is possible to assign the current color to the current vertex without any conflict, assign the color and recursively call the 'solve' function for the next vertex.
   - If the 'solve' function returns true, return true.
   - If the 'solve' function returns false, try the next color.
   - If no color can be assigned to the current vertex without any conflict, return false.
3. Create the main function called 'graphColoring' that initializes an array of colors and calls the 'solve' function to check if it is possible to color the graph.
   - If the 'solve' function returns true, return true.
   - Otherwise, return false.

Time Complexity: O(M^N), where M is the number of colors and N is the number of vertices in the graph. In the worst case, we have to try all possible color combinations for all vertices.
Space Complexity: O(N), as we are using an array of colors to store the assigned colors for each vertex.

CODE:*/

// m colors, N vertices, graph[i][j] means there is a edge

class Solution {
public:

    // If there is an edge between node and k, then l and node should have different color
    bool isPossible(bool graph[101][101], vector<int>& color, int N, int col, int node) {
        for (int k = 0; k < N; k++) {
            if (graph[node][k] && color[k] == col)
                return false;
        }
        return true;
    }

    bool solve(bool graph[101][101], int m, int N, vector<int>& color, int node) {
        if (node == N) return true;

        for (int c = 1; c <= m; c++) {
            if (isPossible(graph, color, N, c, node)) {
                color[node] = c;
                if (solve(graph, m, N, color, node + 1)) return true;
                color[node] = 0; // backtrack
            }
        }
        return false;
    }

    bool graphColoring(bool graph[101][101], int m, int N) {
        vector<int> color(N, 0);
        return solve(graph, m, N, color, 0);    // start from node 0
    }
};
