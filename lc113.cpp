//#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;
#define mainTest main
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
    void dfs(vector<int>& path, int remain, vector<vector<int>>& pathS,TreeNode* node){
        if( node== nullptr) return;

        path.emplace_back(node->val);
        remain-=node->val;

        if(remain==0 && node->left== nullptr && node->right== nullptr){
            pathS.emplace_back(path);
//            return;
        }else {
            dfs(path, remain, pathS, node->left);
            dfs(path, remain, pathS, node->right);
        }
        path.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> pathS;
        vector<int> path;
        dfs(path,targetSum,pathS,root);
        return pathS;
    }
};

void printResult(const vector<vector<int>>& result, const vector<vector<int>>& expected) {
    if (result == expected) {
        cout << "\033[1;32mPass\033[0m "; // Green color for pass
    } else {
        cout << "\033[1;31mFail\033[0m "; // Red color for fail
    }

    cout << "Result: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            if (j > 0) cout << ", ";
            cout << result[i][j];
        }
        cout << "]";
    }
    cout << "] Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < expected[i].size(); ++j) {
            if (j > 0) cout << ", ";
            cout << expected[i][j];
        }
        cout << "]";
    }
    cout << "]" << endl;
}

int mainTest() {
    // Test Case 1
    Solution sol1;
    TreeNode* root1 = new TreeNode(5,
                                   new TreeNode(4,
                                                new TreeNode(11,
                                                             new TreeNode(7),
                                                             new TreeNode(2)),
                                                nullptr),
                                   new TreeNode(8,
                                                new TreeNode(13),
                                                new TreeNode(4,
                                                             new TreeNode(5),
                                                             new TreeNode(1))));
    int targetSum1 = 22;
    vector<vector<int>> expected1 = {{5, 4, 11, 2}, {5, 8, 4, 5}};
    vector<vector<int>> result1 = sol1.pathSum(root1, targetSum1);
    printResult(result1, expected1);

    // Test Case 2
    Solution sol2;
    TreeNode* root2 = new TreeNode(1,
                                   new TreeNode(2),
                                   new TreeNode(3));
    int targetSum2 = 5;
    vector<vector<int>> expected2 = {}; // No valid path
    vector<vector<int>> result2 = sol2.pathSum(root2, targetSum2);
    printResult(result2, expected2);

    // Test Case 3
    Solution sol3;
    TreeNode* root3 = nullptr; // Empty tree
    int targetSum3 = 0;
    vector<vector<int>> expected3 = {}; // No valid path
    vector<vector<int>> result3 = sol3.pathSum(root3, targetSum3);
    printResult(result3, expected3);

    // Test Case 4
    Solution sol4;
    TreeNode* root4 = new TreeNode(-2,
                                   nullptr,
                                   new TreeNode(-3));
    int targetSum4 = -5;
    vector<vector<int>> expected4 = {{-2, -3}};
    vector<vector<int>> result4 = sol4.pathSum(root4, targetSum4);
    printResult(result4, expected4);
    return 0;
}