#include<bits/stdc++.h>
using namespace std;
#define mainTest main


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) swap(nums1,nums2);//make nums1 the shorter
        int n1size=static_cast<int>(nums1.size());
        int n2size=static_cast<int>(nums2.size());
        int left=0,right=n1size;
        while(left<=right){

        }



        return 87426.0;
    }
};


int mainTest() {
    // Local function for testing conditions.
    auto test = [](double obtained, double expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        bool isPass = (obtained == expected);

        // Output result
        cout << (isPass ? GREEN + "[PASS]" : RED + "[FAIL]") << RESET;
        cout << ": " << testName;

        // Output expected and obtained values
        if (!isPass) {
            cout << " - Expected: " << RED << expected << RESET << ", Obtained: " << RED << obtained << RESET;
        } else {
            cout << " - Expected: " << expected << ", Obtained: " << obtained;
        }
        cout << endl;
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> nums1;
        vector<int> nums2;
        double expected;
    };

    vector<TestCase> testCases = {
            {{1, 3}, {2}, 2.00000},         // Test case 1
            {{1, 2}, {3, 4}, 2.50000},      // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        double result = solution.findMedianSortedArrays(testCases[i].nums1, testCases[i].nums2);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
