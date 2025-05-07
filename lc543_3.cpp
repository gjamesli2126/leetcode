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
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int max_global_len=0;
    int dfs(TreeNode* node){
        if(!node) return 0;
        int lh=dfs(node->left);
        int rh=dfs(node->right);
        max_global_len= max(max_global_len,lh+rh);
        return 1+max(lh,rh);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return max_global_len;
    }
};

int testMain(){
    // Test Case 1:
    // Tree: [1,2,3,4,5]
    //         1
    //       /   \
    //      2     3
    //     / \
    //    4   5
    // Expected Output: 3
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    {
        Solution sol;
        int result = sol.diameterOfBinaryTree(root1);
        cout << "Test Case 1 Output: " << result << endl;
    }

    // Test Case 2:
    // Tree: [1,2]
    //       1
    //      /
    //     2
    // Expected Output: 1
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);

    {
        Solution sol;
        int result = sol.diameterOfBinaryTree(root2);
        cout << "Test Case 2 Output: " << result << endl;
    }

    return 0;
}