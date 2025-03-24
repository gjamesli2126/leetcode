#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        /*start from the back to avoid using extra spaces; w/ 3 ptrs*/
        int p1=m-1;
        int p2=n-1;
        int pi=n+m-1;
        while(pi>=0){
            if(p2<0) break;//因為p1就照常
            if(p1>=0 && nums1[p1]>=nums2[p2]){
                nums1[pi]=nums1[p1];
                p1--;
            }else{//當還有p2但 p1已無
                nums1[pi]=nums2[p2];
                p2--;
            }
            pi--;
        }
    }
};

// Helper function to print a vector.
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i + 1 < v.size())
            cout << ",";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, vector<int> nums1, int m, vector<int> nums2, int n, vector<int> expected) {
    Solution sol;
    sol.merge(nums1, m, nums2, n);
    if(nums1 == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        printVector(nums1);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected ";
        printVector(expected);
        cout << " but got ";
        printVector(nums1);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    // Expected Output: [1,2,2,3,5,6]
    runTest(1, {1,2,3,0,0,0}, 3, vector<int>{2,5,6}, 3, {1,2,2,3,5,6});

    // Test Case 2:
    // Input: nums1 = [1], m = 1, nums2 = [], n = 0
    // Expected Output: [1]
    runTest(2, {1}, 1, vector<int>{}, 0, {1});

    // Test Case 3:
    // Input: nums1 = [0], m = 0, nums2 = [1], n = 1
    // Expected Output: [1]
    runTest(3, {0}, 0, vector<int>{1}, 1, {1});

    return 0;
}