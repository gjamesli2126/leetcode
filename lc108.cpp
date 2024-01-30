#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    vector<int> nums;
    TreeNode* traverse(int l,int r){
        if(l>r) return nullptr;
        int m=(l+r)/2;
        auto *root= new TreeNode(nums[m]);
        root->left= traverse(l,m-1);
        root->right= traverse(m+1,r);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums0) {
        nums=std::move(nums0);
        TreeNode *root= traverse(0,static_cast<int>(nums.size())-1);
        return root;
    }
};

int getHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}
bool isBalanced(TreeNode* root) {
    if (root == nullptr) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}


#define mainTest main
int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1
    {
        Solution sol;
        vector<int> nums = {-10, -3, 0, 5, 9};
        TreeNode* expected = new TreeNode(0);
        expected->left = new TreeNode(-10);
        expected->left->right = new TreeNode(-3);
        expected->right = new TreeNode(5);
        expected->right->right = new TreeNode(9);
        TreeNode* result = sol.sortedArrayToBST(nums);
        bool balanced = isBalanced(result);
        cout << "Test #" << ++totalTests << ": ";
        if (balanced) {
            cout << "\033[32m" << "Passed" << "\033[0m" << endl; // Green for passed
        } else {
            cout << "\033[31m" << "Failed" << "\033[0m" << endl; // Red for failed
            failedTests++;
        }
    }
    // Test 2
    {
        Solution sol;
        vector<int> nums = {1, 3};
        TreeNode* expected = new TreeNode(3);
        expected->left = new TreeNode(1);
        TreeNode* result = sol.sortedArrayToBST(nums);
        bool balanced = isBalanced(result);
        cout << "Test #" << ++totalTests << ": ";
        if (balanced) {
            cout << "\033[32m" << "Passed" << "\033[0m" << endl; // Green for passed
        } else {
            cout << "\033[31m" << "Failed" << "\033[0m" << endl; // Red for failed
            failedTests++;
        }
    }

    // Add more test cases here

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
