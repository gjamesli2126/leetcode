#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> nfmp;
        vector<int> ans(k);
        for(const int& i:nums) nfmp[i]++;
        vector<vector<int>> bucket(nums.size());
        for(const auto &[k,v]:nfmp){
            bucket[v-1].push_back(k);
        }
        for(auto it=bucket.rbegin();it!= bucket.rend() && k;++it){
//            cout<<"k: "<<k<<" *it: ";
//            for(const auto &i:*it) cout<<i<<" ";
//            cout<<"////";
            if(!(*it).empty()){
                for(const int &i:*it){
//                    cout<<i<<" ";
                    ans[--k]=i;
                }
            }
//            cout<<endl;
        }

        return ans;
    }
};

// Define the mainTest function
int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

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
