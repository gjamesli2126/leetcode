#include <bits/stdc++.h>
using namespace std;
#define mainTest main


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
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p== nullptr && q== nullptr) return true;
        if(p== nullptr || q== nullptr) return false;
        stack<pair<TreeNode*,TreeNode*>> stk;
        stk.push({p,q});
        while(!stk.empty()){
            auto [curP,curQ]=stk.top();
            stk.pop();
            if(!curP && curQ || curP && !curQ) return false;
            else if (curP->val!=curQ->val) return false;
            if(curP->left || curQ->left) stk.push({curP->left,curQ->left});
            if(curP->right || curQ->right) stk.push({curP->right,curQ->right});
        }
        return true;
    }
};