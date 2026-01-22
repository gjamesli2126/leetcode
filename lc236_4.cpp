#define mainTest main
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits> // For INT_MIN

using namespace std;

// Definition for a TreeNode (NO PARENT POINTER)
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// ==========================================
// YOUR SOLUTION GOES HERE
// ==========================================
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root==p || root==q) return root;
        TreeNode* left= lowestCommonAncestor(root->left,p,q);
        TreeNode* right= lowestCommonAncestor(root->right,p,q);
        if(left && right) return root;
        if(left) return left;
        if(right) return right;
        return nullptr;
    }
};

// ==========================================
// TEST HARNESS
// ==========================================

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Helper: Build tree (Standard Level Order)
TreeNode* buildTree(const vector<int>& TreeNodes) {
    if (TreeNodes.empty()) return nullptr;
    TreeNode* root = new TreeNode(TreeNodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (i < TreeNodes.size()) {
        TreeNode* curr = q.front(); q.pop();
        if (i < TreeNodes.size() && TreeNodes[i] != INT_MIN) {
            curr->left = new TreeNode(TreeNodes[i]);
            q.push(curr->left);
        }
        i++;
        if (i < TreeNodes.size() && TreeNodes[i] != INT_MIN) {
            curr->right = new TreeNode(TreeNodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper: Find TreeNode by value
TreeNode* findTreeNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* l = findTreeNode(root->left, val);
    if (l) return l;
    return findTreeNode(root->right, val);
}

void runTest(vector<int> treeData, int pVal, int qVal, int expectedVal, string testName) {
    TreeNode* root = buildTree(treeData);
    TreeNode* p = findTreeNode(root, pVal);
    TreeNode* q = findTreeNode(root, qVal);

    Solution sol;
    TreeNode* result = sol.lowestCommonAncestor(root, p, q);

    cout << "Test: " << testName << " | p=" << pVal << ", q=" << qVal << endl;

    bool passed = (result != nullptr && result->val == expectedVal);
    if (passed) cout << GREEN << "  [PASS] Output: " << result->val << RESET << endl;
    else cout << RED << "  [FAIL] Expected: " << expectedVal << ", Got: " << (result ? to_string(result->val) : "null") << RESET << endl;
    cout << "------------------------------------------------" << endl;
}

int mainTest() {
    // Example 1
    vector<int> t1 = {3,5,1,6,2,0,8,INT_MIN,INT_MIN,7,4};
    runTest(t1, 5, 1, 3, "Standard Case");

    // Example 2 (One is ancestor of another)
    runTest(t1, 5, 4, 5, "p is ancestor of q");

    // Example 3 (Small tree)
    vector<int> t3 = {1, 2};
    runTest(t3, 1, 2, 1, "Root & Child");

    return 0;
}