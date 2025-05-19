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
public:
    int closestValue(TreeNode* root, double target) {
        //記錄採用處處留情，traverse是一條鞭法(one path)
        pair<int,double> val_delta={root->val,abs(target-root->val)};//msue use double!!
        while(root){
            if(abs(target-root->val)<val_delta.second) val_delta={root->val,abs(target-root->val)};
            //if the delta is the same, use the smaller number
            else if(abs(target-root->val)==val_delta.second) val_delta.first=min(val_delta.first,root->val);
            if(root->left && root->right){
                if(target<root->val) root=root->left;
                else if(target>root->val) root=root->right;
                else return root->val;//found the exact value
            }
            else if(root->left) root=root->left;
            else root=root->right;
        }
        return val_delta.first;
    }
};
// Helper function to free the binary tree.
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, TreeNode* root, double target, int expected) {
    Solution sol;
    int result = sol.closestValue(root, target);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: closestValue(root, " << target << ") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: closestValue(root, " << target << ") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

/*  Build from level order.
 *  – `nullopt`  →  absent child
 *  –  Works for arbitrarily large trees.
 */
TreeNode* buildTree(const std::vector<optional<int>>& lvl) {
    if (lvl.empty() || !lvl[0].has_value()) return nullptr;

    TreeNode* root = new TreeNode(*lvl[0]);
    std::queue<TreeNode*> q;
    q.push(root);

    std::size_t i = 1;
    while (!q.empty() && i < lvl.size()) {
        TreeNode* cur = q.front();
        q.pop();

        if (i < lvl.size() && lvl[i].has_value()) {          // left
            cur->left = new TreeNode(*lvl[i]);
            q.push(cur->left);
        }
        ++i;

        if (i < lvl.size() && lvl[i].has_value()) {          // right
            cur->right = new TreeNode(*lvl[i]);
            q.push(cur->right);
        }
        ++i;
    }
    return root;
}

int testMain(){
    // Test Case 1:
    // Build the BST for [4,2,5,1,3]:
    //         4
    //       /   \
    //      2     5
    //     / \
    //    1   3
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node2 = new TreeNode(2, node1, node3);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* root1 = new TreeNode(4, node2, node5);

    double target1 = 3.714286;
    int expected1 = 4;
    runTest(1, root1, target1, expected1);

    double target0 = 3.5;
    int expected0 = 3;
    runTest(0, root1, target0, expected0);
    freeTree(root1);


    // Test Case 2:
    // Build the BST for [1]:
    TreeNode* root2 = new TreeNode(1);

    double target2 = 4.428571;
    int expected2 = 1;
    runTest(2, root2, target2, expected2);
    freeTree(root2);


    //testcase4:
    std::vector<optional<int>> bigLvl = {
            /* 0-based idx  : value */
            /* 0  */ 41,
            /* 1  */ 37,
            /* 2  */ 44,
            /* 3  */ 24,
            /* 4  */ 39,
            /* 5  */ 42,
            /* 6  */ 48,
            /* 7  */ 1,
            /* 8  */ 35,
            /* 9  */ 38,
            /* 10 */ 40,
            /* 11 */ nullopt,
            /* 12 */ 43,
            /* 13 */ 46,
            /* 14 */ 49,
            /* 15 */ 0,
            /* 16 */ 2,
            /* 17 */ 30,
            /* 18 */ 36,
            /* 19 */ nullopt, /*20*/ nullopt, /*21*/ nullopt,
            /*22*/ nullopt, /*23*/ nullopt, /*24*/ nullopt,
            /* 25 */ 45,
            /* 26 */ 47,
            /* 27 */ nullopt, /*28*/ nullopt, /*29*/ nullopt,
            /*30*/ nullopt, /*31*/ nullopt,
            /* 32 */ 4,
            /* 33 */ 29,
            /* 34 */ 32,
            /* 35 */ nullopt, /*36*/ nullopt, /*37*/ nullopt,
            /*38*/ nullopt, /*39*/ nullopt, /*40*/ nullopt,
            /* 41 */ 3,
            /* 42 */ 9,
            /* 43 */ 26,
            /* 44 */ nullopt,
            /* 45 */ 31,
            /* 46 */ 34,
            /* 47 */ nullopt, /*48*/ nullopt,
            /* 49 */ 7,
            /* 50 */ 11,
            /* 51 */ 25,
            /* 52 */ 27,
            /* 53 */ nullopt, /*54*/ nullopt,
            /* 55 */ 33,
            /* 56 */ nullopt,
            /* 57 */ 6,
            /* 58 */ 8,
            /* 59 */ 10,
            /* 60 */ 16,
            /* 61 */ nullopt, /*62*/ nullopt, /*63*/ nullopt,
            /* 64 */ 28,
            /* 65 */ nullopt, /*66*/ nullopt,
            /* 67 */ 5,
            /* 68 */ nullopt, /*69*/ nullopt, /*70*/ nullopt,
            /*71*/ nullopt, /*72*/ nullopt,
            /* 73 */ 15,
            /* 74 */ 19,
            /* 75 */ nullopt, /*76*/ nullopt, /*77*/ nullopt, /*78*/ nullopt,
            /* 79 */ 12,
            /* 80 */ nullopt,
            /* 81 */ 18,
            /* 82 */ 20,
            /* 83 */ nullopt,
            /* 84 */ 13,
            /* 85 */ 17,
            /* 86 */ nullopt, /*87*/ nullopt,
            /* 88 */ 22,
            /* 89 */ nullopt,
            /* 90 */ 14,
            /* 91 */ nullopt, /*92*/ nullopt,
            /* 93 */ 21,
            /* 94 */ 23
    };

    TreeNode* root3 = buildTree(bigLvl);

    double  target3   = 3.285714;
    int     expected3 = 3;
    runTest(3, root3, target3, expected3);
    freeTree(root3);
    return 0;
}