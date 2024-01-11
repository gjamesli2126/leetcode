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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        deque<pair<TreeNode*,int>> dq;
        dq.push_back({root,0});
        while(!dq.empty()){
            auto [cur,lv]=dq.front();
            dq.pop_front();
            if(!cur) continue;
            if(ans.size()==lv) ans.push_back(cur->val);
            dq.push_back({cur->right,lv+1});
            dq.push_back({cur->left,lv+1});
        }
        return ans;
    }
};