#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left,*right;
};
class Solution{
private:
    bool dfs(long min,TreeNode *cur,long max){
        if(!cur) return true;
        if(min>=cur->val || max<=cur->val ) return false;
        if(!dfs(min,cur->left,cur->val)) return false;
        if(!dfs(cur->val,cur->right,max)) return false;
        return true;
    }
public:
    bool isValidBST(TreeNode *root){
        return dfs(LONG_MIN,root,LONG_MAX);
    }

};