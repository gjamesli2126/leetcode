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
private:
    unordered_map<int,vector<int>> lvmap;

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        //using bfs
        deque<pair<int,TreeNode*>> dq;
        dq.push_back({0,root});
        while(!dq.empty()){
            auto [lv,cur]=dq.front();
            dq.pop_front();
            if(!cur) continue;
            lvmap[lv].push_back(cur->val);
            dq.push_back({lv+1,cur->left});
            dq.push_back({lv+1,cur->right});
        }
        vector<vector<int>> ans(lvmap.size());
        for(const auto& [lv,v]:lvmap) ans[lv]=v;
        return ans;
    }
};