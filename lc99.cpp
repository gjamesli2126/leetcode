#include <bits/stdc++.h>
using namespace std;

#define mainTest main

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//1 6 20 10 11 7 27
//to
//1 6 7 10 11 20 27
//確實是 20 & 7 swap
class Solution {
private:
    TreeNode *firstFault = nullptr, *secondFault = nullptr, *prevNode = nullptr;
    void dfs(TreeNode *root) {
        if (!root) return;
        dfs(root->left);
        if (prevNode && prevNode->val >= root->val) {
            if (!firstFault) {
                firstFault = prevNode;
            }
            secondFault = root;
        }
        prevNode = root;
        dfs(root->right);
    }
public:
    void recoverTree(TreeNode* root) {
        //BST in-order traversal from min to max, use DFS
        dfs(root);
        swap(firstFault->val,secondFault->val);
    }
};

