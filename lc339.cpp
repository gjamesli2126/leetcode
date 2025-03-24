#include <bits/stdc++.h>
#define testMain main
using namespace std;

/**
 * This is a simple implementation of the NestedInteger interface for testing.
 * In an actual interview or online judge, you do not need to implement this.
 */
class NestedInteger {
private:
    bool is_int;
    int value;
    vector<NestedInteger> list;
public:
    // Constructor initializes an empty nested list.
    NestedInteger() : is_int(false) {}

    // Constructor initializes a single integer.
    NestedInteger(int value) : is_int(true), value(value) {}

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const {
        return is_int;
    }

    // Return the single integer that this NestedInteger holds.
    // The result is undefined if this NestedInteger holds a nested list.
    int getInteger() const {
        return value;
    }

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value) {
        is_int = true;
        this->value = value;
        list.clear();
    }

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni) {
        if(is_int) { // If it currently holds an integer, convert it to a list.
            int temp = value;
            list.push_back(NestedInteger(temp));
            is_int = false;
        }
        list.push_back(ni);
    }

    // Return the nested list that this NestedInteger holds, if it holds a nested list.
    // The result is undefined if this NestedInteger holds a single integer.
    const vector<NestedInteger> &getList() const {
        return list;
    }
};

class Solution {
private:
    int dfs(const vector<NestedInteger>& nestedList,int depth){
        int total=0;
        for(const NestedInteger& nl:nestedList){
            if(nl.isInteger()) total+= depth*nl.getInteger();
            else total+=dfs(nl.getList(),depth+1);
        }
        return total;
    }
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return dfs(nestedList,1);
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<NestedInteger> nestedList, int expected) {
    Solution sol;
    int result = sol.depthSum(nestedList);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: Result = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected "
             << expected << ", Got " << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nestedList = [[1,1],2,[1,1]]
    // Expected Output: 10
    vector<NestedInteger> nestedList1;
    {
        NestedInteger ni; // This will hold [1,1]
        ni.add(NestedInteger(1));
        ni.add(NestedInteger(1));
        nestedList1.push_back(ni);
    }
    nestedList1.push_back(NestedInteger(2));
    {
        NestedInteger ni; // This will hold [1,1]
        ni.add(NestedInteger(1));
        ni.add(NestedInteger(1));
        nestedList1.push_back(ni);
    }
    runTest(1, nestedList1, 10);

    // Test Case 2:
    // Input: nestedList = [1,[4,[6]]]
    // Expected Output: 27
    vector<NestedInteger> nestedList2;
    nestedList2.push_back(NestedInteger(1));
    {
        NestedInteger ni; // Will hold [4, [6]]
        ni.add(NestedInteger(4));
        {
            NestedInteger inner; // Will hold [6]
            inner.add(NestedInteger(6));
            ni.add(inner);
        }
        nestedList2.push_back(ni);
    }
    runTest(2, nestedList2, 27);

    // Test Case 3:
    // Input: nestedList = [0]
    // Expected Output: 0
    vector<NestedInteger> nestedList3;
    nestedList3.push_back(NestedInteger(0));
    runTest(3, nestedList3, 0);
    // Test Case 4:
    // Input: nestedList = [[1,1],2,[1,1]]
    // Use this test case to check if your solution is handling depths correctly.
    // Current output might be 4, but the expected output is 10.
    vector<NestedInteger> nestedList4;
    {
        NestedInteger ni; // This will hold [1,1]
        ni.add(NestedInteger(1));
        ni.add(NestedInteger(1));
        nestedList4.push_back(ni);
    }
    nestedList4.push_back(NestedInteger(2));
    {
        NestedInteger ni; // This will hold [1,1]
        ni.add(NestedInteger(1));
        ni.add(NestedInteger(1));
        nestedList4.push_back(ni);
    }
    runTest(4, nestedList4, 10);
    return 0;
}