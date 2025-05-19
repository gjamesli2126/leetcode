#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
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
    TreeNode* dfs(const string& s,int& i){
        if(i==s.length()) return nullptr;
        //find the number for this val
        int stInd=i;
        if(s[i]=='-') i++;
        while(isdigit(s[i])) i++;
        int num=stoi(s.substr(stInd,i-stInd));//not i-stInd+1 becuase has ++ed
        TreeNode *left=nullptr,*right=nullptr;
        //left
        if(s[i]=='('){
            i++;//skip (
            left=dfs(s,i);
            i++;//skip )
        }
        //right
        if(s[i]=='(') {
            i++;//skip (
            right=dfs(s, i);
            i++;//skip )
        }
        return new TreeNode(num,left,right);
    }
public:
    TreeNode* str2tree(const string& s) {
        if(s.empty()) return nullptr;
        int i=0;
        return dfs(s,i);
    }
};
// Helper function: Perform level order traversal of the tree and return the node values.
vector<int> treeToLevelOrder(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();
        result.push_back(cur->val);
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
    return result;
}

// Helper function to free the tree memory.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, vector<int> expected) {
    Solution sol;
    TreeNode* root = sol.str2tree(s);
    vector<int> result = treeToLevelOrder(root);

    bool pass = (result == expected);
    if(pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: str2tree(\"" << s << "\") -> ";
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: str2tree(\"" << s << "\") -> ";
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "], expected [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    }
    freeTree(root);
}

int testMain(){
    // Example 1:
    // Input: s = "4(2(3)(1))(6(5))"
    // Expected Output (level order): [4,2,6,3,1,5]
    runTest(1, "4(2(3)(1))(6(5))", {4,2,6,3,1,5});

    // Example 2:
    // Input: s = "4(2(3)(1))(6(5)(7))"
    // Expected Output (level order): [4,2,6,3,1,5,7]
    runTest(2, "4(2(3)(1))(6(5)(7))", {4,2,6,3,1,5,7});

    // Example 3:
    // Input: s = "-4(2(3)(1))(6(5)(7))"
    // Expected Output (level order): [-4,2,6,3,1,5,7]
    runTest(3, "-4(2(3)(1))(6(5)(7))", {-4,2,6,3,1,5,7});

    return 0;
}