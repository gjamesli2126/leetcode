#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class MaxStack {
private:
    map<int,stack<list<int>::iterator>> val_iterS;
    list<int> lst;

public:
    MaxStack() {

    }
    void push(int x) {
        lst.emplace_back(x);
        val_iterS[x].emplace(prev(lst.end()));//emaplce 裡也要放正向 iter
    }
    int pop() {
        int back=lst.back();
        val_iterS[back].pop();
        //might retain empty stack
        if(val_iterS[back].empty()) val_iterS.erase(back);
        lst.pop_back();
        return back;
    }
    int top() {
        return lst.back();
    }
    int peekMax() {
        return val_iterS.rbegin()->first;
    }
    int popMax() {
        auto max_kv_it=val_iterS.rbegin();
        int v=max_kv_it->first;
        auto& itS=max_kv_it->second;
        lst.erase(itS.top());//what if multiple max??
        itS.pop();
        if(itS.empty()) val_iterS.erase(v);
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