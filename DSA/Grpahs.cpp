Basic Graph Implementation in C++
in adj - list and matric

1. Traversal
   i. BFS
      vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        int vec[V] = {0};
        vec[0] = 1;
        
        queue<int> q;
        q.push(0);
        
        vector<int> bfs;
        
        while(!q.empty()){
            int node = q.front();
            q.pop();
            
            bfs.push_back(node);
            
            for(auto i:adj[node]){
                if(!vec[i]){
                    vec[i] = 1;
                    q.push(i);
                }
            }
        }
        
        return bfs;
       }

  ii. DFS
    void dfs(int node, int vis[] , vector<int> adj[] , vector<int>& ans){
        vis[node] = 1;
        ans.push_back(node);
        
        for(auto i:adj[node]){
            if(!vis[i]){
                dfs(i, vis, adj, ans);
            }
        }
    }
  
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        int vis[V] = {0};
        int start = 0;
        vector<int> ans;
        
        dfs(start , vis , adj , ans);
        
        return ans;
    }

    QUESTION REALTED TO TRAVERSAL(?)


2. Cycle Detection
   a. in un-directed graph
      i. using BFS(for connected components)
        bool bfs(int node, vector<int> adj[], int vis[]) {
            queue<pair<int, int>> q; // pair of node and parent
            q.push({node, -1});
            vis[node] = 1;

            while(!q.empty()) {
                auto [curr, parent] = q.front();
                q.pop();

                for(auto i:adj[curr]) {
                    if(!vis[i]) {
                        vis[i] = 1;
                        q.push({i, curr});
                    } else if(i != parent) {
                        return true; // Cycle detected
                    }
                }
            }
            return false; // No cycle detected
        }

        bool isCycle(int V, vector<int> adj[]) {
            int vis[V] = {0};

            for(int i = 0; i < V; i++) {
                if(!vis[i]) {
                    if(bfs(i, adj, vis)) return true;
                }
            }
            return false; // No cycle detected
        }
        
      ii. using DFS
         bool dfs(int node, int parent, vector<int> adj[], int vis[]) {
            vis[node] = 1;

            for(auto i:adj[node]){
                if(!vis[i]){
                    if(dfs(i, node, adj, vis)) return true;
                } else if(i != parent) {
                    return true; // Cycle detected
                }
            }
            return false; // No cycle detected
        }
        bool isCycle(int V, vector<int> adj[]) {
            int vis[V] = {0};

            for(int i = 0; i < V; i++){
                if(!vis[i]){
                    if(dfs(i, -1, adj, vis)) return true;
                }
            }
            return false; // No cycle detected
        }

    b. in directed graph
       i. using DFS
          bool dfs(int node, vector<int> adj[], int vis[], int pathVis[]) {
            vis[node] = 1;
            pathVis[node] = 1;

            for(auto i:adj[node]){
                if(!vis[i]){
                    if(dfs(i, adj, vis, pathVis)) return true;
                } else if(pathVis[i]) {
                    return true; // Cycle detected
                }
            }
            pathVis[node] = 0; // Backtrack
            return false; // No cycle detected
        }
        bool isCyclic(int V, vector<int> adj[]) {
            int vis[V] = {0};
            int pathVis[V] = {0};

            for(int i = 0; i < V; i++){
                if(!vis[i]){
                    if(dfs(i, adj, vis, pathVis)) return true;
                }
            }
            return false; // No cycle detected
        }
      ii. using BFS(kahns Algo -> topo sort)
          bool isCycle(int V, vector<int> adj[]){
            int indegree[V] = {0};
            vector<int> topo;
            for(int i=0 ; i<V ; i++){
                for(auto it:adj[i]){
                    indegree[it]++;
                }
            }

            queue<int> q;
            for(int i=0 ; i<V ; i++){
                if(indegree[i] == 0){
                    q.push(i);
                }
            }

            while(!q.empty()){
                int node = q.front();
                q.pop();
                topo.push_back(node);

                for(auto it:adj[node]){
                    indegree[it]--;
                    if(indegree[it] == 0){
                        q.push(it);
                    }
                }
            }

            if(topo.size() == V) {
                return false; // No cycle detected
            } else {
                return true; // Cycle detected
            }
        }

3. Topological Sort - used only on DAG(Directed Acyclic Graph)
    -> linear ordering of vertices such that for every directed edge u -> v, 
       vertex u comes before v in the ordering.
   a. using DFS
      void dfs(int node, vector<int> adj[], int vis[], stack<int>& st) {
          vis[node] = 1;

          for(auto i:adj[node]){
              if(!vis[i]){
                  dfs(i, adj, vis, st);
              }
          }
          st.push(node); // Push after visiting all adjacent nodes
      }

      vector<int> topoSort(int V, vector<int> adj[]) {
          int vis[V] = {0};
          stack<int> st;

          for(int i = 0; i < V; i++){
              if(!vis[i]){
                  dfs(i, adj, vis, st);
              }
          }

          vector<int> topo;
          while(!st.empty()){
              topo.push_back(st.top());
              st.pop();
          }
          return topo;
      }

   b. using BFS(Kahns Algorithm)
      - This algorithm is based on the concept of in-degrees.
      vector<int> topoSort(int V, vector<int> adj[]) {
          int indegree[V] = {0};
          for(int i = 0; i < V; i++){
              for(auto it:adj[i]){
                  indegree[it]++;
              }
          }

          queue<int> q;
          for(int i = 0; i < V; i++){
              if(indegree[i] == 0){
                  q.push(i);
              }
          }

          vector<int> topo;
          while(!q.empty()){
              int node = q.front();
              q.pop();
              topo.push_back(node);

              for(auto it:adj[node]){
                  indegree[it]--;
                  if(indegree[it] == 0){
                      q.push(it);
                  }
              }
          }
          
          return topo;
       }

4. Shortest Path Algos
   i. Shortest Path in UG 
      a. using topo sort
        vector<int> shortestPath(int N, vector<vector<int>>& edges) {
            vector<int> adj[N];
            for(auto& edge : edges) {
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]); // For undirected graph
            }
    
            vector<int> topo = topoSort(N, adj); // call any from above
            vector<int> dist(N, INT_MAX);
            dist[0] = 0;
    
            for(int i = 0; i < N; i++) {
                int node = topo[i];
                for(auto it : adj[node]) {
                    if(dist[node] + 1 < dist[it]) {
                        dist[it] = dist[node] + 1;
                    }
                }
            }
            
            return dist;
        }
      b. Shortest Path in UG using BFS
        vector<int> shortestPath(int N, vector<vector<int>>& edges) {
            vector<int> adj[N];
            for(auto& edge : edges) {
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]); // For undirected graph
            }
    
            vector<int> dist(N, INT_MAX);
            dist[0] = 0;
    
            queue<int> q;
            q.push(0);
    
            while(!q.empty()) {
                int node = q.front();
                q.pop();
    
                for(auto it : adj[node]) {
                    if(dist[node] + 1 < dist[it]) {
                        dist[it] = dist[node] + 1;
                        q.push(it);
                    }
                }
            }
            
            return dist;
        } 
    
    ii. Dijkstra's Algorithm(can also use set)
        vector<int> dijkstra(int V, vector<vector<int>>& adj, int S) {
            vector<int> dist(V, INT_MAX);
            dist[S] = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, S}); // {distance, node}

            while(!pq.empty()) {
                auto [d, node] = pq.top();
                pq.pop();

                if(d > dist[node]) continue; // Skip if we already found a better path

                for(auto& it : adj[node]) {
                    int nextNode = it[0];
                    int weight = it[1];

                    if(dist[node] + weight < dist[nextNode]) {
                        dist[nextNode] = dist[node] + weight;
                        pq.push({dist[nextNode], nextNode});
                    }
                }
            }
            return dist;
        }
    iii. Bellman-Ford Algorithm
        vector<int> bellmanFord(int V, vector<vector<int>>& edges, int S) {
            vector<int> dist(V, INT_MAX);
            dist[S] = 0;

            for(int i = 0; i < V - 1; i++) {
                for(auto& edge : edges) {
                    int u = edge[0];
                    int v = edge[1];
                    int weight = edge[2];

                    if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }

            // Check for negative weight cycles
            for(auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];

                if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    return {}; // Negative cycle detected
                }
            }

            return dist;
        }
    iv. Floyd-Warshall Algorithm
        vector<vector<int>> floydWarshall(int V, vector<vector<int>>& edges) {
            vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

            // Initialize distances
            for(int i = 0; i < V; i++) {
                dist[i][i] = 0; // Distance to self is 0
            }
            for(auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                dist[u][v] = min(dist[u][v], weight); // Handle multiple edges
            }

            // Floyd-Warshall algorithm
            for(int k = 0; k < V; k++) {
                for(int i = 0; i < V; i++) {
                    for(int j = 0; j < V; j++) {
                        if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }

            return dist;
        }

5. Minimum Spanning Tree/ Disjoint Set
   
    