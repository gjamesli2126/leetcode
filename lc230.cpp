/*Given the root of a binary search tree,
 * and an integer k, return the kth smallest value (1-indexed)
 * of all the values of the nodes in the tree.
 */
#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left,*right;
};
class Solution{

public:
    int kthSmallest(TreeNode *root,int& k){
        //traverse in-order w/ dfs
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode *cur=stk.top();
        while(!stk.empty()){
            while(cur){
                stk.push(cur);
                cur=cur->left;
            }
            //at this time: cur=nullptr
            cur=stk.top();//means visiting
            stk.pop();
            --k;
            if(k==0) return cur->val;
            cur=cur->right;
        }
        return -1;
    }

};