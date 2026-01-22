#define mainTest main
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

// ==========================================
// YOUR SOLUTION GOES HERE
// ==========================================
class Solution {
public:
    Node* lowestCommonAncestor(Node* p0, Node * q0) {
        if(p0==q0) return q0;
        Node* p=p0;
        Node* q=q0;
        while(p!=q){
            p=p->parent?p->parent:p=q0;
            q=q->parent?q->parent:q=p0;
        }
        return q;
    }
};

// ==========================================
// TEST HARNESS (Do not modify)
// ==========================================

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Helper: Build tree and WIRE UP PARENT POINTERS
Node* buildTree(const vector<int>& nodes) {
    if (nodes.empty()) return nullptr;

    Node* root = new Node(nodes[0]);
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (i < nodes.size()) {
        Node* curr = q.front();
        q.pop();

        // Left Child
        if (i < nodes.size() && nodes[i] != INT_MIN) {
            curr->left = new Node(nodes[i]);
            curr->left->parent = curr; // <--- Critical for this problem
            q.push(curr->left);
        }
        i++;

        // Right Child
        if (i < nodes.size() && nodes[i] != INT_MIN) {
            curr->right = new Node(nodes[i]);
            curr->right->parent = curr; // <--- Critical for this problem
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper: Find node pointer by value
Node* findNode(Node* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    Node* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

void runTest(vector<int> treeData, int pVal, int qVal, int expectedVal, string testName) {
    Node* root = buildTree(treeData);
    Node* p = findNode(root, pVal);
    Node* q = findNode(root, qVal);

    Solution sol;
    Node* result = sol.lowestCommonAncestor(p, q);

    cout << "Test: " << testName << " | p=" << pVal << ", q=" << qVal << endl;

    bool passed = false;
    if (result != nullptr && result->val == expectedVal) {
        passed = true;
    }

    if (passed) {
        cout << GREEN << "  [PASS] " << RESET << "Output: " << result->val << endl;
    } else {
        cout << RED << "  [FAIL] " << RESET;
        if (result == nullptr) cout << "Output: null";
        else cout << "Output: " << result->val;
        cout << " (Expected: " << expectedVal << ")" << endl;
    }
    cout << "------------------------------------------------" << endl;
}

int mainTest() {
    // INT_MIN represents 'null' in the input vector

    // Example 1
    // Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
    // Output: 3
    vector<int> t1 = {3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4};
    runTest(t1, 5, 1, 3, "Example 1");

    // Example 2
    // Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
    // Output: 5
    runTest(t1, 5, 4, 5, "Example 2 (Descendant)");

    // Example 3
    // Input: root = [1,2], p = 1, q = 2
    // Output: 1
    vector<int> t3 = {1, 2};
    runTest(t3, 1, 2, 1, "Example 3 (Small)");

    return 0;
}