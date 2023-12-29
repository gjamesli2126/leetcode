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
public:
    int globalMax=INT_MIN;
    int dfs(TreeNode *node){
        if(!node) return 0;
        int leftMax=max(0,dfs(node->left));
        int rightMax=max(0,dfs(node->right));
        //global max clac here
        globalMax=max(globalMax,rightMax+leftMax+node->val);
        //local max calc here
        int localMax=node->val+max(leftMax,rightMax);
        return localMax;
    }
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return globalMax;
    }
};