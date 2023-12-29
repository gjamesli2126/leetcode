#include <bits/stdc++.h>
using namespace std;
//Definition for a binary tree node.
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
    vector<int> nextVec;
    vector<int>::iterator it;//=nextVec.begin();
    void inorder(TreeNode *root){
        stack<TreeNode*> stk;

        auto node=root;
        while(!stk.empty() || node){
            while(node){
                stk.push(node);
                node=node->left;
            }//node is nullptr here
            node=stk.top();
            stk.pop();
            nextVec.push_back(node->val);
            node=node->right;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        inorder(root);
        it=nextVec.begin();
    }
    
    int next() {
        auto tmpit=it;
        ++it;
        return *tmpit;
    }
    
    bool hasNext() {
        return it!=nextVec.end();
    }
};
