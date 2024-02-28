#include <bits/stdc++.h>
using namespace std;
#define mainTest main

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Codec {
private:
    void encoder(ostringstream& oss,TreeNode *root){
        if(!root){
            oss<<"N ";
            return;
        }
        oss<<root->val<<" ";
        encoder(oss,root->left);
        encoder(oss,root->right);
    }
    TreeNode* decoder(istringstream& iss){
        string s;
        iss>>s;
        if(s=="N") return nullptr;
        TreeNode *node=new TreeNode(stoi(s));
        node->left= decoder(iss);
        node->right=decoder(iss);
        return node;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        encoder(oss,root);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const string& data) {
        istringstream iss(data);
        return decoder(iss);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));