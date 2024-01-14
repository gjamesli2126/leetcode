#include <bits/stdc++.h>
using namespace std;
#define mainTest main

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

    TreeNode* traverse(vector<int>& pre,vector<int>& in,int& rootInd,int leftBound,int rightBound){
        if(leftBound>rightBound) return nullptr;
        TreeNode *root=new TreeNode(pre[rootInd]);

        auto it= find(in.begin(), in.end(),pre[rootInd]);
        int split=it-in.begin();
        ++rootInd;
        root->left= traverse(pre,in,rootInd,leftBound,split-1);
        root->right= traverse(pre,in,rootInd,split+1,rightBound);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int rootInd=0;
        return traverse(preorder,inorder,rootInd,0,inorder.size()-1);

    }
};