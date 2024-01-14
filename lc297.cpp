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
    void encode(ostringstream& oss,TreeNode *node){
        if(!node){
            oss<<"N ";
            return;
        }
        oss<<node->val<<" ";
        encode(oss,node->left);
        encode(oss,node->right);
    }
    TreeNode* decode(istringstream& iss){
        string str;
        iss>>str;
        if(str=="N") return nullptr;
//        TreeNode *node=new TreeNode{.val=stoi(str),.left=decode(iss),.right=decode(iss)};
        TreeNode *node=new TreeNode(stoi(str));
        node->left= decode(iss);
        node->right= decode(iss);
        return node;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        //using dfs
        encode(oss,root);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        return decode(iss);

    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));