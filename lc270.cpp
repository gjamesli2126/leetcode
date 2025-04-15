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
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    pair<int,double> val_absdelta={-1,MAXFLOAT};
    void binSearch(TreeNode* node, double target){
        if(!node) return;
        if(abs(target-node->val)<val_absdelta.second || abs(target-node->val)==val_absdelta.second && node->val<val_absdelta.first) val_absdelta={node->val,abs(target-node->val)};

        if(node->left && node->right) {
            if (node->val < target) binSearch(node->right, target);
            else if (target < node->val) binSearch(node->left, target);
//            else val_absdelta={node->val,01};
        }else if(node->left) binSearch(node->left,target);
        else binSearch(node->right,target);
    }
public:
    int closestValue(TreeNode* root, double target) {
        binSearch(root,target);
        return val_absdelta.first;
    }
};

// Helper function to free the binary tree.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, TreeNode* root, double target, int expected) {
    Solution sol;
    int result = sol.closestValue(root, target);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: closestValue(root, " << target << ") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: closestValue(root, " << target << ") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Build the BST for [4,2,5,1,3]:
    //         4
    //       /   \
    //      2     5
    //     / \
    //    1   3
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node2 = new TreeNode(2, node1, node3);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* root1 = new TreeNode(4, node2, node5);

    double target1 = 3.714286;
    int expected1 = 4;
    runTest(1, root1, target1, expected1);
    freeTree(root1);

    // Test Case 2:
    // Build the BST for [1]:
    TreeNode* root2 = new TreeNode(1);

    double target2 = 4.428571;
    int expected2 = 1;
    runTest(2, root2, target2, expected2);
    freeTree(root2);

    return 0;
}