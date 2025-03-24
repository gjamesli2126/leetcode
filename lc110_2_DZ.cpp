#include <bits/stdc++.h>
using namespace std;
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
    int height(TreeNode* root){
        if(root==nullptr) return 0;

        auto l=height(root->left);
        if(l==-1) return -1;
        auto r = height(root->right);
        if (r == -1) return -1;

        if (std::abs(l - r) > 1)
            return -1;

        return std::max(l, r) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
};
