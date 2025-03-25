#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        vector<TreeNode*> stk;
        stk.push_back(root);
        int sum=0;
        while(!stk.empty()){
            TreeNode* node=stk.back();
            stk.pop_back();
            if(node->val>=low && node->val<=high) sum+=node->val;
            if(node->left) stk.push_back(node->left);
            if(node->right) stk.push_back(node->right);
        }
        return sum;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, TreeNode* root, int low, int high, int expected) {
    Solution sol;
    int result = sol.rangeSumBST(root, low, high);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: rangeSumBST(root, " << low << ", " << high
             << ") = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: rangeSumBST(root, " << low << ", " << high
             << ") = " << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int main() {
    // Test Case 1:
    // Tree: [10,5,15,3,7,null,18]
    // Structure:
    //          10
    //         /   \
    //        5     15
    //       / \      \
    //      3   7      18
    // Nodes in range [7, 15]: 7, 10, 15 => Sum = 32
    TreeNode* root1 = new TreeNode(10);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(15);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(7);
    root1->right->right = new TreeNode(18);
    runTest(1, root1, 7, 15, 32);

    // Test Case 2:
    // Tree: [10,5,15,3,7,13,18,1,null,6]
    // Structure:
    //           10
    //         /    \
    //        5      15
    //       / \     / \
    //      3   7   13 18
    //     /   /
    //    1   6
    // Nodes in range [6, 10]: 10, 7, and 6 => Sum = 23
    TreeNode* root2 = new TreeNode(10);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(15);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(7);
    root2->right->left = new TreeNode(13);
    root2->right->right = new TreeNode(18);
    root2->left->left->left = new TreeNode(1);
    root2->left->right->left = new TreeNode(6);
    runTest(2, root2, 6, 10, 23);

    return 0;
}