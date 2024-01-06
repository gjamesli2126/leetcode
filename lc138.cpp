#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Assuming Node is defined as provided in the problem statement
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
    unordered_map<Node*,shared_ptr<Node>> mp;
public:
    Node* copyRandomList(Node* head) {
        //map old to new
        Node* cur=head;
        while(cur!= nullptr){
            mp[cur]= make_shared<Node>(cur->val);
            cur=cur->next;
        }
        mp[nullptr]= nullptr;
        cur=head;
        while(cur!= nullptr){
            mp[cur]->next=mp[cur->next].get();
            mp[cur]->random=mp[cur->random].get();
            cur=cur->next;
        }
        return mp[head].get();
    }
};

// Helper function to build the list from the given vector of values and random indices
Node* buildList(const vector<pair<int, int>>& nodes) {
    if(nodes.empty()) return nullptr;

    vector<Node*> createdNodes(nodes.size(), nullptr);
    for(int i = 0; i < nodes.size(); i++) {
        createdNodes[i] = new Node(nodes[i].first);
        if(i > 0) createdNodes[i-1]->next = createdNodes[i];
    }

    for(int i = 0; i < nodes.size(); i++) {
        int randomIndex = nodes[i].second;
        if(randomIndex != -1) {
            createdNodes[i]->random = createdNodes[randomIndex];
        }
    }

    return createdNodes[0]; // Return the head of the list
}

// Helper function to compare two lists and check if they are deep copies of each other
bool compareLists(Node* head1, Node* head2) {
    Node *temp1 = head1, *temp2 = head2;
    map<Node*, Node*> mapping;
    while(temp1 != nullptr) {
        if(temp1 == temp2) return false; // They should not be the same node (deep copy)
        if(temp1->val != temp2->val) return false; // Node values should match
        mapping[temp1] = temp2; // Map original node to its copy
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    if(temp2 != nullptr) return false; // Both lists should end together

    // Check random pointers
    temp1 = head1;
    temp2 = head2;
    while(temp1 != nullptr) {
        if(temp1->random != nullptr) {
            if(mapping[temp1->random] != temp2->random) return false;
        } else {
            if(temp2->random != nullptr) return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

int mainTest() {
    // Local function for testing conditions.
    auto test = [](bool isPass, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        cout << (isPass ? GREEN + "PASS" : RED + "FAIL") << RESET << ": " << testName << endl;
    };

    Solution solution;

    // Array of test cases
    vector<vector<pair<int, int>>> testCases = {
            {{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}},  // Test case 1
            {{1, 1}, {2, 1}},                              // Test case 2
            {{3, -1}, {3, 0}, {3, -1}}                     // Test case 3
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        Node* list = buildList(testCases[i]);
        Node* copiedList = solution.copyRandomList(list);
        bool isPass = compareLists(list, copiedList);
        test(isPass, "Test Case " + to_string(i + 1));
    }

    return 0;
}
