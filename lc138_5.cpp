#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================
// 0. LeetCode Definition
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

class Solution {
private:
    unordered_map<Node*,Node*> old2new;
public:
    Node* copyRandomList(Node* head) {
        Node* cur=head;
        while(cur){
            old2new[cur]=new Node(cur->val);
            cur=cur->next;
        }
        cur=head;
        while(cur){
            old2new[cur]->next=old2new[cur->next];
            old2new[cur]->random=old2new[cur->random];
            cur=cur->next;
        }
        return old2new[head];
    }
};
// ==========================================
// 1. Solution (O(1) Interweaving Method)
// ==========================================
class Solution_O1_ref {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Step 1: Interweave (Clone Next)
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // Step 2: Copy Random
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // Step 3: Unweave (Split Lists)
        curr = head;
        Node* newHead = head->next;
        Node* copyCurr = newHead;

        while (curr) {
            curr->next = curr->next->next; // Restore original
            if (copyCurr->next) {
                copyCurr->next = copyCurr->next->next; // Move copy next
            }
            curr = curr->next;
            copyCurr = copyCurr->next;
        }

        return newHead;
    }
};

// ==========================================
// 2. Test Utilities & Stress Generator
// ==========================================

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// 構建測試鏈表 Helper
Node* buildList(const vector<pair<int, int>>& data) {
    if (data.empty()) return nullptr;
    vector<Node*> nodes;
    for (auto& p : data) nodes.push_back(new Node(p.first));
    for (int i = 0; i < data.size(); i++) {
        if (i < data.size() - 1) nodes[i]->next = nodes[i+1];
        if (data[i].second != -1) nodes[i]->random = nodes[data[i].second];
    }
    return nodes[0];
}

// **核心驗證邏輯**
bool verifyDeepCopy(Node* original, Node* copy) {
    if (!original && !copy) return true;
    if (!original || !copy) return false;

    unordered_map<Node*, int> origMap;
    unordered_map<Node*, int> copyMap;

    Node* o = original;
    Node* c = copy;
    int idx = 0;

    // 1. 建立 Index 映射並檢查值與地址
    while (o && c) {
        if (o == c) return false; // 錯誤：這是淺拷貝 (Same Address)
        if (o->val != c->val) return false; // 錯誤：值不對

        origMap[o] = idx;
        copyMap[c] = idx;
        o = o->next;
        c = c->next;
        idx++;
    }
    if (o || c) return false; // 長度不一致

    // 2. 檢查 Random 指針的拓撲結構
    o = original;
    c = copy;
    while (o) {
        int oRand = (o->random) ? origMap[o->random] : -1;
        int cRand = (c->random) ? copyMap[c->random] : -1;

        if (oRand != cRand) return false; // 錯誤：Random 指向的相對位置不同
        o = o->next;
        c = c->next;
    }
    return true;
}

// **壓力測試生成器**
Node* generateRandomList(int n) {
    if (n == 0) return nullptr;
    vector<Node*> nodes;
    // 1. 建立節點
    for (int i = 0; i < n; i++) {
        nodes.push_back(new Node(rand() % 1000)); // Random Val
    }
    // 2. 連接 Next
    for (int i = 0; i < n - 1; i++) {
        nodes[i]->next = nodes[i+1];
    }
    // 3. 連接 Random (隨機指向任一節點 或 null)
    for (int i = 0; i < n; i++) {
        int r = rand() % (n + 2); // 稍微增加 null 的機率
        if (r < n) {
            nodes[i]->random = nodes[r];
        } else {
            nodes[i]->random = nullptr;
        }
    }
    return nodes[0];
}

void runTest(int id, string name, Node* head, int& failed) {
    Solution sol;
    Node* copied = sol.copyRandomList(head);

    cout << "Test " << id << " [" << name << "]: ";
    if (verifyDeepCopy(head, copied)) {
        cout << GREEN << "PASS" << RESET << endl;
    } else {
        failed++;
        cout << RED << "FAIL" << RESET << endl;
    }

    // Memory cleanup omitted for brevity in test logic, 
    // but in production, you should delete both lists.
}

// ==========================================
// 3. Main Test Execution
// ==========================================
#define mainTest main

int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Manual Corner Cases ===" << endl;

    // Case 1: Standard
    runTest(++totalTests, "Standard Example", buildList({{7,-1},{13,0},{11,4},{10,2},{1,0}}), failedTests);

    // Case 2: Loop / Self-pointer
    runTest(++totalTests, "Self Loop", buildList({{1,0}, {2,1}}), failedTests);

    // Case 3: Null Randoms
    runTest(++totalTests, "Null Randoms", buildList({{3,-1}, {4,-1}}), failedTests);

    // Case 4: Empty
    runTest(++totalTests, "Empty List", nullptr, failedTests);


    cout << "\n=== Randomized Stress Tests (Wait...) ===" << endl;

    // 壓力測試配置
    const int STRESS_ROUNDS = 50;
    const int MAX_NODES = 1000;

    for (int i = 0; i < STRESS_ROUNDS; i++) {
        int n = rand() % MAX_NODES; // 隨機長度 0 ~ 999
        Node* randomHead = generateRandomList(n);

        string caseName = "Random Size " + to_string(n);
        Solution sol;
        Node* copied = sol.copyRandomList(randomHead);

        // 這裡不打印 PASS 以免洗版，只在失敗時報錯
        if (!verifyDeepCopy(randomHead, copied)) {
            failedTests++;
            cout << RED << "FAIL on Stress Test " << i << " (Size: " << n << ")" << RESET << endl;
        }
        totalTests++;
    }
    cout << "Stress Tests Finished (" << STRESS_ROUNDS << " rounds)." << endl;

    // ==========================================
    // Report
    // ==========================================
    double errorRate = (totalTests == 0) ? 0.0 : (double)failedTests / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) cout << "\033[94m" << "0%" << RESET;
    else cout << "\033[33m" << errorRate * 100 << "%" << RESET;
    cout << endl;

    return 0;
}