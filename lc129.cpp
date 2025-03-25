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
private:
    int total=0;
    void dfs(TreeNode* node,int totsofar){
        if(!node){
//            total+=totsofar;
            return;
        }
        totsofar=10*totsofar+node->val;
        if(!node->left && !node->right) total+=totsofar;
        dfs(node->left,totsofar);
        dfs(node->right, totsofar);
    }
public:
    int sumNumbers(TreeNode* root) {
        dfs(root,0);
        return total;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, TreeNode* root, int expected) {
    Solution sol;
    int result = sol.sumNumbers(root);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: sumNumbers(root) = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected "
             << expected << ", Got " << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: root = [1,2,3]
    // Tree structure:
    //       1
    //      / \
    //     2   3
    // Root-to-leaf paths: 1->2 = 12, 1->3 = 13; Sum = 12 + 13 = 25
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    runTest(1, root1, 25);

    // Test Case 2:
    // Input: root = [4,9,0,5,1]
    // Tree structure:
    //         4
    //        / \
    //       9   0
    //      / \
    //     5   1
    // Root-to-leaf paths: 4->9->5 = 495, 4->9->1 = 491, 4->0 = 40; Sum = 495 + 491 + 40 = 1026
    TreeNode* root2 = new TreeNode(4);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(0);
    root2->left->left = new TreeNode(5);
    root2->left->right = new TreeNode(1);
    runTest(2, root2, 1026);

    return 0;
}