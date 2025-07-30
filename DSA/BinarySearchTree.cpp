Binary Search Tree - L<N<R
                   - left and right substree should be binary search tree also

                   
1. Search in BST
   Height - log(n)
   TC - Height

2. Ceil in BST
    - smallest element greater than or equal to given element
    int findCeil(Node* root, int key) {
        if (root == NULL) return -1; // or some sentinel value
        if (root->data == key) return root->data;
        if (root->data < key) return findCeil(root->right, key);
        int ceil = findCeil(root->left, key);
        return (ceil >= 0) ? ceil : root->data; // if left subtree has no ceil, return root's data
    }
    TC - Height
    SC - O(1) if we ignore recursion stack, otherwise O(Height)

3. Floor in BST
    - largest element less than or equal to given element
    int findFloor(Node* root, int key) {
        if (root == NULL) return -1; // or some sentinel value
        if (root->data == key) return root->data;
        if (root->data > key) return findFloor(root->left, key);
        int floor = findFloor(root->right, key);
        return (floor >= 0) ? floor : root->data; // if right subtree has no floor, return root's data
    }
    TC - Height
    SC - O(1) if we ignore recursion stack, otherwise O(Height)

4. Insert in BST
   TreeNode* insertInBst(TreeNode* root, int val){
         if (root == NULL) {
              return new TreeNode(val);
         }
         TreeNode* curr = root;
         while(true){
            if(curr->val <= val){
                if(curr->right != NULL){
                    curr = curr->right;
                }else{
                    curr->right = new TreeNode(val);
                    break;
                }
            }else {
                    if(curr->left != NULL){
                        curr = curr->left;
                    }else{
                        curr->left = new TreeNode(val);
                        break;
                    }
                }
        }
        return root;
   }
    TC - O(log n) on average, O(n) in worst case (unbalanced tree)
    SC - O(1) if we ignore recursion stack, otherwise O(Height)

5. Delete in BST
   //find the node to be deleted and return the new root
   TreeNode* deleteNode(TreeNode* root, int key){
        if(root == nullptr) return root;

        if(root->val == key) return helper(root);

        TreeNode* dummy = root;
        while(root != nullptr){
            if(root->val > key){
                if(root->left != nullptr && root->left->val == key){
                    root->left = helper(root->left);
                    break;
                }else{
                    root = root->left;
                }
            }else{
                if(root->right != nullptr && root->right->val == key){
                    root->right = helper(root->right);
                    break;
                }else{
                    root = root->right;
                }
            }
        }
        return dummy;
   }
   // Helper function to handle the deletion of a node
   TreeNode* helper(TreeNode* root){
        if(root->left == nullptr) return root->right;
        if(root->right == nullptr) return root->left;

        TreeNode* rightChild = root->right;
        TreeNode* lastRight = findLastRight(root->left);
        lastRight->right = rightChild;
        return root->left;
    }
    TreeNode* findLastRight(TreeNode* root){
        while(root->right != nullptr){
            root = root->right;
        }
        return root;
    }
    TC - O(log n) on average, O(n) in worst case (unbalanced tree)
    SC - O(1) if we ignore recursion stack, otherwise O(Height)

6. Kth Smallest/Largest Element in BST
   inorder + count
   - recc - TC - O(n)
          - SC - O(n) for recursion stack
   - iterative - TC - O(n)
                - SC - O(1) if we ignore stack(MORRIS), otherwise O(n) for stack

7. Validate BST
   - give a range [min, max] at every node which follows BST rule
   - root should be in range [INT_MIN, INT_MAX]
   - root->left should be in range [INT_MIN, root->data]
   - root->right should be in range [root->data, INT_MAX]
   - recuse though left and right if both true then yes or else fuck you!!

8. LCA in BST
   TreeNode LCA(root, p, q){
        if(root == NULL) return null;
        int curr = root->val;
        if(curr<p->val && curr<q->val){
            return LCA(root->right,p,q);
        }
        if(curr>p->val && curr>q->val){
            return LCA(root->left,p,q);
        }
        return root;
   }

9. Construct BST from Preorder alone
   TreeNode* bst(vector<int> a){
        int i=0 ; 
        return build(a,i,INT_MAX);
   }
   TreeNode* build(a,i,bound){
        if(i == a.size() || a[i]>bound) return nullptr;
        TreeNode* root = new TreeNode(a[i++]);
        root->left = build(a,i,root->val);
        root->right = build(a,i,bound);
        return root;
   }
   TC: O(n)
   SC: O(1)

10. Inorder Successor(just next)/Predecessor(just prev) in BST    
    naive: store and find next to given target(succ)
    thodi efficient: where you find root->val > tar return; (for predeccesor <)
    full efficient: take one variable succ and at every node check
                    if root->val > tar then succ = root->val and go left
                    else go right
    for Successor:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* succ = nullptr;
        while (root) {
            if (p->val < root->val) {
                succ = root; // potential successor
                root = root->left; 
            } else {
                root = root->right; 
            }
        }
        return succ;
    }
    for Predecessor:
    TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) { 
        TreeNode* pred = nullptr;
        while (root) {
            if (p->val > root->val) {
                pred = root; // potential predecessor
                root = root->right; 
            } else {
                root = root->left; 
            }
        }
        return pred;
    }

11. BST Iterator
    - use stack to store the leftmost path of the tree
    - next() will pop from stack and push right child and all its left children
    - hasNext() will check if stack is not empty
    class BSTIterator {
    public:
        stack<TreeNode*> st;

        BSTIterator(TreeNode* root) {
            pushAll(root);   
        }
        
        int next() {
            TreeNode* node = st.top();
            st.pop();
            pushAll(node->right);
            return node->val;
        }
        
        bool hasNext() {
            return !st.empty();
        }

        private:
        void pushAll(TreeNode* root){
            for(; root!=nullptr ; st.push(root),root = root->left);
        }
    };

12. Two sum in BST(use 11.)
13. Recover BST
    - two nodes are swapped in BST
    naive: store inorder and find two nodes which are not in order
    TC: n+nlogn

    efficient: use morris/normal traversal to find two nodes which are not in order
    class Solution {
    public:
        TreeNode* first;
        TreeNode* prev;
        TreeNode* middle;
        TreeNode* last;

        void inorder(TreeNode* root){
            if(root == nullptr) return;
            inorder(root->left);

            if(prev != nullptr && prev->val > root->val) {
                if(first == nullptr) {
                    first = prev;
                    middle = root;
                } else {
                    last = root;
                }
            }
            prev = root;
            inorder(root->right);
        }

        void recoverTree(TreeNode* root) {
            first = middle = last = prev = nullptr;
            inorder(root);
            if(first && last) {
                swap(first->val, last->val);
            } else if(first && middle) {
                swap(first->val, middle->val);
            }
        }
    };

14. Largest BST in Binary Tree
    - use postorder traversal to find largest BST in binary tree
    - return size of largest BST and root of that BST
    - if left and right are BST then check if current node is also BST
    - if yes then return size of left + right + 1
    - if no then return max of left and right sizes
    class Solution {
    public:
        pair<int, TreeNode*> largestBSTSubtree(TreeNode* root) {
            if (!root) return {0, nullptr};
            auto left = largestBSTSubtree(root->left);
            auto right = largestBSTSubtree(root->right);
            
            if (left.second && right.second && 
                left.second->val < root->val && 
                right.second->val > root->val) {
                return {left.first + right.first + 1, root};
            }
            return {max(left.first, right.first), nullptr};
        }
    };

    


        


