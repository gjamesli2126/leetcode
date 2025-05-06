#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;   // previous pointer in the doubly-linked list
    Node* right;  // next pointer in the doubly-linked list

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
    Node(int _val, Node* _left, Node* _right) : val(_val), left(_left), right(_right) {}
};

class Solution {
private:
    Node* prev= nullptr,*first= nullptr;
    void helper(Node* node){
        if(!node) return;
        //left
        helper(node->left);
        //node
        if(prev){
            prev->right=node;
            node->left=prev;
        }
        else{
            first=node;
        }
        prev=node;
        //right
        helper(node->right);
    }
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return nullptr;
        helper(root);
        prev->right=first;
        first->left=prev;
        return first;
    }
};

// Helper: Build a binary tree from a vector using complete-binary-tree indexing.
// Uses -INF sentinel to represent null nodes.
Node* buildTree(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    vector<Node*> nodes(vals.size(), nullptr);
    for (size_t i = 0; i < vals.size(); ++i) {
        if (vals[i] != INT_MIN) {
            nodes[i] = new Node(vals[i]);
        }
    }
    for (size_t i = 0; i < vals.size(); ++i) {
        if (!nodes[i]) continue;
        size_t l = 2*i + 1, r = 2*i + 2;
        if (l < vals.size())  nodes[i]->left  = nodes[l];
        if (r < vals.size())  nodes[i]->right = nodes[r];
    }
    return nodes[0];
}

// Helper: Traverse the circular DLL starting from head and collect values.
vector<int> dllToVector(Node* head) {
    vector<int> res;
    if (!head) return res;
    Node* cur = head;
    do {
        res.push_back(cur->val);
        cur = cur->right;
    } while (cur && cur != head);
    return res;
}

// Helper: Free the DLL nodes (break the circle first).
void freeDLL(Node* head) {
    if (!head) return;
    head->left->right = nullptr;  // break circularity
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->right;
        delete cur;
        cur = nxt;
    }
}

// Helper: Free the original tree (pre-order delete).
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper: Run a test case.
void runTest(int testNum, vector<int> treeVals, vector<int> expected) {
    Node* root = buildTree(treeVals);
    Solution sol;
    Node* head = sol.treeToDoublyList(root);
    vector<int> result = dllToVector(head);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int v : expected) cout << v << " ";
        cout << "], Got: [";
        for (int v : result) cout << v << " ";
        cout << "]" << endl;
    }
    freeDLL(head);
    // Note: original tree nodes are reused in DLL, so no separate freeTree call.
}

int testMain(){
    // Example 1:
    // Input tree: [4, 2, 5, 1, 3] (complete binary representation)
    // Expected circular DLL order: [1, 2, 3, 4, 5]
    runTest(1, {4,2,5,1,3}, {1,2,3,4,5});

    // Example 2:
    // Input tree: [2, 1, 3]
    // Expected circular DLL order: [1, 2, 3]
    runTest(2, {2,1,3}, {1,2,3});

    return 0;
}