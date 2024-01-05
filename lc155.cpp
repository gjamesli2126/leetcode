#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class MinStack {
private:
    stack<int> stk;
    stack<int> minstk;
public:
    MinStack() {}

    void push(int val) {
        stk.push(val);
        if(minstk.empty() || val<=minstk.top()) minstk.push(val);
    }

    void pop() {
        if(stk.empty()) return;
        if(minstk.top()==stk.top()) minstk.pop();
        stk.pop();
    }

    int top() {
        if(stk.empty()) return NULL;
        return stk.top();
    }

    int getMin() {
        if(minstk.empty()) return NULL;
        return minstk.top();
    }
};
int mainTest() {
    // Local function for testing conditions.
    auto test = [](bool condition, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (condition) {
            cout << GREEN << "PASS: " << testName << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << RESET << endl;
        }
    };

    MinStack* minStack = new MinStack();

    // First test case based on the example provided.
    minStack->push(-2);
    test(minStack->getMin() == -2, "Push -2, Min is -2");

    minStack->push(0);
    test(minStack->getMin() == -2, "Push 0, Min is still -2");

    minStack->push(-3);
    test(minStack->getMin() == -3, "Push -3, Min is now -3");

    minStack->pop();
    test(minStack->top() == 0, "After popping, top is 0");
    test(minStack->getMin() == -2, "After popping, Min is -2");

    // Resetting for new test case
    delete minStack;
    minStack = new MinStack();

    // New test case from the additional input and expected output.
    minStack->push(2);
    minStack->push(0);
    minStack->push(3);
    minStack->push(0);
    test(minStack->getMin() == 0, "After multiple pushes, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 0, "After popping, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 0, "After popping, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 2, "After popping, Min is 2");

    // Clean up
    delete minStack;
    return 0;
}