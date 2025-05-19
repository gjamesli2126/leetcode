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
    int global_max{-1000};
    int dfs(TreeNode* node){//return the deliverible sum, !=local sum
        if(!node) return 0;//can not incldue fcking children
        int l=dfs(node->left);
        int r=dfs(node->right);
        l=max(0,l);
        r=max(0,r);//choose if I wanna include this fucking child
        global_max=max(global_max,l+r+node->val);
        return node->val+max(l,r);
    }
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return global_max;
    }
};

// Use INT_MIN as a sentinel for null nodes
static const int NUL = numeric_limits<int>::min();

// Builds a binary tree from level-order vector, using NUL for nulls
TreeNode* buildTree(const vector<int>& v) {
    if (v.empty() || v[0] == NUL) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    int idx = 1;
    while (idx < (int)v.size() && !q.empty()) {
        TreeNode* node = q.front(); q.pop();
        // left child
        if (idx < (int)v.size()) {
            if (v[idx] != NUL) {
                node->left = new TreeNode(v[idx]);
                q.push(node->left);
            }
            idx++;
        }
        // right child
        if (idx < (int)v.size()) {
            if (v[idx] != NUL) {
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
    int result = sol.maxPathSum(root);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed. maxPathSum = " << result << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed. maxPathSum = " << result
             << ", expected " << expected << "\033[0m\n";
    }
}

int testMain() {
    // Example 1: [1,2,3] -> 6
    runTest(1, {1,2,3}, 6);

    // Example 2: [-10,9,20,null,null,15,7] -> 42
    runTest(2, {-10,9,20,NUL,NUL,15,7}, 42);
    runTest(3, {2,-1,NUL}, 2);

    return 0;
}