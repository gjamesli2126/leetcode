#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string s) {
        unordered_map<int,int> daraf={
                {0,0},{1,1},{6,9},{8,8},{9,6}
        };
        int l=0,r=s.length()-1;
        while(l<=r){
            int n1=s[l]-'0';
            int n2=s[r]-'0';
            if(!daraf.contains(n1) || !daraf.contains(n2)) return false;
            if(daraf[n1]!=n2) return false;
            l++;
            r--;
        }
        return true;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string num, bool expected) {
    Solution sol;
    bool result = sol.isStrobogrammatic(num);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isStrobogrammatic(\"" << num << "\") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isStrobogrammatic(\"" << num << "\") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: num = "69"
    // Expected Output: true
    runTest(1, "69", true);

    // Test Case 2:
    // Input: num = "88"
    // Expected Output: true
    runTest(2, "88", true);

    // Test Case 3:
    // Input: num = "962"
    // Expected Output: false
    runTest(3, "962", false);

    return 0;
}