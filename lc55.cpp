#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>

// Use a macro to avoid conflict if you paste this into a larger project
#define mainTest main

using namespace std;

// ==========================================
// YOUR SOLUTION CLASS
// ==========================================
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //直接從 back to front 的 Greedy
        int goal=nums.size()-1;
//        if(goal==0) return true;
        for(int i=goal-1;i>=0;i--){
            if(i+nums[i]>=goal) goal=i;
        }
        return goal==0;
    }
};

// ==========================================
// TEST HARNESS UTILITIES
// ==========================================

// Trusted Reference Solution (Greedy O(N)) to verify correctness
bool canJumpReference(const vector<int>& nums) {
    int n = nums.size();
    int maxReach = 0;
    for (int i = 0; i < n; i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) return true;
    }
    return true;
}

// Helper: Run a single test case
void runTest(int testId, vector<int>& nums, int& failedTests) {
    Solution sol;

    // Get results
    bool expected = canJumpReference(nums);
    bool actual = sol.canJump(nums);

    // Output formatting
    cout << "Test #" << testId << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red
        cout << " | Expected: " << (expected ? "true" : "false")
             << ", Actual: " << (actual ? "true" : "false");

        // Print input if it's small enough
        if (nums.size() <= 20) {
            cout << " | Input: [";
            for (int i = 0; i < nums.size(); ++i) {
                cout << nums[i] << (i == nums.size() - 1 ? "" : ",");
            }
            cout << "]";
        } else {
            cout << " | Input size: " << nums.size();
        }
        failedTests++;
    }
    cout << endl;
}

// Helper: Generate random test case
vector<int> generateRandomCase(int maxSize, int maxJump) {
    int size = (rand() % maxSize) + 1; // Length 1 to maxSize
    vector<int> nums(size);
    for (int i = 0; i < size; i++) {
        // Skew randomness: 20% chance of 0 to make "false" cases more likely
        if (rand() % 5 == 0) {
            nums[i] = 0;
        } else {
            nums[i] = rand() % (maxJump + 1);
        }
    }
    return nums;
}

int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Running Manual Edge Cases ===" << endl;

    // 1. Single element (Always true)
    {
        vector<int> nums = {0};
        runTest(++totalTests, nums, failedTests);
    }

    // 2. Basic True
    {
        vector<int> nums = {2, 3, 1, 1, 4};
        runTest(++totalTests, nums, failedTests);
    }

    // 3. Basic False
    {
        vector<int> nums = {3, 2, 1, 0, 4};
        runTest(++totalTests, nums, failedTests);
    }

    // 4. Exact reach
    {
        vector<int> nums = {2, 0, 0};
        runTest(++totalTests, nums, failedTests);
    }

    // 5. Blocked at start
    {
        vector<int> nums = {0, 2, 3};
        runTest(++totalTests, nums, failedTests);
    }

    // 6. Large jumps (overshoot is allowed)
    {
        vector<int> nums = {10, 0, 0};
        runTest(++totalTests, nums, failedTests);
    }

    // 7. Long Chain
    {
        vector<int> nums = {1, 1, 1, 1, 1, 1, 1};
        runTest(++totalTests, nums, failedTests);
    }

    // 8. Trap just before end
    {
        vector<int> nums = {1, 1, 1, 0, 1}; // Fails at index 3
        runTest(++totalTests, nums, failedTests);
    }

    // 9. Two elements false
    {
        vector<int> nums = {0, 1};
        runTest(++totalTests, nums, failedTests);
    }

    // 10. Two elements true
    {
        vector<int> nums = {1, 0};
        runTest(++totalTests, nums, failedTests);
    }

    cout << "\n=== Running Randomized Stress Tests (90 cases) ===" << endl;

    for (int i = 0; i < 90; i++) {
        // Generate random sizes up to 20, max jump value up to 5
        // We keep size small so you can debug the output if needed
        vector<int> randomNums = generateRandomCase(20, 5);
        runTest(++totalTests, randomNums, failedTests);
    }

    // ==========================================
    // ERROR RATE REPORT
    // ==========================================
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for perfect
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for errors
    }
    cout << endl;

    return 0;
}