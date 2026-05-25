/*
QUESTION:
Given a weighted, undirected, and connected graph of V vertices and an adjacency list 'adj', where 'adj[i]' is a list of lists containing two integers where the first integer of each list j denotes there is an edge between node i and node j, and the second integer corresponds to the weight of that edge. You are also given the source vertex S. You need to find the shortest distance of all vertices from the source vertex S. You have to return a list of integers denoting the shortest distance between each node and the source vertex S.

APPROACH:
- We can use Dijkstra's algorithm to find the shortest distance from the source vertex to all other vertices in a weighted graph.
- The algorithm maintains a priority queue (min-heap) to store the vertices based on their tentative distances from the source vertex. We start with the source vertex and update the distances of its neighbors, pushing them into the priority queue.
- We continue this process until all vertices are visited and their distances are finalized. The priority queue ensures that we always pick the vertex with the minimum tentative distance for processing.
- We initialize the distance array 'dis' with a large value (infinity) for all vertices, except the source vertex whose distance is set to 0.
- We push the source vertex into the priority queue along with its distance, and then perform Dijkstra's algorithm.
- After the algorithm completes, we have the shortest distances of all vertices from the source vertex in the 'dis' array.

COMPLEXITY ANALYSIS:
- Time Complexity: O(E + log(V)), where E is the number of edges and V is the number of vertices in the graph. The time complexity is dominated by the priority queue operations in Dijkstra's algorithm.
- Space Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph. We use additional space for the adjacency list, the distance array, and the priority queue.
*/
/*
In the set, we save space, as for a particualr node, we will be having only the shortest possible distance one. i.e, {5 units, 4th node}  {6 units, 4th node}
In PQ, both can exist, but in set, only 1st one exists

TC : O(ElogV)
There are E edges and for each, it takes logV to retrive and insert into PQ, set
SC : O(E + V)
For adjList storage, dist vector storage

PQ : for dense graphs, where redundant entries are not significant
Set : for sparse graphs, as it significant
*/

// pq.push({s, 0}) is correct. Braces are important

vector<int> dijkstra(int n, vector<vector<int>> adj[], int s){
    // priority_queue<int, vector<int>, greater<int>> pq;
    
    // {wt, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<int> dist(n, 1e9);
    dist[s] = 0;
    pq.push(0, s);

    while(!pq.empty()) {
        int u = pq.top().second;        // there is no pq.top().second and pq.top()[2]
        // here dist[v] = pq.top().first, because we push a node multiple times

        for(auto it : adj[u]) {
            int v = it[0], wt = it[1];
            if(dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push(dist[v], v);
            }
        }
    }
    return dist;
}
________________________________________________

vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    set<pair<int,int>> st; 
    vector<int> dist(V, 1e9); 
    
    st.insert({0, S});                 // push => insert
    dist[S] = 0;
    
    while(!st.empty()) {
        auto it = *(st.begin());        // accessed like this
        int node = it.second; 
        int dis = it.first; 
        st.erase(it);                     // pop => erase
        
        for(auto it : adj[node]) {
            int adjNode = it[0]; 
            int edgW = it[1]; 
            
            if(dis + edgW < dist[adjNode]) {
                if(dist[adjNode] != 1e9)  st.erase({dist[adjNode], adjNode});  // Not needed actually, as anyways in the next 2nd line is wrong
                // Here, both old one and new one co exist, if we don't erase the old one
                dist[adjNode] = dis + edgW; 
                st.insert({dist[adjNode], adjNode});         
            }
        }
    }
    return dist; 
}

