#include <bits/stdc++.h>
using namespace std;
#define mainTest main

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int maxdep=0;
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        stack<pair<TreeNode*,int>> stk;
        stk.push({root,1});
        while(!stk.empty()){
            auto &[cur,dep]=stk.top();
            stk.pop();
            if(cur->left== nullptr && cur->right== nullptr) maxdep=max(maxdep,dep);
            if(cur->left) stk.push({cur->left,dep+1});
            if(cur->right) stk.push({cur->right,dep+1});
        }
        return maxdep;
    }
};

// Utility functions for building and deleting trees
TreeNode* buildTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;

    queue<TreeNode**> nodePointers;
    TreeNode* root = new TreeNode(nodes[0]);
    nodePointers.push(&root->left);
    nodePointers.push(&root->right);

    for (size_t i = 1; i < nodes.size(); i++) {
        TreeNode** current = nodePointers.front();
        nodePointers.pop();

        if (nodes[i] != -1) {
            *current = new TreeNode(nodes[i]);
            nodePointers.push(&((*current)->left));
            nodePointers.push(&((*current)->right));
        }
    }

    return root;
}


void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


int mainTest() {
    Solution solution;
    const string GREEN = "\033[32m";
    const string RED = "\033[31m";
    const string RESET = "\033[0m";

    struct TestCase {
        vector<int> nodes;
        int expectedDepth;
    };

    vector<TestCase> testCases = {
            {{3, 9, 20, -1, -1, 15, 7}, 3},  // Example 1
            {{1, -1, 2}, 2},                // Example 2
            // Add more test cases as needed
    };

    bool allTestsPassed = true;
    for (const auto& testCase : testCases) {
        TreeNode* root = buildTree(testCase.nodes);
        int result = solution.maxDepth(root);
        if (result != testCase.expectedDepth) {
            cout << RED << "Test Failed: Expected depth " << testCase.expectedDepth << ", but got " << result << RESET << endl;
            allTestsPassed = false;
        } else {
            cout << GREEN << "Test Passed" << RESET << endl;
        }
        deleteTree(root);
    }

    if (allTestsPassed) {
        cout << GREEN << "All tests passed!" << RESET << endl;
    } else {
        cout << RED << "Some tests failed." << RESET << endl;
    }

    return 0;
}
