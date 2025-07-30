1. Representing a Binary Tree in C++
    class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int val) {
            data = val;
            left = NULL;
            right = NULL;
        }
    };
    int main() {
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);
        root->left->right = new Node(5);
        return 0;
    }

    --IMPORTANT--   
        1.1 Insert in Binary Search Tree
            Node* Insert(Node* root, int key) {
                if (root == NULL) {
                    return new Node(key);
                }
                if (key < root->data) {
                    root->left = Insert(root->left, key);
                } else {
                    root->right = Insert(root->right, key);
                }
                return root;
            }
            OR 
            Node* InsertIterative(Node* root, int key) {
                Node* newNode = new Node(key);
                if (root == NULL) return newNode;

                Node* parent = NULL;
                Node* current = root;

                while (current != NULL) {
                    parent = current;
                    if (key < current->data) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }

                if (key < parent->data) {
                    parent->left = newNode;
                } else {
                    parent->right = newNode;
                }
                return root;
            }
            Time Complexity: O(h) where h is the height of the tree
            Space Complexity: O(h) where h is the height of the tree

        1.2 **Delete in Binary Search Tree
            Node* Delete(Node* root, int key) {
                if (root == NULL) return root;

                if (key < root->data) {
                    root->left = Delete(root->left, key);
                } else if (key > root->data) {
                    root->right = Delete(root->right, key);
                } else {
                    // Node with one child or no child
                    if (root->left == NULL) {
                        Node* temp = root->right;
                        delete root;
                        return temp;
                    } else if (root->right == NULL) {
                        Node* temp = root->left;
                        delete root;
                        return temp;
                    }

                    // Node with two children: Get the inorder successor
                    Node* temp = FindMin(root->right);
                    root->data = temp->data; // Copy the inorder successor's content to this node
                    root->right = Delete(root->right, temp->data); // Delete the inorder successor
                }
                return root;
            }
            Time Complexity: O(h) where h is the height of the tree
            Space Complexity: O(h) where h is the height of the tree
        1.3 Search in Binary Search Tree
    Balanced - O(log n)
    Unbalanced - O(n)

    Node* Search(Node* root, int key) {
        if (root == NULL || root->data == key) return root;
        if (key < root->data) return Search(root->left, key);
        return Search(root->right, key);
    }
    Time Complexity: O(h) where h is the height of the tree
    Space Complexity: O(h) where h is the height of the tree


2. Binary Tree Traversal(DFS)

    void preOrder(Node* root) {
        if (root == NULL) return;
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

    void inOrder(Node* root) {
        if (root == NULL) return;
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

    void postOrder(Node* root) {
        if (root == NULL) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }   
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree


3. Level Order Traversal (BFS)
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            
            for (int i = 0; i < size; i++) {
                Node* current = q.front();
                q.pop();
                level.push_back(current->data);
                if (current->left != NULL) q.push(current->left);
                if (current->right != NULL) q.push(current->right);
            }
            ans.push_back(level);
        }
        return ans;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the queue

4. Iterative Preorder Traversal
    vector<int> iterativePreorder(Node* root) {
        vector<int> result;
        if (root == NULL) return result;

        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            result.push_back(current->data);

            // Push right first so that left is processed first
            if (current->right != NULL) s.push(current->right);
            if (current->left != NULL) s.push(current->left);
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the stack

5. Iterative Inorder Traversal
    vector<int> iterativeInorder(Node* root) {
        vector<int> result;
        stack<Node*> st;
        Node* curr = root;

        while (true) {
            if(curr != NULL){
                st.push(curr);
                curr = curr->left; 
            }else{
                if(st.empty()) break;
                curr = st.top();
                st.pop();
                result.push_back(curr->data);
                curr = curr->right;
            }
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the stack

6. Iterative Postorder Traversal
    vector<int> iterativePostorder(Node* root) {
        vector<int> result;
        if (root == NULL) return result;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* current = s1.top();
            s1.pop();
            s2.push(current);

            if (current->left != NULL) s1.push(current->left);
            if (current->right != NULL) s1.push(current->right);
        }

        while (!s2.empty()) {
            result.push_back(s2.top()->data);
            s2.pop();
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the stacks

    #with one stack
    vector<int> iterativePostorderOneStack(Node* root) {
        vector<int> result;
        if (root == NULL) return result;

        stack<Node*> s;
        Node* current = root;
        Node* lastVisited = NULL;

        while (current != NULL || !s.empty()) {
            if(current != NULL) {
                s.push(current);
                current = current->left;
            }
            else{
                int temp = s.top()->right;
                if(temp == NULL){
                    temp = st.top();
                    st.pop();
                    result.push_back(temp->data);
                    while(!s.empty() && temp == s.top()->right) {
                        temp = s.top();
                        s.pop();
                        result.push_back(temp->data);
                    }
                }else{
                    current = temp;
                }
            }
        }
        return result;
    }

7. Pre+In+Post in one Traversal
    vector<int> preInPostTraversal(Node* root){
        stack<pair<Node*, int>> s;
        st.push({root, 1});
        vector<int> pre, in, post;

        if(root == NULL) return {pre, in, post};

        while(!s.empty()) {
            auto [node, state] = s.top();
            s.pop();

            if(state == 1) {
                pre.push_back(node->data);
                s.push({node, 2}); // Push the node back with state 2
                if(node->left != NULL) s.push({node->left, 1});
            } else if(state == 2) {
                in.push_back(node->data);
                s.push({node, 3}); // Push the node back with state 3
                if(node->right != NULL) s.push({node->right, 1});
            } else {
                post.push_back(node->data);
            }
        }
        return {pre, in, post};
    }








8. Size of Binary Tree
    int Size(Node* root) {
        if (root == NULL) return 0;
        return 1 + Size(root->left) + Size(root->right);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

9. Height/Max Depth of Binary Tree
    int Height(Node* root) {
        if (root == NULL) return 0;
        return 1 + max(Height(root->left), Height(root->right));
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree


10. Check Balanced Binary Tree
    Naive Approach:
    - Check the height of left and right subtrees for every node 
    - and ensure the difference is not more than 1.
    - return bool of each node.
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

    using max height
    int check(node){
        if(node == NULL) return 0;

        int l = check(node->left);
        int r = check(node->right);

        if(l == -1 || r == -1 || abs(l-r) > 1) return -1;

        return max(l,r) + 1;
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

11. Diameter of BT - longest path btw two node
    Naive - go to every node ane check height andn retrn max and store
    advance
    int findMax(node, maxi){
        if(node == nullptr) return 0;

        int l = findMax(node->left, maxi);
        int r = findMax(node->right, maxi);
        maxi = max(maxi, l + r);
        return max(l, r) + 1;
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

12. Max Path Sum (using height code)
    int maxPath(node, maxi){
        if(node == NULL) return 0;

        int l = max(0, maxPath(node->left, maxi)); // Ignore negative paths
        int r = max(0, maxPath(node->right, maxi));
        maxi = max(maxi, l + r + node->data); // Update the maximum path sum
        return max(l, r) + node->data; // Return the maximum path sum including
    }

13. Zig Zag Traversal
    vector<vector<int>> zigZagTraversal(Node* root) {
        vector<vector<int>> result;
        if (root == NULL) return result;

        queue<Node*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);

            for (int i = 0; i < size; i++) {
                Node* current = q.front();
                q.pop();

                // Find the position to insert the current node's data
                int index = leftToRight ? i : size - 1 - i;
                level[index] = current->data;

                if (current->left != NULL) q.push(current->left);
                if (current->right != NULL) q.push(current->right);
            }
            result.push_back(level);
            leftToRight = !leftToRight; // Toggle the direction for the next level
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the queue

14. Boundary Traversal
    Approach - left Traversal -> leaf(inorder) -> right Traversal without leafs
    bool isLeaf(Node* node) {
        return node && !node->left && !node->right;
    }
    vector<int> printBoundary(root){
        vector<int> res;
        if(!root) return res;
        if(!isLeaf(root)) res.push_back(root->data);
        addLeftBoundary(root->left, res);
        addLeaves(root, res);
        addRightBoundary(root->right, res);
        return res;
    } 
    void addLeftBoundary(Node* node, vector<int>& res) {
        while (node) {
            if (!isLeaf(node)) res.push_back(node->data);
            node = node->left ? node->left : node->right; // Go down the left or right child
        }
    }
    void addLeaves(Node* node, vector<int>& res) {
        if (node == NULL) return;
        if (isLeaf(node)) {
            res.push_back(node->data);
            return;
        }
        addLeaves(node->left, res);
        addLeaves(node->right, res);
    }
    void addRightBoundary(Node* node, vector<int>& res) {
        vector<int> temp;
        while (node) {
            if (!isLeaf(node)) temp.push_back(node->data);
            node = node->right ? node->right : node->left; // Go down the right or left child
        }
        reverse(temp.begin(), temp.end());
        res.insert(res.end(), temp.begin(), temp.end());
    }

15. Vertical Order Traversal
    vector<vector<int>> verticalOrder(Node* root) {
        map<int, vector<int>> m;
        queue<pair<Node*, int>> q; // Pair of node and its horizontal distance
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();
            if (node) {
                m[hd].push_back(node->data);
                q.push({node->left, hd - 1});
                q.push({node->right, hd + 1});
            }
        }

        vector<vector<int>> result;
        for (auto& [key, vec] : m) {
            result.push_back(vec);
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the map and queue

16. Views in BT

    1. Top View
    vector<int> topView(Node* root) {
        vector<int> result;
        if (root == NULL) return result;

        map<int, int> m; // Map to store the first node at each horizontal distance
        queue<pair<Node*, int>> q; // Pair of node and its horizontal distance
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            if (m.find(hd) == m.end()) { // If this horizontal distance is not already in the map
                m[hd] = node->data;
            }

            if (node->left != NULL) q.push({node->left, hd - 1});
            if (node->right != NULL) q.push({node->right, hd + 1});
        }

        for (auto& [key, value] : m) {
            result.push_back(value);
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the map and queue

    2. Bottom View
    vector<int> bottomView(Node* root) {
        vector<int> result;
        if (root == NULL) return result;

        map<int, int> m; // Map to store the last node at each horizontal distance
        queue<pair<Node*, int>> q; // Pair of node and its horizontal distance
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            m[hd] = node->data; // Update the map with the last node at this horizontal distance

            if (node->left != NULL) q.push({node->left, hd - 1});
            if (node->right != NULL) q.push({node->right, hd + 1});
        }

        for (auto& [key, value] : m) {
            result.push_back(value);
        }
        return result;
    }
    Time Complexity: O(n)
    Space Complexity: O(n) for the map and queue

    3. Left View(Recusive)
    void leftView(node, level, vector<int>& res) {
        if (node == NULL) return;

        // If this level is not already in the map, add it
        if (level == res.size()) {
            res.push_back(node->data);
        }

        leftView(node->left, level + 1, res);
        leftView(node->right, level + 1, res);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

    4. Right View(Recusive)
    void rightView(node, level, vector<int>& res) {
        if (node == NULL) return;

        // If this level is not already in the map, add it
        if (level == res.size()) {
            res.push_back(node->data);
        }

        rightView(node->right, level + 1, res);
        rightView(node->left, level + 1, res);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree


17. Symmetric Tree
    bool isSymmetric(Node* root) {
        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }

    bool isMirror(Node* left, Node* right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        return (left->data == right->data) && 
               isMirror(left->left, right->right) && 
               isMirror(left->right, right->left);
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

18. Root to Node / Root to Leaf Path 
    vector<int> solve(root, tar){
        vector<int> arr;
        if(root == NULL) return arr;

        getPath(root, tar, arr);
        return arr;
    }
    bool getPath(Node* root, int tar, vector<int>& arr) {
        if (root == NULL) return false;

        arr.push_back(root->data);

        if (root->data == tar) return true;

        if (getPath(root->left, tar, arr) || 
            getPath(root->right, tar, arr)) {
            return true;
        }

        arr.pop_back(); // Backtrack if not found
        return false;
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

19. Lowest Common Ancestor
    brute - path of both nodes and compare
          - last common node is LCA
    optimal - use recusion and par and curr pointer
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root==q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);

        if(left == NULL) return right;
        else if(right == NULL) return left;
        else
        return root;
    }
    Time Complexity: O(n)
    Space Complexity: O(h) where h is the height of the tree

20. Max Width of Binary Tree
    int maxWidth(Node* root) {
        if (root == NULL) return 0;

        int left = maxWidthUtil(root->left)*2;
        int right = maxWidthUtil(root->right)*2 + 1;

        int wid = right-left+1;
        return wid;
    }
    time Complexity : O(n)
    Space Complexity: O(h) where h is the height of the tree

    OR(to save integer overflow)
    int maxWidth(Node* root){
        if(!root) return 0;
        int ans = 0;
        queue<pair<Node*, int>> q; // Pair of node and its index
        q.push({root, 0}); // Start with index 0

        while(!q.empty()){
            int size = q.size();
            int mmin = q.front().second; // Minimum index at the current level
            int first, last;
            for(int i=0 ; i<size ; i++){
                int curr_id = q.front().second - mmin; // Normalize the index to prevent overflow
                Node* node = q.front().first;
                q.pop();
                if(i == 0) first = curr_id; // First index at this level
                if(i == size - 1) last = curr_id; // Last index at this
                if(node->left) q.push({node->left, curr_id * 2 + 1}); // Left child index
                if(node->right) q.push({node->right, curr_id * 2 + 2}); // Right child index
            }
            ans = max(ans, last - first + 1); // Update the maximum width
        }
        return ans;
    }


21. Children Sum Property in BT
    void changeTree(Tree <int> *root){
        if(root == NULL) return;
        int child = 0;
        if(root->left) 
            child += root->left->data;
        if(root->right)
            child += root->right->data;

        if(child >= root->data) 
            root->data = child;
        else {
            if(root->left) 
                root->left->data = root->data;
            else if(root->right)
                root->right->data = root->data;
        }

        changeTree(root->left);
        changeTree(root->right);

        int total = 0;
        if(root->left) 
            total += root->left->data;
        if(root->right)
            total += root->right->data;
        if(root->left || root->right)
            root->data = total;
    }

22. Nodes at Distance of K in BT
    void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent_track, TreeNode* target) {
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            if(node->left) {
                parent_track[node->left] = node;
                q.push(node->left);
            }
            if(node->right) {
                parent_track[node->right] = node;
                q.push(node->right);
            }
        }
    }
    vector<int> distaceK(TreeNode* root, TreeNode* tar, int k){
        unordered_map<TreeNode*, TreeNode*> parent_track; //node->parent
        markParents(root, parent_track, tar);

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(tar);
        visited[tar] = true;
        int level = 0;
        while(!q.emoty()){
            int size = q.size();
            if(level++ == k) break; // Stop when we reach the desired distance
            
            for(int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                if(current->left && !visited[current->left]) {
                    q.push(current->left);
                    visited[current->left] = true;
                }
                if(current->right && !visited[current->right]) {
                    q.push(current->right);
                    visited[current->right] = true;
                }if(parent_track[current] && !visited[parent_track[current]]) {
                    q.push(parent_track[current]);
                    visited[parent_track[current]] = true;
                }
            }
        }
        vector<int> result;
        while(!q.empty()) {
            result.push_back(q.front()->data);
            q.pop();
        }
        return result;
    }


23. Min Time to Burn Tree
    int findMaxDis(map<TreeNode*, TreeNode*> mp, TreeNode* tar){
        int time = 0;
        map<TreeNode*, bool> vis;
        queue<TreeNode*> q;
        q.push(tar);
        vis[tar] = true;

        while(!q.empty()){
            int size = q.size();
            int burned = 0;
            for(int i=0 ; i<size ; i++){
                auto node = q.front();
                q.pop();
                //left
                if(node->left && !vis[node->left]){
                    burned = 1;
                    vis[node->left] = true;
                    q.push(node->left);
                }
                //right
                if(node->right && !vis[node->right]){
                    burned = 1;
                    vis[node->right] = true;
                    q.push(node->right);
                }
                //parent(up)
                if(mp[node] && !vis[mp[node]]){
                    burned = 1;
                    vis[mp[node]] = 1;
                    q.push(mp[node]);
                }
            }
            if(burned) time++;
        }
        return time;
    }
    TreeNode* bfsToMapParent(TreeNode* root,  map<TreeNode*, TreeNode*> &mp ,int start){
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* res;
        while(!q.empty()){
            auto node = q.front(); q.pop();
            if(node->val == start) res = node;
            if(node->left){
                q.push(node->left);
                mp[node->left] = node;
            }
            if(node->right){
                q.push(node->right);
                mp[node->right] = node;
            }
        }

        return res;
    }
    int amountOfTime(TreeNode* root, int start) {
        map<TreeNode*, TreeNode*> mp;
        TreeNode* tar = bfsToMapParent(root,mp,start);
        int maxi = findMaxDis(mp, tar);

        return maxi;
    }

24. Count Total Node in Complete Tree
    Naive - Traverse the tree and count nodes(recusion - inorder,pre,post)
    Smart - check if l and r subtree height are equal -> return 2^h - 1
            else return 1 + count(l) + count(r); (recusively)
    

    int countNodes(TreeNode* root) {
        //this below is naive and traversing all nodes
        // if(root == NULL) return 0;

        // int left = countNodes(root->left);
        // int right = countNodes(root->right);
        // return left+right+1;

        //this approach is not traversing all nodes
        //it is checking the height of left and right subtree
        //and using the property of complete binary tree
        if(root == NULL) return 0;

        int left = countLeft(root->left);
        int right = countRight(root->right);

        if(left == right) return (1<<(left+1)) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    int countLeft(TreeNode* root){
        int h = 0;
        while(root){
            h++;
            root = root->left;
        }
        return h;
    }
    int countRight(TreeNode* root){
        int h = 0;
        while(root){
            h++;
            root = root->right;
        }
        return h;
    }
    Time Complexity: O(log n * log n) for the height calculation
    Space Complexity: O(h) where h is the height of the tree

25. Construct Binary Tree
    i. PreOrder and Inorder
        TreeNode* buildTree(vector<int>& preoder, vector<int>& inorder){
            map<int,int> mp;

            for(int i=0 ; i<inorder.size() ; i++){
                mp[inorder[i]] = i; // Store the index of each value in inorder
            }

            TreeNode* root = buildTree(preoder,0, preoder.size()-1, inorder, 0, inorder.size()-1, mp);
            return root;
        }

        TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd, map<int,int>& mp) {
            if (preStart > preEnd || inStart > inEnd) return NULL;

            TreeNode* root = new TreeNode(preorder[preStart]);
            int inRootIndex = mp[root->val]; // Get the index of the root in inorder
            int numsLeft = inRootIndex - inStart; // Number of nodes in the left subtree

            // Recursively build the left and right subtrees
            root->left = buildTree(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRootIndex - 1, mp);
            root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd, inorder, inRootIndex + 1, inEnd, mp);

            return root;
        }
        Time Complexity: O(n)
        Space Complexity: O(n) for the map and recursion stack
    ii. Inorder and Postorder
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            map<int,int> mp;

            for(int i=0 ; i<inorder.size() ; i++){
                mp[inorder[i]] = i; // Store the index of each value in inorder
            }

            TreeNode* root = buildTree(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1, mp);
            return root;
        }
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd, map<int,int>& mp) {
            if (inStart > inEnd || postStart > postEnd) return NULL;

            TreeNode* root = new TreeNode(postorder[postEnd]);
            int inRootIndex = mp[root->val]; // Get the index of the root in inorder
            int numsLeft = inRootIndex - inStart; // Number of nodes in the left subtree

            // Recursively build the right and left subtrees
            root->right = buildTree(inorder, postorder, inRootIndex + 1, inEnd, postStart + numsLeft, postEnd - 1, mp);
            root->left = buildTree(inorder, postorder, inStart, inRootIndex - 1, postStart, postStart + numsLeft - 1, mp);

            return root;
        }
        Time Complexity: O(n)
        Space Complexity: O(n) for the map and recursion stack

26. Serialize and DeSerialize in Binary Tree
    i. Serialize
        string serialize(TreeNode* root) {
            if (root == NULL) return "";

            string s = "";
            queue<TreeNode*> q;
            q.push(root);
            while (!q.empty()) {
                TreeNode* node = q.front();
                q.pop();

                if (node == NULL) {
                    s += "#,";
                } else {
                    s += to_string(node->val) + ",";
                    q.push(node->left);
                    q.push(node->right);
                }
            }

            return s;
        }
    ii. DeSerialize
        TreeNode* deserialize(string data) {
            if (data.empty()) return NULL;

            stringstream ss(data);
            string str;
            getline(ss, str, ',');
            if (str == "#") return NULL;

            TreeNode* root = new TreeNode(stoi(str));
            queue<TreeNode*> q;
            q.push(root);

            while (!q.empty()) {
                TreeNode* node = q.front();
                q.pop();

                getline(ss, str, ',');
                if (str != "#") {
                    node->left = new TreeNode(stoi(str));
                    q.push(node->left);
                }

                getline(ss, str, ',');
                if (str != "#") {
                    node->right = new TreeNode(stoi(str));
                    q.push(node->right);
                }
            }

            return root;
        }

27. MORRIS INORDER Traversal(Threaded Binary Tree)
    vector<int> inorderMorris(TreeNode* root){
        vector<int> res;
        TreeNode* curr = root;
        while(curr != NULL){
            if(curr->left == NULL){
                res.push_back(curr->val);
                curr = curr->right; // Move to the right child
            } 
            else{
                TreeNode* prev = curr->left;
                while(prev->right != NULL && prev->right != curr){
                    prev = prev->right; // Find the rightmost node in the left subtree
                }

                if(prev->right == NULL){
                    prev->right = curr;
                    // res.push_back(curr->val); // Visit the current node -> FOR PREORDER
                    curr = curr->left; // Move to the left child
                }
                else{
                    prev->right = NULL; // Restore the tree structure
                    res.push_back(curr->val); // Visit the current node ->DELETE THIS FOR PREODER
                    curr = curr->right; // Move to the right child
                }
            }
        }
        return res;
    }
    Time Complexity: O(n)
    Space Complexity: O(1) - no extra space used for traversal

28. Flatten Binary Tree to Linked List
    1. Naive Approach -> preorder + new Linked List
    2. Recusive approach
       TreeNode* prev = nullptr;
       void flatten(TreeNode* root){
            if(root == nullptr) return;

            flatten(root->right); // Flatten the right subtree first
            flatten(root->left); // Flatten the left subtree

            root->right = prev;
            root->left = nullptr;
            prev = root;
        }
    
    3. Iterative with stack
       void flatten(TreeNode* root){
            if(root == NULL) return;

            stack<TreeNode*> st;
            st.push(root);
            TreeNode* prev = NULL;

            while(!st.empty()){
                TreeNode* curr = st.top(); st.pop();

                if(curr->left) st.push(curr->left);
                if(curr->right) st.push(curr->right);

                if(!st.empty())
                    curr->right = st.top();
                
                curr->left = NULL;
            }
       }    
    
    4. Morris BABA
       void flatten(TreeNode* root){
            TreeNode* curr = root;
            while(curr!=NULL){
                if(curr->left == NULL){
                    TreeNode* prev = curr->left;

                    while(prev->right)
                        prev = prev->right;
                    
                    prev->right = curr->right; 
                    curr->right = curr->left;
                }
                curr = curr->right;
            }
       }





    
    



