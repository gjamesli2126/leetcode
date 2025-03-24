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
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        //using bfs iter
        if(!root) return {};
        vector<int> v;
        deque<pair<TreeNode*,int>> q;//node*,depth
        q.emplace_back(root,0);
        while(!q.empty()){
            auto [node,depth]=q.front();
            q.pop_front();
            if(v.size()==depth) v.push_back(node->val);
            else v[depth]=node->val;
            if(node->left) q.emplace_back(node->left,depth+1);
            if(node->right) q.emplace_back(node->right,depth+1);
        }
        return v;
    }
};

// Helper function to print a vector of integers in [a,b,c,...] format.
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size())
            cout << ",";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, TreeNode* root, const vector<int>& expected) {
    Solution sol;
    vector<int> result = sol.rightSideView(root);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        printVector(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected ";
        printVector(expected);
        cout << " but got ";
        printVector(result);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: root = [1,2,3,null,5,null,4]
    // Constructing the tree:
    //         1
    //        / \
    //       2   3
    //        \    \
    //         5    4
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->right = new TreeNode(5);
    root1->right->right = new TreeNode(4);
    // Right side view: [1,3,4]
    runTest(1, root1, {1,3,4});

    // Example 2:
    // Input: root = [1,2,3,4,null,null,null,5]
    // Constructing the tree:
    //          1
    //         / \
    //        2   3
    //       /
    //      4
    //     /
    //    5
    // Right side view: level 0: 1, level 1: 3, level 2: 4, level 3: 5, so output: [1,3,4,5]
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->left->left = new TreeNode(5);
    runTest(2, root2, {1,3,4,5});

    // Example 3:
    // Input: root = [1,null,3]
    // Constructing the tree:
    //     1
    //      \
    //       3
    // Right side view: [1,3]
    TreeNode* root3 = new TreeNode(1);
    root3->right = new TreeNode(3);
    runTest(3, root3, {1,3});

    // Example 4:
    // Input: root = []
    // Constructing an empty tree.
    TreeNode* root4 = nullptr;
    runTest(4, root4, {});

    return 0;
}