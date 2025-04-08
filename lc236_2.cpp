// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 *
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

		According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T
    that has both p and q as descendants (where we allow a node to be a descendant of itself).”


      T(LCA)
    /   \
   a.    q
  /
 p

 min_num_node=2;
 * */
struct Node{
    Node(){}
    int val;
    Node *left,*right;
};

class FindLCA{
private:
    Node* p,*q,*lca=nullptr;
int dfs(Node* node){
        if(!node) return 0;
        int found_stat=0;
        if(node==p || node==q){
            found_stat++;
        }
        found_stat+=dfs(node->left);
        if(lca) return 0;
        found_stat+=dfs(node->right);
        if(lca) return 0;
        if(found_stat==2) lca=node;
        return found_stat;
    }
public:
    Node* lca_fn(Node* root,Node* p0, Node* q0){
        if(p==q) return q;
        p=p0;
        q=q0;
        //dfs here
        dfs(root);
        cout<<root->val<<p0->val<<q0->val<<endl;
        return lca;
    }

};


int main() {
    vector<Node> v(5);
    for(int i=0;i<v.size();i++){
        v[i].val=i+100;

    }
    FindLCA flca;

    v[0].left=&v[1];
    v[1].left=&v[2];
    v[0].right=&v[3];

    Node* llca=flca.lca_fn(&v[0],&v[2],&v[3]);
    if(llca==nullptr) cout<<"fuck"<<endl;
    cout<<llca->val<<endl;
//    cout<<flca.lca->val<<endl;


    return 0;
}