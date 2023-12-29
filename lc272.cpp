/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> arr;
    void dfs(TreeNode* node){
        if(!node) return;
        dfs(node->left);
        arr.emplace_back(node->val);
        dfs(node->right);
    }
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        //traverse all the way through;
        dfs(root);
        //sliding windows
        int leftBound=0,rightBound=arr.size()-k;
        while(leftBound<rightBound){
            int mid=(leftBound+rightBound)/2;
            if(abs(target-arr[mid+k])<abs(target-arr[mid])){
                leftBound=mid+1;
            }
            else{
                rightBound=mid;
            }
        }
        vector<int> subArr(arr.begin()+leftBound,arr.begin()+leftBound+k);
        return subArr;
    }
};