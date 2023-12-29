/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> ans;
    void dfs(TreeNode* node){
        if(!node) return;
        dfs(node->left);
        ans.emplace_back(node->val);
        dfs(node->right);
    }
    void iter(TreeNode* root){
        stack<TreeNode*> stack;
        TreeNode* current = root;

        while (current != nullptr || !stack.empty()) {
            // Go to the leftmost node
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }

            // Current must be nullptr at this point
            current = stack.top();
            stack.pop();

            // Add the value of the node to the result
            ans.emplace_back(current->val);

            // Visit the right subtree
            current = current->right;
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        iter(root);
        return ans;
    }
};