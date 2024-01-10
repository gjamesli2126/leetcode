#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//do not use extra space
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root== nullptr) return nullptr;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()){
            TreeNode *cur=stk.top();
            stk.pop();
            swap(cur->left,cur->right);
            if(cur->right) stk.push(cur->right);
            if(cur->left) stk.push(cur->left);
        }
        return root;
    }
};