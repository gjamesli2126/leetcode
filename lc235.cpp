#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!p && !q) return nullptr;
        if(root==p || root==q) return root;
        if(p->val < q->val) swap(p,q);//enusre p must > q
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()){
            TreeNode *cur=stk.top();
            stk.pop();
            if(p->val > cur->val && q->val > cur->val) stk.push(cur->right);
            else if(p->val < cur->val && q->val < cur->val) stk.push(cur->left);
            else if(p->val > cur->val && q->val < cur->val || p->val==cur->val || q->val==cur->val) return cur;
        }
        return root;
    }
};