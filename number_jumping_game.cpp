#include <bits/stdc++.h>
#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION (Greedy - O(N))
// ==========================================
class Solution {
public:
    /*
     * Determines if you can reach the last index.
     * Strategy: Keep track of the 'furthest' index reachable so far.
     */
    bool canJump(const vector<int>& nums) {
        if(nums.empty()) return false;
        if(nums.size()==1) return true;
        int needed=0;
        for(int i=nums.size()-2;i>=0;i--){
            needed++;
            if(nums[i]>=needed) needed=0;
        }
        return !needed;
    }
};

// ==========================================
//  REFERENCE SOLUTION (DP - O(N^2))
// ==========================================
// Used to verify the Greedy solution on random small inputs
class ReferenceSolution {
public:
    bool canJump(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return false;

        // dp[i] means "can we reach the end starting from index i?"
        vector<bool> dp(n, false);
        dp[n-1] = true; // We are already at the end

        for (int i = n - 2; i >= 0; --i) {
            int maxJump = min(i + nums[i], n - 1);
            for (int j = i + 1; j <= maxJump; ++j) {
                if (dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};

// ==========================================
//  TEST HELPERS
// ==========================================
void printResult(string name, bool expected, bool got) {
    cout << "Test: " << left << setw(30) << name << " -> ";
    if (expected == got) {
        cout << "\033[32m[PASS]\033[0m" << endl;
    } else {
        cout << "\033[31m[FAIL]\033[0m" << endl;
        cout << "      Exp: " << (expected ? "True" : "False")
             << ", Got: " << (got ? "True" : "False") << endl;
    }
}

// ==========================================
//  MAIN DRIVER
// ==========================================
int mainTest() {
    srand(time(0));
    Solution sol;
    ReferenceSolution ref;

    cout << "=== MANUAL CASES ===" << endl;

    // Case 1: Example from the Image
    // Index: 0 1 2 3 4 5 6 7 8
    // Value: 3 2 0 1 3 1 2 0 0
    // Path: 0(3)->1(2)->3(1)->4(3)->7(0).. Stuck?
    // Wait, 0->4(3)->6(2)->8(End). Winnable.
    vector<int> imgEx = {3, 2, 0, 1, 3, 1, 2, 0, 0};
    // Note: The image says reach "final position".
    // If size is 9, final pos is index 8.
    // From 6 (val 2), we can jump to 7 or 8. So yes, winnable.
    printResult("Image Example", true, sol.canJump(imgEx));

    // Case 2: Classic Winnable
    vector<int> c1 = {2, 3, 1, 1, 4};
    printResult("Standard Winnable", true, sol.canJump(c1));

    // Case 3: Classic Stuck
    // 3->(1,2,3). 1->2. 2->1. 3->0(Stuck). All roads lead to index 3 (value 0)
    vector<int> c2 = {3, 2, 1, 0, 4};
    printResult("Standard Stuck", false, sol.canJump(c2));

    // Case 4: Single Element
    // You start at index 0. If size is 1, you are already at the end.
    vector<int> c3 = {0};
    printResult("Single Element (0)", true, sol.canJump(c3));

    // Case 5: Immediate Fail
    vector<int> c4 = {0, 2, 3};
    printResult("Start is Zero", false, sol.canJump(c4));

    // Case 6: Just barely make it
    vector<int> c5 = {1, 1, 1, 1};
    printResult("Step by Step", true, sol.canJump(c5));


    cout << endl << "=== STRESS TEST (Greedy vs DP) ===" << endl;
    // Verification on small randomized inputs
    int stressCount = 1000;
    int passed = 0;

    for(int i=0; i<stressCount; i++) {
        int len = rand() % 50 + 1; // Length 1 to 50
        vector<int> nums(len);
        for(int j=0; j<len; j++) {
            // 20% chance of 0 to create trap scenarios
            if (rand() % 5 == 0) nums[j] = 0;
            else nums[j] = rand() % 5 + 1;
        }

        bool exp = ref.canJump(nums);
        bool act = sol.canJump(nums);

        if (exp == act) passed++;
        else {
            cout << "\033[31m[FAIL]\033[0m Random Input: ";
            for(int x : nums) cout << x << " ";
            cout << "\nExp: " << exp << ", Got: " << act << endl;
            break;
        }
    }
    cout << "Correctness: " << passed << "/" << stressCount << " Passed." << endl;


    cout << endl << "=== PERFORMANCE TEST (Large Input) ===" << endl;
    // TLE Check: N = 200,000 (O(N^2) would die here)
    int N = 200000;
    vector<int> huge(N);
    for(int i=0; i<N; i++) huge[i] = 1; // Worst case for greedy? No, just linear.
    // Make it barely reachable
    huge[N-2] = 1;

    auto start = chrono::high_resolution_clock::now();
    bool res = sol.canJump(huge);
    auto end = chrono::high_resolution_clock::now();
    long long duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    if (duration < 50 && res == true) {
        cout << "\033[32m[PASS]\033[0m Large Input (" << N << " items) finished in " << duration << "ms" << endl;
    } else {
        cout << "\033[31m[FAIL]\033[0m Too Slow! Time: " << duration << "ms" << endl;
    }

    return 0;
}