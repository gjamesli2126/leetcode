#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class MaxStack {
private:
    //for push pop top
    stack<pair<int,int>> val_id_stk;
    //for peekMAX, popMAX
    priority_queue<pair<int,int>> maxHeap;
    //for deletion when del is cheap
    unordered_set<int> removed_id;
    int id;
public:
    MaxStack():id(0) {}
    void push(int x) {
        val_id_stk.emplace(x,id);
        maxHeap.emplace(x,id);
        ++id;
    }
    int pop() {
        //del those redundent first
        while(!val_id_stk.empty() && removed_id.contains(val_id_stk.top().second)) val_id_stk.pop();
        auto [v,id]=val_id_stk.top();
        val_id_stk.pop();
        removed_id.insert(id);
        return v;
    }
    int top() {
        while(!val_id_stk.empty() && removed_id.contains(val_id_stk.top().second)) val_id_stk.pop();
        return val_id_stk.top().first;
    }
    int peekMax() {
        while(!maxHeap.empty() && removed_id.contains(maxHeap.top().second)) maxHeap.pop();//peak max O(nlogn)
        return maxHeap.top().first;
    }
    int popMax() {
        while(!maxHeap.empty() && removed_id.contains(maxHeap.top().second)) maxHeap.pop();//nlogn??
        auto [v,id]=maxHeap.top();
        removed_id.insert(id);
        return v;
    }
};

// -------- Helper functions --------

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1) cout << ", ";
    }
    cout << "]";
}

bool compareVectors(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return false;
    return true;
}

void runTest(int testNum,
             const vector<string>& ops,
             const vector<vector<int>>& vals,
             const vector<int>& expected)
{
    const string GREEN = "\033[32m";
    const string RED   = "\033[31m";
    const string RESET = "\033[0m";

    vector<int> output;
    MaxStack* stk = nullptr;

    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == "MaxStack") {
            stk = new MaxStack();
            output.push_back(INT_MIN);  // null placeholder
        }
        else if (ops[i] == "push") {
            stk->push(vals[i][0]);
            output.push_back(INT_MIN);
        }
        else if (ops[i] == "pop") {
            output.push_back(stk->pop());
        }
        else if (ops[i] == "top") {
            output.push_back(stk->top());
        }
        else if (ops[i] == "peekMax") {
            output.push_back(stk->peekMax());
        }
        else if (ops[i] == "popMax") {
            output.push_back(stk->popMax());
        }
    }

    // filter out null values
    vector<int> filtered;
    for (int x : output)
        if (x != INT_MIN) filtered.push_back(x);

    if (compareVectors(filtered, expected)) {
        cout << GREEN << "Test Case " << testNum << " PASSED: ";
        printVector(filtered);
        cout << RESET << endl;
    } else {
        cout << RED << "Test Case " << testNum << " FAILED\n";
        cout << "  Expected: ";
        printVector(expected);
        cout << "\n  Got:      ";
        printVector(filtered);
        cout << RESET << "\n";
    }
}


// -------- mainTest --------

int mainTest() {

    // Test Case 1 (Given Example)
    // ["MaxStack","push","push","push","top","popMax","top","peekMax","pop","top"]
    // [[], [5], [1], [5], [], [], [], [], [], []]
    // Output: [null,null,null,null,5,5,1,5,1,5]
    runTest(
            1,
            {"MaxStack","push","push","push","top","popMax","top","peekMax","pop","top"},
            {{},{5},{1},{5},{},{},{},{},{},{}},
            {5,5,1,5,1,5}
    );

    return 0;
}