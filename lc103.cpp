#include <bits/stdc++.h>
using namespace std;

#define mainTest main

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    vector<vector<int>> bfs(TreeNode *root){
        if(!root) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> ans;
        bool even=true;
        while(!q.empty()){
            size_t n=q.size();
            vector<int> subAns(n);

            for(size_t i=0;i<n;++i){
                TreeNode *node=q.front();
                q.pop();
                size_t index=even?i:n-1-i;
                subAns[index]=node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            even=!even;
            ans.push_back(subAns);
        }
        return ans;
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        return bfs(root);
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (const auto& level : result) {
        cout << "[";
        for (size_t i = 0; i < level.size(); ++i) {
            cout << level[i];
            if (i < level.size() - 1) cout << ",";
        }
        cout << "]";
    }
    cout << "]" << endl;
}

TreeNode* createTree(const vector<int>& nodes) {
    if (nodes.empty()) return nullptr;
    queue<TreeNode*> q;
    TreeNode* root = new TreeNode(nodes[0]);
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();
        if (nodes[i] != INT_MIN) {
            current->left = new TreeNode(nodes[i]);
            q.push(current->left);
        }
        ++i;
        if (i < nodes.size() && nodes[i] != INT_MIN) {
            current->right = new TreeNode(nodes[i]);
            q.push(current->right);
        }
        ++i;
    }
    return root;
}

int mainTest() {
    // Test Case 1
    Solution solution1;
    vector<int> nodes1 = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    TreeNode* root1 = createTree(nodes1);
    vector<vector<int>> expected1 = {{3}, {20, 9}, {15, 7}};
    vector<vector<int>> output1 = solution1.zigzagLevelOrder(root1);
    cout << "Expected: ";
    printResult(expected1);
    cout << "Output: ";
    printResult(output1);

    // Test Case 2
    Solution solution2;
    vector<int> nodes2 = {1};
    TreeNode* root2 = createTree(nodes2);
    vector<vector<int>> expected2 = {{1}};
    vector<vector<int>> output2 = solution2.zigzagLevelOrder(root2);
    cout << "Expected: ";
    printResult(expected2);
    cout << "Output: ";
    printResult(output2);

    // Test Case 3
    Solution solution3;
    vector<int> nodes3 = {};
    TreeNode* root3 = createTree(nodes3);
    vector<vector<int>> expected3 = {};
    vector<vector<int>> output3 = solution3.zigzagLevelOrder(root3);
    cout << "Expected: ";
    printResult(expected3);
    cout << "Output: ";
    printResult(output3);

    return 0;
}
