#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for a binary tree node.
struct TreeNode{
public:
    int val{0};
    TreeNode* left=nullptr,*right=nullptr;
    TreeNode(){}
    TreeNode(int val):val(val){}
    TreeNode(int val,TreeNode* l,TreeNode* r):val(val),left(l),right(r){}
};

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        //use BFs. use count of children is too complicated. Use seen null instead
        if(!root) return true;
        queue<TreeNode*> q;
        q.push(root);
        bool seenNull=false;
        while(!q.empty()){
            TreeNode* node=q.front();
            q.pop();
            if(node== nullptr) seenNull=true;
            else{
                if(seenNull) return false;
                q.push(node->left);
                q.push(node->right);
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