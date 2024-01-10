#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
    int val=-101;
    TreeNode *left= nullptr;
    TreeNode *right= nullptr;
    TreeNode(int val):val(val){};
    TreeNode(TreeNode *l,TreeNode *r):left(l),right(r){};
};

class Solution{
private:
    struct Node{
        int leftLen=-1;
        int rigghtLen=-1;
        TreeNode *node;
    };
    int globalMax=0;
    int dfs(TreeNode *node){
        if(!node) return 0;
        int lMax=dfs(node->left);
        int rMax=dfs(node->right);

        globalMax=max(globalMax,1+lMax+rMax);//可能是一條龍
        int localMax=max(lMax,rMax)+1;
        return localMax;
    }
public:
    int diameterOfBinaryTree(TreeNode *root){
        if(root== nullptr) return 0;
        dfs(root);
        return --globalMax;//-- bc we were counting the max node number in a path, however the question was assking about the length of the path=node_num-1
    }
};