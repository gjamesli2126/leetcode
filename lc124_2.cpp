#include <bits/stdc++.h>
using namespace std;
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
    int globalSum=INT_MIN;
    int treeSum(TreeNode *root){
        if(!root) return 0;

        int rightSum= treeSum(root->right);
        int leftSum= treeSum(root->left);
        int localMax=root->val+max({leftSum,rightSum,0});
        globalSum=max({globalSum,localMax,root->val+leftSum+rightSum});
        return localMax;

    }
public:
    int maxPathSum(TreeNode* root) {
        treeSum(root);
        return globalSum;
    }
};