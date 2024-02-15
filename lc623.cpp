#include <iostream>
#include <vector>
#include <queue>
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
    queue<TreeNode*> bfs(TreeNode *root,int depth,int val){
        queue<TreeNode*> q;
        q.push(root);
        int count=0;
        while(!q.empty()){
            int n=static_cast<int>(q.size());
            ++count;
            if(count==depth-1) break;
            while(n--){
                TreeNode *cur=q.front();
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        return q;
    }
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if(depth==1){
            TreeNode *node=new TreeNode(val);
            node->left=root;
            return node;
        }
        auto q= bfs(root,depth,val);
        while (!q.empty()){
            TreeNode *cur=q.front();
            q.pop();
            TreeNode *newLeft=new TreeNode(val);
            newLeft->left=cur->left;
            cur->left=newLeft;

            TreeNode *newRight=new TreeNode(val);
            newRight->right=cur->right;
            cur->right=newRight;

        }
        return root;
    }
};

TreeNode* buildTree(const vector<int>& nums) {
    if (nums.empty() || nums[0] == -1) return nullptr; // Assuming -1 represents null

    TreeNode* root = new TreeNode(nums[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nums.size()) {
        TreeNode* node = q.front();
        q.pop();

        if (i < nums.size() && nums[i] != -1) {
            node->left = new TreeNode(nums[i]);
            q.push(node->left);
        }
        i++;

        if (i < nums.size() && nums[i] != -1) {
            node->right = new TreeNode(nums[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}

vector<int> treeToVector(TreeNode* root) {
    vector<int> result;
    queue<TreeNode*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node) {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back(-1); // Assuming -1 represents null
        }
    }

    // Remove trailing nulls
    while (!result.empty() && result.back() == -1) {
        result.pop_back();
    }

    return result;
}

void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int mainTest() {
    vector<tuple<vector<int>, int, int>> testCases = {
            {{4, 2, 6, 3, 1, 5}, 1, 2},
            {{4, 2, -1, 3, 1}, 1, 3}
    };

    Solution solution;
    for (int i = 0; i < testCases.size(); ++i) {
        TreeNode* root = buildTree(get<0>(testCases[i]));
        TreeNode* modifiedRoot = solution.addOneRow(root, get<1>(testCases[i]), get<2>(testCases[i]));
        vector<int> actualOutput = treeToVector(modifiedRoot);

        cout << "Test " << i + 1 << ": ";
        cout << "Input: root = [";
        for (int j = 0; j < get<0>(testCases[i]).size(); ++j) {
            cout << get<0>(testCases[i])[j] << (j == get<0>(testCases[i]).size() - 1 ? "" : ", ");
        }
        cout << "], val = " << get<1>(testCases[i]) << ", depth = " << get<2>(testCases[i]) << "; ";
        cout << "Output: [";
        for (int j = 0; j < actualOutput.size(); ++j) {
            cout << actualOutput[j] << (j == actualOutput.size() - 1 ? "" : ", ");
        }
        cout << "]" << endl;

        freeTree(modifiedRoot);
    }

    return 0;
}
