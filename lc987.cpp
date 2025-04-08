#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for a binary tree node.
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
    vector<vector<pair<int,int>>> vec{2000,vector<pair<int,int>>()};//ind, {row,val}
    void dfs(int ind,int depth,TreeNode* node){
        if(!node) return;
        vec[ind].emplace_back(depth,node->val);
        dfs(ind-1,1+depth,node->left);
        dfs(ind+1,1+depth,node->right);
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        //travers w/ DFS whiling building a hashmap(vector,ind=0~2000)
        dfs(1000,0,root);
        //ans.push_back(sorted_sub_array)
        vector<vector<int>> ans;
        for(auto v:vec){
            if(v.empty()) continue;
            sort(v.begin(),v.end(),[&](pair<int,int> rv1,pair<int,int>rv2){
                if(rv1.first!=rv2.first) return rv1.first<rv2.first;
                return rv1.second<rv2.second;
            });
            vector<int> v_e;
            for(auto p:v) v_e.push_back(p.second);
            ans.push_back(v_e);
        }
        return ans;
    }
};

// Helper function: Build a binary tree from a vector of strings,
// where "null" represents a null node.
TreeNode* buildTree(const vector<string>& nodes) {
    if(nodes.empty() || nodes[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while(!q.empty() && i < nodes.size()){
        TreeNode* curr = q.front();
        q.pop();
        // Left child.
        if(i < nodes.size() && nodes[i] != "null"){
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;
        // Right child.
        if(i < nodes.size() && nodes[i] != "null"){
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper function: Free the allocated binary tree.
void freeTree(TreeNode* root) {
    if(root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function: Print a 2D vector.
void print2DVector(const vector<vector<int>>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << "[";
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << (j < vec[i].size()-1 ? ", " : "");
        }
        cout << "]" << (i < vec.size()-1 ? ", " : "");
    }
    cout << "]";
}

// Helper function: Run a test case.
void runTest(int testNum, vector<string> treeNodes, vector<vector<int>> expected) {
    TreeNode* root = buildTree(treeNodes);
    Solution sol;
    vector<vector<int>> result = sol.verticalTraversal(root);

    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: ";
        print2DVector(expected);
        cout << "\nGot: ";
        print2DVector(result);
        cout << endl;
    }
    freeTree(root);
}

int testMain(){
    // Test Case 1:
    // Input: root = [3,9,20,"null","null",15,7]
    // Expected Output: [[9],[3,15],[20],[7]]
    vector<string> treeNodes1 = {"3", "9", "20", "null", "null", "15", "7"};
    vector<vector<int>> expected1 = {{9}, {3,15}, {20}, {7}};
    runTest(1, treeNodes1, expected1);

    // Test Case 2:
    // Input: root = [1,2,3,4,5,6,7]
    // Expected Output: [[4],[2],[1,5,6],[3],[7]]
    vector<string> treeNodes2 = {"1", "2", "3", "4", "5", "6", "7"};
    vector<vector<int>> expected2 = {{4}, {2}, {1,5,6}, {3}, {7}};
    runTest(2, treeNodes2, expected2);

    // Test Case 3:
    // Input: root = [1,2,3,4,6,5,7]
    // Expected Output: [[4],[2],[1,5,6],[3],[7]]
    vector<string> treeNodes3 = {"1", "2", "3", "4", "6", "5", "7"};
    vector<vector<int>> expected3 = {{4}, {2}, {1,5,6}, {3}, {7}};
    runTest(3, treeNodes3, expected3);

    // Test Case 4:
    vector<string> treeNodes4 = {"3","1","4","0","2","2"};
    vector<vector<int>> expected4 = {{0},{1},{3,2,2},{4}};
    runTest(4, treeNodes4, expected4);


    return 0;
}