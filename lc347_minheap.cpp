#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //step1 build map
        unordered_map<int,int> val_freq_mp;
        for(int n:nums) val_freq_mp[n]++;
        //step2 heapify

        auto cmp=[](const pair<int,int>& a,const pair<int,int>& b){
            return a.second>b.second;//convert max heap to min heap
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(cmp)> pq;
        for(auto [val,freq]:val_freq_mp){
            pq.push({val,freq});
            if(pq.size()>k) pq.pop();
        }
        //step3 calc
        vector<int> res(k);
        for(int i=0;i<k;i++){
            auto [val,freq]=pq.top();
            pq.pop();
            res[i]=val;
        }
        return res;
    }
};

// Helper function to sort and compare two vectors (since order doesn't matter)
bool compareVectors(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

// Helper function to print a vector in the format [a, b, c, ...]
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++){
        cout << v[i];
        if (i != v.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.topKFrequent(nums, k);
    if (compareVectors(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: topKFrequent(";
        printVector(nums);
        cout << ", " << k << ") = ";
        printVector(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: topKFrequent(";
        printVector(nums);
        cout << ", " << k << ") = ";
        printVector(result);
        cout << ", expected ";
        printVector(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums = [1,1,1,2,2,3], k = 2
    // Expected Output: [1,2] (order does not matter)
    runTest(1, {1,1,1,2,2,3}, 2, {1,2});

    // Example 2:
    // Input: nums = [1], k = 1
    // Expected Output: [1]
    runTest(2, {1}, 1, {1});

    return 0;
}