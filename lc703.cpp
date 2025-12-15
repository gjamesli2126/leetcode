#include <bits/stdc++.h>
#define testMain main
using namespace std;

class KthLargest {
private:
    priority_queue<int,vector<int>,greater<int>> minHeap;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        //using minHeap to get the k largest
        for(int n:nums){
            minHeap.emplace(n);
            if(minHeap.size()>k) minHeap.pop();
        }
        this->k=k;
    }

    int add(int val) {
        minHeap.emplace(val);
        if(minHeap.size()>k) minHeap.pop();
        return minHeap.top();
    }
};

// ------------------ Helpers ------------------

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
             int k, vector<int> nums,
             vector<string> ops,
             vector<vector<int>> vals,
             vector<int> expectedOutput)
{
    vector<int> results;
    KthLargest* obj = nullptr;

    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == "KthLargest") {
            obj = new KthLargest(k, nums);
            results.push_back(INT_MIN); // placeholder for null
        } else if (ops[i] == "add") {
            int r = obj->add(vals[i][0]);
            results.push_back(r);
        }
    }

    // Remove placeholder (INT_MIN) to compare outputs
    vector<int> filtered;
    vector<int> expectedFiltered;

    for (int x : results)
        if (x != INT_MIN)
            filtered.push_back(x);

    for (int x : expectedOutput)
        expectedFiltered.push_back(x);

    if (compareVectors(filtered, expectedFiltered)) {
        cout << "\033[1;32mTest Case " << testNum << " PASSED: Output = ";
        printVector(filtered);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " FAILED!" << endl;
        cout << "Your Output = ";
        printVector(filtered);
        cout << ",   Expected = ";
        printVector(expectedFiltered);
        cout << "\033[0m" << endl;
    }
}

// ------------------ mainTest ------------------

int testMain() {

    // ---------------- Example 1 ----------------
    // ["KthLargest","add","add","add","add","add"]
    // [[3, [4,5,8,2]], [3], [5], [10], [9], [4]]
    // Output: [null, 4, 5, 5, 8, 8]

    runTest(
            1,
            3,
            {4,5,8,2},
            {"KthLargest","add","add","add","add","add"},
            {{},{3},{5},{10},{9},{4}},
            {4,5,5,8,8}
    );

    // ---------------- Example 2 ----------------
    // ["KthLargest","add","add","add","add"]
    // [[4,[7,7,7,7,8,3]], [2], [10], [9], [9]]
    // Output: [null,7,7,7,8]

    runTest(
            2,
            4,
            {7,7,7,7,8,3},
            {"KthLargest","add","add","add","add"},
            {{},{2},{10},{9},{9}},
            {7,7,7,8}
    );
    // ---------------- Example 3 ----------------
    // ["KthLargest","add","add","add","add","add"]
    // [[1, []], [-3], [-2], [-4], [0], [4]]
    // Output: [null, -3, -2, -2, 0, 4]

    runTest(
            3,
            1,
            {},    // 初始 nums = []
            {"KthLargest","add","add","add","add","add"},
            {{},{-3},{-2},{-4},{0},{4}},
            {-3, -2, -2, 0, 4}
    );
    return 0;
}