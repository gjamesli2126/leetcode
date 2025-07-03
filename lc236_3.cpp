#include <bits/stdc++.h>
#define testMain main
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    TreeNode* ans= nullptr;
    bool dfs(TreeNode* node, TreeNode* p, TreeNode* q){
        if(!node || ans) return false;
        bool left= dfs(node->left,p,q);
        bool right=dfs(node->right,p,q);
        bool mid=(node==p || node==q);
        if(left+right+mid>=2){
            ans=node;
            return false;
        }
        return left | right | mid;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //using DFS recusivly; return false if wanna skip. return true means keep traversing
        dfs(root,p,q);
        return ans;
    }
};

// Helper: Build a binary tree from level-order input with "null" markers.
TreeNode* buildTree(const vector<string>& vals) {
    if (vals.empty() || vals[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(vals[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* curr = q.front(); q.pop();
        if (i < vals.size() && vals[i] != "null") {
            curr->left = new TreeNode(stoi(vals[i]));
            q.push(curr->left);
        }
        i++;
        if (i < vals.size() && vals[i] != "null") {
            curr->right = new TreeNode(stoi(vals[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper: Find pointer to the node with given value.
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

// Helper: Free the allocated tree.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper: Run a single test case.
void runTest(int testNum,
             vector<string> treeVals,
             int pVal,
             int qVal,
             int expectedVal) {
    TreeNode* root = buildTree(treeVals);
    TreeNode* p = findNode(root, pVal);
    TreeNode* q = findNode(root, qVal);
    Solution sol;
    TreeNode* ans = sol.lowestCommonAncestor(root, p, q);
    int resultVal = ans ? ans->val : INT_MIN;
    if (resultVal == expectedVal) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected LCA = " << expectedVal
             << ", Got = " << (ans ? ans->val : -1) << endl;
    }
    freeTree(root);
}

int testMain(){
    // Example 1:
    // Tree = [3,5,1,6,2,0,8,null,null,7,4], p=5, q=1, LCA=3
    runTest(1,
            {"3","5","1","6","2","0","8","null","null","7","4"},
            5, 1, 3);

    // Example 2:
    // Tree = [3,5,1,6,2,0,8,null,null,7,4], p=5, q=4, LCA=5
    runTest(2,
            {"3","5","1","6","2","0","8","null","null","7","4"},
            5, 4, 5);

    // Example 3:
    // Tree = [1,2], p=1, q=2, LCA=1
    runTest(3,
            {"1","2"},
            1, 2, 1);

    return 0;
}