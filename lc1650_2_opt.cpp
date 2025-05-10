#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
    Node(int _val): val(_val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {

public:
    Node* lowestCommonAncestor(Node* p0, Node * q0) {
        //距離 of p--->root + q--->root == 距離 of q--->root + p--->root
        Node* p=p0;
        Node* q=q0;
        while(p!=q){
            if(p== nullptr) p=q0;
            else p=p->parent;
            if(q== nullptr) q=p0;
            else q=q->parent;
        }
        return p;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, Node* p, Node* q, int expectedVal) {
    Solution sol;
    Node* lca = sol.lowestCommonAncestor(p, q);
    if(lca != nullptr && lca->val == expectedVal) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: LCA = " << lca->val << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected LCA = " << expectedVal
             << ", Got " << (lca ? to_string(lca->val) : "null") << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Tree: [3,5,1,6,2,0,8,null,null,7,4]
    //        3
    //       / \
    //      5   1
    //     / \ / \
    //    6  2 0  8
    //       / \
    //      7   4
    // p = 5, q = 1, expected LCA = 3
    Node* t1_node3 = new Node(3);
    Node* t1_node5 = new Node(5);
    Node* t1_node1 = new Node(1);
    Node* t1_node6 = new Node(6);
    Node* t1_node2 = new Node(2);
    Node* t1_node0 = new Node(0);
    Node* t1_node8 = new Node(8);
    Node* t1_node7 = new Node(7);
    Node* t1_node4 = new Node(4);

    t1_node3->left = t1_node5;    t1_node3->right = t1_node1;
    t1_node5->parent = t1_node3;    t1_node1->parent = t1_node3;
    t1_node5->left = t1_node6;     t1_node5->right = t1_node2;
    t1_node6->parent = t1_node5;     t1_node2->parent = t1_node5;
    t1_node1->left = t1_node0;     t1_node1->right = t1_node8;
    t1_node0->parent = t1_node1;     t1_node8->parent = t1_node1;
    t1_node2->left = t1_node7;     t1_node2->right = t1_node4;
    t1_node7->parent = t1_node2;     t1_node4->parent = t1_node2;

    runTest(1, t1_node5, t1_node1, 3);

    // Test Case 2:
    // Using the same tree as Test Case 1, with:
    // p = 5, q = 4, expected LCA = 5
    runTest(2, t1_node5, t1_node4, 5);

    // Test Case 3:
    // Tree: [1,2]
    //       1
    //      /
    //     2
    // p = 1, q = 2, expected LCA = 1
    Node* t3_node1 = new Node(1);
    Node* t3_node2 = new Node(2);
    t3_node1->left = t3_node2;
    t3_node2->parent = t3_node1;

    runTest(3, t3_node1, t3_node2, 1);

    return 0;
}