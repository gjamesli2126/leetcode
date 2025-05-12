#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //in map, get the largest(most frequent) k elem -> minHeap
        unordered_map<int,int> num_freq;
        for(int n:nums) num_freq[n]++;
        //use minHeap to get the top k
        auto cmp=[](const pair<int,int>& a,const pair<int,int>& b){
                return a.second>b.second;//true then b pop first
                //in priority, if compare(a,b)==true meaning b will be popped first
                //in sorting: compare(a,b): a appears before b
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> minHeap;
        for(auto [n,f]:num_freq){
            minHeap.emplace(n,f);
            if(minHeap.size()>k) minHeap.pop();
        }
        //gathering the ans
        vector<int> ans;
//        for(int i=0;i<minHeap.size();i++) ans[i]=minHeap[i].first;
        while(!minHeap.empty()){
            ans.push_back(minHeap.top().first);
            minHeap.pop();
        }
        return ans;
    }
};
// Define the main function
int main() {
    // Define a series of test cases
    vector<pair<vector<int>, int>> testCases = {
            {{1,1,1,2,2,3}, 2},  // Example 1
            {{1}, 1},             // Example 2
            {{1,2},2}
            // Add more test cases as needed
    };

    // Define the expected outputs for each test case
    vector<vector<int>> expectedOutputs = {
            {1,2},  // Expected output for Example 1
            {1},     // Expected output for Example 2
            {1,2}
            // Add more expected outputs as needed
    };

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Create a new instance of the Solution class for each test case
        Solution solution;

        // Retrieve the actual output from the topKFrequent method
        vector<int> actualOutput = solution.topKFrequent(testCases[i].first, testCases[i].second);

        // Sort the actual output for comparison (as the order doesn't matter)
        sort(actualOutput.begin(), actualOutput.end());

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutputs[i]);

        // Print the test results
        cout << "Test " << i + 1 << ": ";
        cout << "Input: nums = [";
        for (const int &num : testCases[i].first) {
            cout << num << (num == testCases[i].first.back() ? "" : ", ");
        }
        cout << "], k = " << testCases[i].second << "; ";
        cout << "Expected: [";
        for (const int &num : expectedOutputs[i]) {
            cout << num << (num == expectedOutputs[i].back() ? "" : ", ");
        }
        cout << "], Actual: [";
        for (const int &num : actualOutput) {
            cout << num << (num == actualOutput.back() ? "" : ", ");
        }
        cout << "], Status: " << (status ? "PASS" : "FAIL") << endl;
    }

    return 0;
}
