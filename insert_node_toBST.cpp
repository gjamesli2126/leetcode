#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to insert a new element into the BST
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == NULL) {
        return new TreeNode(val);
    }

    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }

    return root;
}

// Utility function to do inorder traversal of the BST
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        std::cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    TreeNode* root = NULL;

    // Insert elements into the BST
    root = insertIntoBST(root, 5);
    root = insertIntoBST(root, 3);
    root = insertIntoBST(root, 2);
    root = insertIntoBST(root, 4);
    root = insertIntoBST(root, 7);

    // Print inorder traversal of the BST
    inorderTraversal(root);

    return 0;
}
