class Solution {
private:
    vector<int> boundaryNodes;
    vector<int> rightBoundaryNodes;

    void addLeftBoundary(TreeNode* node) {
        while (node) {
            if (node->left || node->right) boundaryNodes.push_back(node->val);
            if (node->left) node = node->left;
            else node = node->right;
        }
    }

    void addLeaves(TreeNode* node) {
        if (!node) return;
        if (!node->left && !node->right) boundaryNodes.push_back(node->val);
        addLeaves(node->left);
        addLeaves(node->right);
    }

    void addRightBoundary(TreeNode* node) {
        while (node) {
            if (node->left || node->right) rightBoundaryNodes.push_back(node->val);
            if (node->right) node = node->right;
            else node = node->left;
        }
    }

public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return {};

        // Add root to the boundary
        boundaryNodes.push_back(root->val);

        // Add left boundary excluding leaves
        if (root->left) addLeftBoundary(root->left);

        // Add all leaves
        if (root->left || root->right) addLeaves(root);

        // Add right boundary excluding root and leaves
        if (root->right) {
            addRightBoundary(root->right);
            // Add the right boundary in reverse
            for (auto it = rightBoundaryNodes.rbegin(); it != rightBoundaryNodes.rend(); ++it) {
                boundaryNodes.push_back(*it);
            }
        }

        return boundaryNodes;
    }
};
