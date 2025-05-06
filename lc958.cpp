#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.emplace(root);
        bool nullExist= false;
        while(!q.empty()){
            auto node=q.front();
            q.pop();
            if(node== nullptr) nullExist=true;
            else{
                if(nullExist) return false;
                q.emplace(node->left);
                q.emplace(node->right);
            }
        }
        return true;
    }
};

// Helper: Build a binary tree from a level-order list with "null" for missing nodes.
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front(); q.pop();
        if (i < nodes.size() && nodes[i] != "null") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "null") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper: Free the allocated tree.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper: Run a test case and print pass (green) or fail (red).
void runTest(int testNum, vector<string> treeNodes, bool expected) {
    TreeNode* root = buildTree(treeNodes);
    Solution sol;
    bool result = sol.isCompleteTree(root);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: " << (expected ? "true" : "false")
             << ", Got: " << (result ? "true" : "false") << endl;
    }
    freeTree(root);
}

int testMain(){
    // Example 1:
    // Input: root = [1,2,3,4,5,6]
    // Output: true
    runTest(1, {"1","2","3","4","5","6"}, true);

    // Example 2:
    // Input: root = [1,2,3,4,5,null,7]
    // Output: false
    runTest(2, {"1","2","3","4","5","null","7"}, false);

    return 0;
}