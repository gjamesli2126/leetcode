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
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;

        unordered_map<TreeNode*, int> height;
        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node->left && !height.contains(node->left)) {
                st.push(node->left);
            } else if (node->right && !height.contains(node->right)) {
                st.push(node->right);
            } else {
                st.pop();
                int leftHeight = (node->left ? height[node->left] : -1);
                int rightHeight = (node->right ? height[node->right] : -1);
                if (abs(leftHeight - rightHeight) > 1) return false;
                height[node] = 1 + max(leftHeight, rightHeight);
            }
        }

        return true;
    }
};
