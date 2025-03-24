#include <bits/stdc++.h>
using namespace std;
#define testMain main

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
private:
    unordered_map<Node*,Node*> mp;
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        Node* node=head;
        while(node!= nullptr){
            Node* newNode=new Node(node->val);
            mp[node]=newNode;
            node=node->next;
        }
        node=head;
        while(node!= nullptr){
            Node* newNode=mp[node];
            Node* ranNode=node->random;
            newNode->random=mp[ranNode];
            node=node->next;
            newNode->next=mp[node];
        }
        return mp[head];
    }
};

// -------------------- Helper Functions --------------------

// Build a linked list from a vector of pairs.
// Each pair is {val, random_index} where random_index is the index
// of the node that the random pointer should point to, or -1 if null.
Node* buildList(const vector<pair<int,int>>& data) {
    if(data.empty()) return nullptr;
    int n = data.size();
    vector<Node*> nodes(n, nullptr);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node(data[i].first);
    }
    for (int i = 0; i < n; i++) {
        if(i < n - 1) nodes[i]->next = nodes[i+1];
        int randomIndex = data[i].second;
        if(randomIndex >= 0 && randomIndex < n) {
            nodes[i]->random = nodes[randomIndex];
        } else {
            nodes[i]->random = nullptr;
        }
    }
    return nodes[0];
}

// Convert the linked list into a vector representation.
// Each element is a pair {val, random_index}, where random_index is -1 if null.
vector<pair<int,int>> listToVector(Node* head) {
    vector<Node*> nodes;
    Node* cur = head;
    while(cur != nullptr) {
        nodes.push_back(cur);
        cur = cur->next;
    }
    vector<pair<int,int>> result;
    for (int i = 0; i < nodes.size(); i++){
        int randomIndex = -1;
        if(nodes[i]->random != nullptr) {
            // Find index of the node pointed by random.
            for (int j = 0; j < nodes.size(); j++){
                if(nodes[i]->random == nodes[j]) {
                    randomIndex = j;
                    break;
                }
            }
        }
        result.push_back({nodes[i]->val, randomIndex});
    }
    return result;
}

// Check that the deep copy is correct: It must have the same structure and values,
// and none of the nodes in the copy should be the same as in the original.
bool checkDeepCopy(Node* original, Node* copy) {
    if(original == nullptr && copy == nullptr) return true;

    // Build vectors for original and copy.
    vector<Node*> origNodes, copyNodes;
    for(Node* cur = original; cur; cur = cur->next)
        origNodes.push_back(cur);
    for(Node* cur = copy; cur; cur = cur->next)
        copyNodes.push_back(cur);

    if(origNodes.size() != copyNodes.size())
        return false;

    // Check values and ensure that nodes are distinct.
    for (int i = 0; i < origNodes.size(); i++) {
        if(origNodes[i]->val != copyNodes[i]->val)
            return false;
        if(origNodes[i] == copyNodes[i])
            return false; // They must be different objects.
    }

    // Convert both lists to vector representations.
    vector<pair<int,int>> origRep = listToVector(original);
    vector<pair<int,int>> copyRep = listToVector(copy);

    return (origRep == copyRep);
}

// Free all nodes in a linked list to avoid memory leaks.
void freeList(Node* head) {
    while(head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

// -------------------- Test Runner --------------------

// Runs a test case: builds the original list from inputData, calls copyRandomList,
// and verifies that the deep copy has the expected vector representation.
void runTest(int testNum, const vector<pair<int,int>> &inputData, const vector<pair<int,int>> &expectedData) {
    Node* original = buildList(inputData);
    Solution sol;
    Node* copied = sol.copyRandomList(original);

    vector<pair<int,int>> copyRep = listToVector(copied);
    bool deepCopyCorrect = checkDeepCopy(original, copied);
    bool structureCorrect = (copyRep == expectedData);

    if(deepCopyCorrect && structureCorrect) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed" << "\033[0m" << endl;
        cout << "Expected Representation: ";
        for(auto &p: expectedData)
            cout << "[" << p.first << ", " << (p.second == -1 ? "null" : to_string(p.second)) << "] ";
        cout << "\nGot: ";
        for(auto &p: copyRep)
            cout << "[" << p.first << ", " << (p.second == -1 ? "null" : to_string(p.second)) << "] ";
        cout << endl;
    }

    freeList(original);
    freeList(copied);
}

int testMain(){
    // Example 1:
    // Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    // In our representation, we use -1 to denote null.
    vector<pair<int,int>> test1 = {
            {7, -1},    // Node 0: 7, random = null
            {13, 0},    // Node 1: 13, random -> Node 0
            {11, 4},    // Node 2: 11, random -> Node 4
            {10, 2},    // Node 3: 10, random -> Node 2
            {1, 0}      // Node 4: 1,  random -> Node 0
    };
    runTest(1, test1, test1);

    // Example 2:
    // Input: head = [[1,1],[2,1]]
    vector<pair<int,int>> test2 = {
            {1, 1},    // Node 0: 1, random -> Node 1
            {2, 1}     // Node 1: 2, random -> Node 1
    };
    runTest(2, test2, test2);

    // Example 3:
    // Input: head = [[3,null],[3,0],[3,null]]
    vector<pair<int,int>> test3 = {
            {3, -1},   // Node 0: 3, random = null
            {3, 0},    // Node 1: 3, random -> Node 0
            {3, -1}    // Node 2: 3, random = null
    };
    runTest(3, test3, test3);

    return 0;
}