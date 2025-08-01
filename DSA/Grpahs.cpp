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

    QUESTION REALTED TO TRAVERSAL
    
