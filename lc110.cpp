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
    bool dfs(TreeNode *node,int& h){
        if(node== nullptr){
            h=-1;
            return true;
        }
        int lh=0,rh=0;
        bool ltf=dfs(node->left,lh);
        bool rtf=dfs(node->right,rh);
        if(!ltf || !rtf) return false;
        else if(abs(lh-rh)>1) return false;
        h=1+max(lh,rh);
        return true;
    }
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int h=0;
        return dfs(root,h);
    }
};