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
class Solution {
private:
    int totalNum=0;
public:
    int goodNodes(TreeNode* root) {
        if(!root) return 0;
        stack<pair<int,TreeNode*>> stk;
        stk.push({root->val,root});
        while(!stk.empty()){
            auto [maxVal,cur]=stk.top();
            stk.pop();
            if(!cur) continue;
            if(cur->val>=maxVal){
                ++totalNum;
                maxVal=cur->val;
            }
            stk.push({maxVal,cur->left});
            stk.push({maxVal,cur->right});
        }
        return totalNum;
    }
};