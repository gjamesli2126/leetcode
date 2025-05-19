#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    unordered_map<int,unordered_set<int>> node_neis;
    void buildGraph(TreeNode* root){
        if(!root) return;
        //using bfs to traverse
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            auto node=q.front();
            q.pop();
            if(node->left){
                q.push(node->left);
                node_neis[node->val].insert(node->left->val);
                node_neis[node->left->val].insert(node->val);
            }
            if(node->right){
                q.push(node->right);
                node_neis[node->val].insert(node->right->val);
                node_neis[node->right->val].insert(node->val);
            }
            //no need to consider visited issue as only go downwards!
        }
    }
    //using bfs again to find from the target
    vector<int> findTheShit(int targetVal,int k){
        queue<pair<int,int>> q;
        q.emplace(targetVal,0);
        vector<int> ans;
        unordered_set<int> visited;
        while(!q.empty()){
            auto [node_val,dist]=q.front();
            q.pop();
            if(dist==k) ans.push_back(node_val);
            for(int nei:node_neis[node_val]){
                if(visited.contains(nei)) continue;
                q.emplace(nei,dist+1);
            }
            visited.insert(node_val);
        }
        return ans;
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        //solution: 與其用tree不如轉成 graph
        buildGraph(root);
        return findTheShit(target->val,k);
    }
};
// Helper function: Build a binary tree from a vector of strings (level-order).
// "null" represents an empty node.
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* cur = q.front();
        q.pop();
        if (i < nodes.size() && nodes[i] != "null") {
            cur->left = new TreeNode(stoi(nodes[i]));
            q.push(cur->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "null") {
            cur->right = new TreeNode(stoi(nodes[i]));
            q.push(cur->right);
        }
        i++;
    }
    return root;
}

// Helper function: Find the target node with the given value.
TreeNode* findTarget(TreeNode* root, int targetVal) {
    if (!root) return nullptr;
    if (root->val == targetVal) return root;
    TreeNode* left = findTarget(root->left, targetVal);
    if (left) return left;
    return findTarget(root->right, targetVal);
}

// Helper function: Free the allocated binary tree.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function: Run a test case and print pass (green) or fail (red).
// Since the answer can be returned in any order, we'll sort both expected and result.
void runTest(int testNum, vector<string> treeNodes, int targetVal, int k, vector<int> expected) {
    TreeNode* root = buildTree(treeNodes);
    TreeNode* target = findTarget(root, targetVal);
    Solution sol;
    vector<int> result = sol.distanceK(root, target, k);
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());

    bool pass = (result == expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size() - 1 ? ", " : "");
        }
        cout << "], Got: [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }

    freeTree(root);
}

int testMain(){
    // Test Case 1:
    // Input: root = [3,5,1,6,2,0,8,"null","null",7,4], target = 5, k = 2
    // Expected Output: [7,4,1]
    vector<string> treeNodes1 = {"3", "5", "1", "6", "2", "0", "8", "null", "null", "7", "4"};
    runTest(1, treeNodes1, 5, 2, {7, 4, 1});

    // Test Case 2:
    // Input: root = [1], target = 1, k = 3
    // Expected Output: []
    vector<string> treeNodes2 = {"1"};
    runTest(2, treeNodes2, 1, 3, {});

    return 0;
}