/* QUESTION:

Given a weighted, directed and connected graph of V vertices and E edges, Find the shortest distance of all the vertex's from the source vertex S.
Note: If the Graph contains a negative cycle then return an array consisting of only -1.

Example:

Input: E = [[0,1,5],[1,0,3],[1,2,-1],[2,0,1]], S = 2
Output: 1 6 0
Explanation:
For nodes 2 to 0, we can follow the path - 2 -> 0. This has a distance of 1.
For nodes 2 to 1, we can follow the path - 2 -> 0 -> 1, which has a distance of 1 + 5 = 6.

CODE:
*/

/*
BellmanFord is Dijkstra applied 'V' times. If then, it is ElogV * V

Two follow-up questions about the algorithm: 
1. Why do we need exact N-1 iterations?
0->1->2->3->4
In 1st iteration, 0->1 comes
In 2nd iteration, 1->2, then 2->3 and so on... It is because, dist[1], [2], ... will be inf, so they won't run in 1st iteration
Let’s try to first understand his using an example:
In the above graph, the algorithm will minimize the distance of the ith node in the ith iteration like dist[1] 
will be updated in the 1st iteration, dist[2] will be updated in the 2nd iteration, and so on. So we will need 
a total of 4 iterations(i.e. N-1 iterations) to minimize all the distances as dist[0] is already set to 0.
Note: Points to remember since, in a graph of N nodes we will take at most N-1 edges to reach from the first to 
the last node, we need exact N-1 iterations. It is impossible to draw a graph that takes more than N-1 edges to reach any node. 



1. Negative Weights:
Dijkstra's Algorithm: Does not handle negative weights. It assumes all edge weights are non-negative.
Bellman-Ford Algorithm: Handles negative weights and detects negative-weight cycles in the graph.

2. Complexity:
Dijkstra's Algorithm: O(E + VlogV)
Bellman-Ford Algorithm: O(V.E)

Bellman ford is not O(V.Degree), it is O(V.E), observe properly.
6 nodes and each node have 3 edges. Total = 9 edges. Then we are checking all 9 edges for n-1 times.
Bellman ford helps to get shortest path for negative edges
For negative cycles, it can detect, but it can't give correct path. No algo can give for this case.

*/

const int INF = INT_MAX;

// Function to implement the Bellman-Ford algorithm
void bellmanFord(int vertices, int edges, vector<tuple<int, int, int>> &graph, int source) {
    vector<int> distance(vertices, INF);
    distance[source] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 0; i < vertices - 1; i++) {
        for (const auto &[u, v, weight] : graph) {
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto &[u, v, weight] : graph) {
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return;
        }
    }
}
