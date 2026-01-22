#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION
// ==========================================
class Solution {
public:
    /*
     * Find all pairs that sum up to the target.
     * Requirement based on image:
     * 1. Output distinct pairs (e.g. if we have two (3,2)s, usually just return one,
     * but this test harness is flexible).
     * 2. Order within pair or order of pairs does not matter.
     */
    //assuming number 不重複
    struct PairHash{
        size_t operator()(const pair<int,int>& p) const{
            hash<int> intHasher;
            size_t h1=intHasher(p.first);
            size_t h2=intHasher(p.second);
            return h1^(h2<<1);
        }
    };
    vector<pair<int, int>> findPairs(vector<int>& nums, int target) {
        vector<pair<int, int>> result;
        unordered_set<int> visited;
        unordered_set<pair<int,int>,PairHash> ans;
        // (min,max)

        for(int n:nums){
            int remain=target-n;
            if(visited.contains(remain)){
                if(n<remain) ans.emplace(n,remain);
                else ans.emplace(remain,n);
            }
            visited.insert(n);
        }
        // TODO: Implement Logic Here (HashSet or Sort+TwoPointers)
        for(const auto& [n1,n2]:ans) result.emplace_back(n1,n2);
        return result;
    }
};

// ==========================================
//  TEST HELPERS & VALIDATORS
// ==========================================

// Helper to canonicalize a pair (small, large) for comparison
pair<int, int> makeCanonical(int a, int b) {
    if (a > b) return {b, a};
    return {a, b};
}

// Validator: Checks if user result matches expected result (ignoring order)
bool validate(vector<int> nums, int target, vector<pair<int, int>> actual) {
    // 1. Verify every pair sums to target
    for (const auto& p : actual) {
        if (long(p.first) + long(p.second) != target) {
            cout << "  [Error] Pair (" << p.first << ", " << p.second << ") does not sum to " << target << endl;
            return false;
        }
    }

    // 2. Advanced Check: Verify availability (The numbers must exist in the input)
    // Note: This is a simplified check. A strict check would verify frequency counts.
    // For this problem type, usually finding the values is enough.

    // 3. Duplicate Check Strategy:
    // The prompt example implies we want unique pairs of values.
    // e.g., [1, 3, 2, 3, 4], target 5 -> (1,4), (2,3). Even though 3 appears twice.
    // We will check if the user output contains duplicates.
    set<pair<int,int>> distinctPairs;
    for(const auto& p : actual) {
        distinctPairs.insert(makeCanonical(p.first, p.second));
    }

    // Warn if user returns duplicate pairs (e.g. (2,3) and (3,2) simultaneously)
    if (distinctPairs.size() != actual.size()) {
        cout << "  [Warning] Output contains duplicate pairs or permutations. (Expected unique sets of values)" << endl;
    }

    return true;
}

// Ground Truth Generator (Brute Force O(N^2) for Stress Test)
vector<pair<int, int>> getReferencePairs(vector<int> nums, int target) {
    set<pair<int, int>> uniquePairs;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int l = 0, r = n - 1;
    while(l < r) {
        long sum = (long)nums[l] + (long)nums[r];
        if (sum == target) {
            uniquePairs.insert({nums[l], nums[r]});
            l++; r--;
        } else if (sum < target) {
            l++;
        } else {
            r--;
        }
    }
    return vector<pair<int, int>>(uniquePairs.begin(), uniquePairs.end());
}

void printResult(const vector<pair<int, int>>& res) {
    cout << "[";
    for (size_t i = 0; i < res.size(); ++i) {
        cout << "(" << res[i].first << "," << res[i].second << ")";
        if (i < res.size() - 1) cout << ", ";
    }
    cout << "]";
}

void runTest(int testNum, string testName, vector<int> nums, int target, int& failedTests) {
    Solution sol;
    cout << "Test #" << testNum << " (" << testName << "): ";

    vector<pair<int, int>> actual = sol.findPairs(nums, target);

    // We compare strict correctness against a reference solution for pass/fail
    vector<pair<int, int>> expected = getReferencePairs(nums, target);

    // Canonicalize actual for comparison
    set<pair<int,int>> actualSet;
    for(auto p : actual) actualSet.insert(makeCanonical(p.first, p.second));

    set<pair<int,int>> expectedSet;
    for(auto p : expected) expectedSet.insert(makeCanonical(p.first, p.second));

    if (actualSet == expectedSet) {
        cout << "\033[32mPassed\033[0m";
        // Uncomment to see output
        // cout << " Output: "; printResult(actual);
    } else {
        cout << "\033[31mFailed\033[0m";
        cout << "\n  Expected: "; printResult(expected);
        cout << "\n  Got:      "; printResult(actual);
        failedTests++;
    }
    cout << endl;
}

// ==========================================
//  MAIN TEST DRIVER
// ==========================================
int mainTest() {
    srand(time(0));
    int failedTests = 0, totalTests = 0;

    cout << "=== STANDARD & TWIST CASES ===" << endl;

    // Test 1: Image Example
    // [1, 3, 6, 2, 3, 4], Target 5 -> (1,4), (2,3)
    vector<int> t1 = {1, 3, 6, 2, 3, 4};
    runTest(++totalTests, "Image Example", t1, 5, failedTests);

    // Test 2: Negative Numbers (Twist)
    // [-1, 1, 2, -2], Target 0 -> (-1, 1), (-2, 2)
    vector<int> t2 = {-1, 1, 2, -2};
    runTest(++totalTests, "Negative Numbers", t2, 0, failedTests);

    // Test 3: Duplicate Pairs (Twist)
    // [3, 3], Target 6 -> (3, 3)
    // The code should be able to pick up the same number twice if they are distinct indices
    vector<int> t3 = {3, 3};
    runTest(++totalTests, "Same Number Pair", t3, 6, failedTests);

    // Test 4: Multiple Duplicates
    // [1, 1, 2, 2], Target 3 -> (1, 2)
    // Should typically return ONE (1,2) if unique value pairs are requested
    vector<int> t4 = {1, 1, 2, 2};
    runTest(++totalTests, "Duplicate inputs", t4, 3, failedTests);

    // Test 5: No Solution
    vector<int> t5 = {1, 2, 3};
    runTest(++totalTests, "No Solution", t5, 7, failedTests);

    cout << endl << "=== STRESS TESTS (Progress) ===" << endl;

    int stressCount = 2000;
    int stressFailures = 0;

    for(int i=0; i<stressCount; ++i) {
        int n = rand() % 50 + 2; // Size 2 to 52
        int target = rand() % 20 - 10; // Target -10 to 10
        vector<int> nums;
        for(int j=0; j<n; ++j) {
            nums.push_back(rand() % 20 - 10); // Vals -10 to 10 (Creates duplicates & negatives)
        }

        Solution sol;
        vector<pair<int, int>> actual = sol.findPairs(nums, target);
        vector<pair<int, int>> expected = getReferencePairs(nums, target);

        set<pair<int,int>> actS, expS;
        for(auto p : actual) actS.insert(makeCanonical(p.first, p.second));
        for(auto p : expected) expS.insert(makeCanonical(p.first, p.second));

        if (actS != expS) {
            stressFailures++;
            failedTests++;
        }

        // Simple progress bar
        if (i % 200 == 0) {
            cout << "\r[" << i << "/" << stressCount << "] Running...";
            cout.flush();
        }
    }
    cout << "\r[" << stressCount << "/" << stressCount << "] Done!       " << endl;

    // Results
    double successRate = (double)(totalTests - failedTests) / totalTests * 100.0;
    cout << endl << "==========================================" << endl;
    if (failedTests == 0) cout << "\033[32mAll Tests Passed (100%)\033[0m" << endl;
    else cout << "\033[31mFailed " << failedTests << " Tests (" << (100-successRate) << "% Fail Rate)\033[0m" << endl;
    cout << "==========================================" << endl;

    return 0;
}