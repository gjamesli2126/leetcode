#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {

public:
    Node* connect(Node* root) {
        if(!root) return nullptr;
        //performing BFS
        deque<Node*> q;
        q.push_back(root);
        while(!q.empty()){
            Node* node=q.front();
            q.pop_front();
        //for par->left
            if(node->left) {
                node->left->next = node->right ? node->right : nullptr;
                q.push_back(node->left);
            }
        //for per=?right
            if(node->right) {
                if(node->next && node->next->left){
                    node->right->next = node->next->left;
                }

                q.push_back(node->right);
            }
        }
        return root;
    }
};

// Helper function to print the tree level by level using the next pointers.
// Each level is printed on one line with nodes separated by a space,
// and a '#' is printed at the end of each level.
void printTreeUsingNext(Node* root) {
    Node* levelStart = root;
    while (levelStart != nullptr) {
        Node* cur = levelStart;
        while (cur != nullptr) {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << "# ";
        levelStart = levelStart->left;
    }
    cout << endl;
}

// Helper function to run a test case and print pass (green) or fail (red).
// For this problem, visual inspection of the printed output is used.
void runTest(int testNum) {
    // Construct the following perfect binary tree:
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);

    n1->left = n2;  n1->right = n3;
    n2->left = n4;  n2->right = n5;
    n3->left = n6;  n3->right = n7;

    Solution sol;
    Node* root = sol.connect(n1);

    // Expected level order via next pointers:
    // Level 0: "1 #"
    // Level 1: "2 3 #"
    // Level 2: "4 5 6 7 #"
    cout << "Output: ";
    printTreeUsingNext(root);

    // Free the tree. (Traverse using left/right pointers, not next pointers.)
    function<void(Node*)> freeTree = [&](Node* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    };
    freeTree(n1);
}

int testMain(){
    runTest(1);
    return 0;
}
