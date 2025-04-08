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

class BSTIterator {
private:
    stack<TreeNode*> stk;
    void _inorder_push2stk(TreeNode* node){

        while(node) {
            stk.push(node);
            node=node->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        _inorder_push2stk(root);
    }

    int next() {
        TreeNode* topNode=stk.top();
        stk.pop();
        if(topNode->right) _inorder_push2stk(topNode->right);
        return topNode->val;
    }

    bool hasNext() {
        return !stk.empty();
    }
};
/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<string> expected) {
    // Build the BST corresponding to [7,3,15,null,null,9,20]
    //         7
    //        / \
    //       3  15
    //          / \
    //         9  20
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator* iterator = new BSTIterator(root);
    vector<string> result;
    result.push_back(to_string(iterator->next()));              // Expected output: "3"
    result.push_back(to_string(iterator->next()));              // Expected output: "7"
    result.push_back(iterator->hasNext() ? "true" : "false");     // Expected output: "true"
    result.push_back(to_string(iterator->next()));              // Expected output: "9"
    result.push_back(iterator->hasNext() ? "true" : "false");     // Expected output: "true"
    result.push_back(to_string(iterator->next()));              // Expected output: "15"
    result.push_back(iterator->hasNext() ? "true" : "false");     // Expected output: "true"
    result.push_back(to_string(iterator->next()));              // Expected output: "20"
    result.push_back(iterator->hasNext() ? "true" : "false");     // Expected output: "false"

    bool pass = (result == expected);
    if(pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "], Got: [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "]" << endl;
    }
}

int testMain(){
    // Expected sequence:
    // next() -> 3, next() -> 7, hasNext() -> true,
    // next() -> 9, hasNext() -> true, next() -> 15,
    // hasNext() -> true, next() -> 20, hasNext() -> false.
    vector<string> expected = {"3", "7", "true", "9", "true", "15", "true", "20", "false"};
    runTest(1, expected);

    return 0;
}