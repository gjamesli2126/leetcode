#include <bits/stdc++.h>
#define testMain main
using namespace std;

/**
 * Definition for a binary tree node.
 */
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
    vector<vector<int>> vec;
    const int offset=100;
    void bfs(TreeNode* root){
        deque<pair<TreeNode*,unsigned>> dq;
        dq.push_back({root,100});
        while(!dq.empty()){

            auto [node,col]=dq.front();
            dq.pop_front();
            if(node== nullptr) continue;
            vec.at(col).push_back(node->val);
            if(node->left) dq.push_back({node->left,col-1});
            if(node->right) dq.push_back({node->right,col+1});

        }
    }

public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vec.resize(200);
        bfs(root);
        vector<vector<int>> ans;
        for(auto &v:vec){
            if(v.size()) ans.push_back(v);
        }
        return ans;
    }
};

// Helper function to print a 2D vector.
void print2DVector(const vector<vector<int>>& res) {
    cout << "[";
    for (size_t i = 0; i < res.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < res[i].size(); j++) {
            cout << res[i][j];
            if(j < res[i].size()-1)
                cout << ",";
        }
        cout << "]";
        if(i < res.size()-1)
            cout << ",";
    }
    cout << "]" << endl;
}

int testMain(){
    // Test Case 1: Example 1
    // Input: root = [3,9,20,null,null,15,7]
    // Expected Output: [[9],[3,15],[20],[7]]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    {
        Solution sol;
        vector<vector<int>> res = sol.verticalOrder(root1);
        cout << "Test Case 1 Output: ";
        print2DVector(res);
    }

    // Test Case 2: Example 2
    // Input: root = [3,9,8,4,0,1,7]
    // Expected Output: [[4],[9],[3,0,1],[8],[7]]
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(8);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(0);
    root2->right->left = new TreeNode(1);
    root2->right->right = new TreeNode(7);

    {
        Solution sol;
        vector<vector<int>> res = sol.verticalOrder(root2);
        cout << "Test Case 2 Output: ";
        print2DVector(res);
    }

    // Test Case 3: Example 3
    // Input: root = [1,2,3,4,10,9,11,null,5,null,null,null,null,null,null,null,6]
    // Expected Output: [[4],[2,5],[1,10,9,6],[3],[11]]
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(3);
    root3->left->left = new TreeNode(4);
    root3->left->right = new TreeNode(10);
    root3->right->left = new TreeNode(9);
    root3->right->right = new TreeNode(11);
    root3->left->left->right = new TreeNode(5);
    root3->left->left->right->right = new TreeNode(6);

    {
        Solution sol;
        vector<vector<int>> res = sol.verticalOrder(root3);
        cout << "Test Case 3 Output: ";
        print2DVector(res);
    }

    return 0;
}