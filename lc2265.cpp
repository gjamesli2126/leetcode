#include <bits/stdc++.h>
#define testMain main
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    struct Result{
        int num{0};
        int res{0};
        int sum{0};
    };
    Result dfs_compute(TreeNode* node){
        if(!node) return Result{};
        Result l= dfs_compute(node->left);
        Result r= dfs_compute(node->right);
        Result res;

        res.num=l.num+r.num+1;
        res.sum=l.sum+r.sum+node->val;
        res.res=l.res+r.res+(node->val==(res.sum/res.num));
        return res;
    }
public:
    int averageOfSubtree(TreeNode* root) {
        return dfs_compute(root).res;
    }
};

// Helper to build a tree from level-order vector with -1 as null
TreeNode* buildTree(const vector<int>& v) {
    if (v.empty() || v[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    int idx = 1;
    while (idx < (int)v.size() && !q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (idx < (int)v.size()) {
            if (v[idx] != -1) {
                node->left = new TreeNode(v[idx]);
                q.push(node->left);
            }
            idx++;
        }
        if (idx < (int)v.size()) {
            if (v[idx] != -1) {
                node->right = new TreeNode(v[idx]);
                q.push(node->right);
            }
            idx++;
        }
    }
    return root;
}

void runTest(int testNum, const vector<int>& treeVec, int expected) {
    TreeNode* root = buildTree(treeVec);
    Solution sol;
    int result = sol.averageOfSubtree(root);
    if (result == expected) {
        cout << "\033[1;32mTest " << testNum
             << " Passed: result = " << result << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest " << testNum
             << " Failed: result = " << result
             << ", expected " << expected << "\033[0m\n";
    }
}

int testMain() {
    // Example 1: [4,8,5,0,1,null,6] -> 5
    runTest(1, {4,8,5,0,1,-1,6}, 5);

    // Example 2: [1] -> 1
    runTest(2, {1}, 1);

    return 0;
}