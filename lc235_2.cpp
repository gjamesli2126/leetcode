 #include <bits/stdc++.h>
 #define testMain main
 using namespace std;

 /**
  * Definition for a binary tree node.
  */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
private:
    TreeNode* dfs(TreeNode* node, TreeNode* p,TreeNode* q){
        //base case
        if(!node || node==p || node==q) return node;
        //normal---find left & right children
        TreeNode* left=dfs(node->left,p,q);
        TreeNode* right=dfs(node->right,p,q);
        //if found common ancessotr
        if(left && right) return node;
        //if not found both
        if(left) return left;
        else return right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return dfs(root,p,q);
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, TreeNode* root, TreeNode* p, TreeNode* q, int expectedVal) {
    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    if(lca != nullptr && lca->val == expectedVal) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: LCA = "
             << lca->val << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected LCA = "
             << expectedVal;
        if(lca != nullptr)
            cout << ", Got LCA = " << lca->val;
        else
            cout << ", Got LCA = nullptr";
        cout << "\033[0m" << endl;
    }
}

 int testMain(){
     // Test Case 1:
     // Tree: [3,5,1,6,2,0,8,null,null,7,4]
     // Construct the tree:
     //          3
     //         / \
    //        5   1
     //       / \ / \
    //      6  2 0  8
     //         / \
    //        7   4
     TreeNode* root1 = new TreeNode(3);
     root1->left = new TreeNode(5);
     root1->right = new TreeNode(1);
     root1->left->left = new TreeNode(6);
     root1->left->right = new TreeNode(2);
     root1->right->left = new TreeNode(0);
     root1->right->right = new TreeNode(8);
     root1->left->right->left = new TreeNode(7);
     root1->left->right->right = new TreeNode(4);

     // p = node with value 5, q = node with value 1, expected LCA = 3 (root)
     TreeNode* p1 = root1->left;    // Node with value 5
     TreeNode* q1 = root1->right;   // Node with value 1
     runTest(1, root1, p1, q1, 3);

     // Test Case 2:
     // Using the same tree:
     // p = node with value 5, q = node with value 4, expected LCA = 5
     TreeNode* p2 = root1->left;                // Node with value 5
     TreeNode* q2 = root1->left->right->right;    // Node with value 4
     runTest(2, root1, p2, q2, 5);

     // Test Case 3:
     // Tree: [1,2]
     //      1
     //     /
     //    2
     // p = node with value 1, q = node with value 2, expected LCA = 1
     TreeNode* root2 = new TreeNode(1);
     root2->left = new TreeNode(2);
     TreeNode* p3 = root2;         // Node with value 1
     TreeNode* q3 = root2->left;     // Node with value 2
     runTest(3, root2, p3, q3, 1);

     return 0;
 }