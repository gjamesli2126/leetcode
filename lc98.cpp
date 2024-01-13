#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left,*right;
};
class Solution{
public:
    bool isValidBST(TreeNode *root){
        stack<tuple<long,TreeNode*,long>> stk;//min,cur,max
        stk.push({LONG_MIN,root,LONG_MAX});//becuase node.val=INT_MIN~INT_MAX
        while(!stk.empty()){
            auto [min,cur,max]=stk.top();
            stk.pop();
            if(!cur) continue;
            //if this node is ligit
            if(!(min<cur->val && cur->val<max)) return false;
            stk.push({min,cur->left,cur->val});//push to the left
            stk.push({cur->val,cur->right,max});//push to the right
        }
        return true;
    }

};