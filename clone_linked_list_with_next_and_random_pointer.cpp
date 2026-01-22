#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <iomanip>

#define mainTest main
using namespace std;

// ==========================================
//  NODE DEFINITION
// ==========================================
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

// ==========================================
//  USER SOLUTION (To Implement)
// ==========================================
class Solution {
public:
    /*
     * Deep copy the given linked list.
     * Constraint: Time Limit 200ms for N=100,000
     */
    unordered_map<Node*,Node*> node_cpy;
    Node* copyRandomList(Node* head) {
        // TODO: Implement O(N) Deep Copy Logic
        Node* h=head;
        while(h){
            Node* newNode=new Node(h->val);
            node_cpy[h]=newNode;
            h=h->next;
        }
        h=head;
        while(h){
            node_cpy[h]->next=node_cpy[h->next];
            node_cpy[h]->random=node_cpy[h->random];
            h=h->next;
        }
        return node_cpy[head];
    }
};

// ==========================================
//  TEST HELPERS & VALIDATORS
// ==========================================

Node* createList(const vector<pair<int, int>>& data) {
    if (data.empty()) return nullptr;
    int n = data.size();
    vector<Node*> nodes(n);
    for(int i=0; i<n; ++i) nodes[i] = new Node(data[i].first);
    for(int i=0; i<n; ++i) {
        if (i < n - 1) nodes[i]->next = nodes[i+1];
        int randIdx = data[i].second;
        if (randIdx != -1) nodes[i]->random = nodes[randIdx];
    }
    return nodes[0];
}

bool verifyDeepCopy(Node* original, Node* copy) {
    if (!original && !copy) return true;
    if (!original || !copy) return false;

    unordered_map<Node*, Node*> mapping;
    Node* o = original;
    Node* c = copy;

    // Pass 1: Structure & Values
    while (o && c) {
        if (o == c) return false; // Shallow copy error
        if (o->val != c->val) return false;
        mapping[o] = c;
        o = o->next;
        c = c->next;
    }
    if (o || c) return false;

    // Pass 2: Random Pointers
    o = original;
    c = copy;
    while (o) {
        Node* oRand = o->random;
        Node* cRand = c->random;
        if (oRand) {
            if (mapping.find(oRand) == mapping.end() || mapping[oRand] != cRand) return false;
        } else {
            if (cRand != nullptr) return false;
        }
        o = o->next;
        c = c->next;
    }
    return true;
}

void freeList(Node* head) {
    while(head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// ==========================================
//  MAIN DRIVER
// ==========================================
int mainTest() {
    srand(time(0));
    Solution sol;
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== CORRECTNESS TESTS ===" << endl;

    // Case 1: Standard
    totalTests++;
    cout << "Test #" << totalTests << " (Standard): ";
    Node* list1 = createList({{7,-1}, {13,0}, {11,4}, {10,2}, {1,0}});
    Node* copy1 = sol.copyRandomList(list1);
    if (verifyDeepCopy(list1, copy1)) cout << "\033[32m[PASS]\033[0m" << endl;
    else { cout << "\033[31m[FAIL]\033[0m" << endl; failedTests++; }
    freeList(list1); freeList(copy1);

    // Case 2: Empty
    totalTests++;
    cout << "Test #" << totalTests << " (Empty): ";
    Node* res2 = sol.copyRandomList(nullptr);
    if (res2 == nullptr) cout << "\033[32m[PASS]\033[0m" << endl;
    else { cout << "\033[31m[FAIL]\033[0m" << endl; failedTests++; }

    // Case 3: Random Cycle (Self Loop)
    totalTests++;
    cout << "Test #" << totalTests << " (Cycle/Self-Loop): ";
    Node* list3 = createList({{1,0}, {2,0}});
    Node* copy3 = sol.copyRandomList(list3);
    if (verifyDeepCopy(list3, copy3)) cout << "\033[32m[PASS]\033[0m" << endl;
    else { cout << "\033[31m[FAIL]\033[0m" << endl; failedTests++; }
    freeList(list3); freeList(copy3);


    cout << endl << "=== PERFORMANCE TEST (TLE CHECK) ===" << endl;

    // Config: N = 100,000 nodes
    int N = 100000;
    int timeLimitMs = 200; // Strict limit for O(N)

    cout << "Generating Large List (N=" << N << ")... ";
    cout.flush();

    vector<pair<int, int>> largeData(N);
    for(int i=0; i<N; i++) {
        largeData[i].first = i;
        // Random pointer to anywhere, or null
        if (rand() % 5 == 0) largeData[i].second = -1;
        else largeData[i].second = rand() % N;
    }
    Node* largeList = createList(largeData);
    cout << "Done." << endl;

    cout << "Running Solution... ";
    cout.flush();

    // Timer Start
    auto start = chrono::high_resolution_clock::now();

    Node* largeCopy = sol.copyRandomList(largeList);

    // Timer End
    auto end = chrono::high_resolution_clock::now();
    long long duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Finished in " << duration << "ms." << endl;

    bool timePass = (duration <= timeLimitMs);
    bool correctPass = verifyDeepCopy(largeList, largeCopy); // Still need to verify it works!

    if (timePass && correctPass) {
        cout << "Result: \033[32m[PASS]\033[0m (Within " << timeLimitMs << "ms limit)" << endl;
    } else {
        cout << "Result: \033[31m[FAIL]\033[0m" << endl;
        if (!timePass) cout << "  -> Time Limit Exceeded! (" << duration << "ms > " << timeLimitMs << "ms)" << endl;
        if (!correctPass) cout << "  -> Output Incorrect (Deep copy verification failed)" << endl;
        failedTests++;
    }

    // Cleanup Large List (Might take a moment)
    // freeList(largeList);
    // freeList(largeCopy);

    cout << endl << "==========================================" << endl;
    if(failedTests == 0) cout << "\033[32mAll Tests Passed\033[0m" << endl;
    else cout << "\033[31mTests Failed: " << failedTests << "\033[0m" << endl;
    cout << "==========================================" << endl;

    return 0;
}