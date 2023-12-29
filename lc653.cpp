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
private:
	unordered_set<int> s;
public:
	bool dfs(TreeNode* node,const int& k){
		if(!node) return false;
		else if(s.find(node->val)!=s.end()) return true;
		s.insert(k-node->val);
		if(dfs(node->left,k)) return true;
		if(dfs(node->right,k)) return true;
		return false;
	}
    bool findTarget(TreeNode* root, int k) {
        if(dfs(root,k)) return true;
        return false;
    }
};

/*
dzwang1997@gmail.com
Daniel0920@

*/