#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
private:
    void doInsert(Node* thisN,Node* prevN,Node* tar){
        prevN->next=tar;
        tar->next=thisN;
    }
public:
    Node* insert(Node* head, int insertVal) {
        if(!head) {
            Node* node=new Node(insertVal);
            node->next=node;
            return node;
        }

        Node* thisNode=head->next;
        Node* prevNode=head;

        do{
            if(thisNode->val>=insertVal && prevNode->val<=insertVal
                || (prevNode->val>thisNode->val)&&(insertVal<=thisNode->val || insertVal>=prevNode->val)) {
                doInsert(thisNode, prevNode, new Node(insertVal));
                return head;
            }
            thisNode=thisNode->next;
            prevNode=prevNode->next;
        }while(thisNode!=head);

        // If no insertion happened, insert after the last node.
        Node* newNode = new Node(insertVal);
        prevNode->next = newNode;
        newNode->next = thisNode;
        return head;
    }
};

// Helper function to create a circular linked list from a vector of integers.
Node* createCircularList(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    Node* head = new Node(vals[0]);
    Node* curr = head;
    for (size_t i = 1; i < vals.size(); i++) {
        curr->next = new Node(vals[i]);
        curr = curr->next;
    }
    curr->next = head; // make it circular
    return head;
}

// Helper function to convert a circular linked list to a vector of integers.
// Traverses starting from head and stops when it returns to head.
vector<int> circularListToVector(Node* head) {
    vector<int> result;
    if (!head) return result;
    Node* curr = head;
    do {
        result.push_back(curr->val);
        curr = curr->next;
    } while (curr != head);
    return result;
}

// Helper function to free the circular linked list.
void freeCircularList(Node* head) {
    if (!head) return;
    Node* curr = head->next;
    head->next = nullptr;  // Break the circularity.
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    delete head;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> inputList, int insertVal, vector<int> expected) {
    Node* head = createCircularList(inputList);
    Solution sol;
    Node* newHead = sol.insert(head, insertVal);
    vector<int> result = circularListToVector(newHead);

    bool pass = (result == expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "], Got: [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "]" << endl;
    }

    if (newHead) freeCircularList(newHead);
}

int testMain(){
    // Test Case 1:
    // Input: head = [3,4,1], insertVal = 2
    // Expected Output: [3,4,1,2]
    runTest(1, {3,4,1}, 2, {3,4,1,2});

    // Test Case 2:
    // Input: head = [], insertVal = 1
    // Expected Output: [1]
    runTest(2, {}, 1, {1});

    // Test Case 3:
    // Input: head = [1], insertVal = 0
    // Expected Output: [1,0]
    runTest(3, {1}, 0, {1,0});

    return 0;
}