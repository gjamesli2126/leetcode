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
    bool isSame(TreeNode *p,TreeNode *q) {
        if(!p && !q) return true;
        else if(!q || !p) return false;

        stack<pair<TreeNode*,TreeNode*>> stk;
        stk.push({p,q});
        while(!stk.empty()) {
            auto [cp,cq]=stk.top();
            stk.pop();
            if(!cp && cq || cp && !cq) return false;
            if(cp->val!=cq->val) return false;

            if(cp->left || cq->left) stk.push({cp->left,cq->left});
            if(cp->right || cq->right) stk.push({cp->right,cq->right});
        }
        return true;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
       if(!subRoot) return true;
       else if(!root) return false;
       stack<TreeNode*> stk;
       stk.push(root);
       while(!stk.empty()){
           TreeNode *cur=stk.top();
           stk.pop();
           if(isSame(cur,subRoot)) return true;
           if(cur->left) stk.push(cur->left);
           if(cur->right) stk.push(cur->right);
       }
       return false;
    }
};