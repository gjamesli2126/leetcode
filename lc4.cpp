#include<bits/stdc++.h>
using namespace std;
#define mainTest main


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1,nums2);
        }

        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;

        while (left <= right) {
            int partitionA = (left + right) / 2;
            int partitionB = (m + n + 1) / 2 - partitionA;

            int maxLeftA = (partitionA == 0) ? INT_MIN : nums1[partitionA - 1];
            int minRightA = (partitionA == m) ? INT_MAX : nums1[partitionA];
            int maxLeftB = (partitionB == 0) ? INT_MIN : nums2[partitionB - 1];
            int minRightB = (partitionB == n) ? INT_MAX : nums2[partitionB];

            if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
                if ((m + n) % 2 == 0) {
                    return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
                } else {
                    return max(maxLeftA, maxLeftB);
                }
            } else if (maxLeftA > minRightB) {
                right = partitionA - 1;
            } else {
                left = partitionA + 1;
            }
        }

        return 0.0;
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
