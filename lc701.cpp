
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root){
            TreeNode *tree=new TreeNode(val);
            return tree;
        }
        TreeNode *cur=root;
        while(true){
            if(val>cur->val) {
                if(cur->right) cur = cur->right;
                else {
                    cur->right = new TreeNode(val);
                    return root;
                }
            }
            else{
                if(cur->left) cur=cur->left;
                else{
                    cur->left=new TreeNode(val);
                    return root;
                }
            }
        }
    }
};

