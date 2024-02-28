#include <bits/stdc++.h>
using namespace std;

#define mainTest main

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        //one pass, odd index 要 greater than prev, even index要smaller than prev, 從 index=1開始 loop
    }
};

void printResult(const vector<int>& expected, const vector<int>& output) {
    cout << "Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        cout << expected[i];
        if (i < expected.size() - 1) cout << ",";
    }
    cout << "], Output: [";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << output[i];
        if (i < output.size() - 1) cout << ",";
    }
    cout << "]";
    if (expected == output) {
        cout << " \033[32mPass\033[0m" << endl;
    } else {
        cout << " \033[31mFail\033[0m" << endl;
    }
}

int mainTest() {
    // Test Case 1
    Solution solution1;
    vector<int> nums1 = {3, 5, 2, 1, 6, 4};
    vector<int> expected1 = {3, 5, 1, 6, 2, 4}; // One possible solution
    solution1.wiggleSort(nums1);
    printResult(expected1, nums1);

    // Test Case 2
    Solution solution2;
    vector<int> nums2 = {6, 6, 5, 6, 3, 8};
    vector<int> expected2 = {6, 6, 5, 6, 3, 8}; // One possible solution
    solution2.wiggleSort(nums2);
    printResult(expected2, nums2);

    return 0;
}
