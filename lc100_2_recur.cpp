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
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(!p && !q) return true;
        else if(!p || !q) return false;

        if(p->val == q->val) return true;
        else if(isSameTree(p->left,q->left)) return true;
        else if(isSameTree(p->right,q->left)) return true;
        else return false;
    }
};