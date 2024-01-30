#include<bits/stdc++.h>
#define mainTest main
using namespace std;
class Solution {
public:
    int hammingWeight(uint32_t n) {
        return __builtin_popcount(n);
    }
};
/*
    int hammingWeight(uint32_t n) const noexcept {
        return std::bitset<32>(n).count();
    }
*/

int mainTest() {
    // Test 1
    {
        Solution sol;
        uint32_t n1 = bitset<32>("00000000000000000000000000001011").to_ulong();
        int expected1 = 3;
        int actual1 = sol.hammingWeight(n1);
        cout << "Test 1: " << (expected1 == actual1 ? "Passed" : "Failed") << endl;
        cout << "Expected: " << expected1 << ", Actual: " << actual1 << endl;
    }

    // Test 2
    {
        Solution sol;
        uint32_t n2 = bitset<32>("00000000000000000000000010000000").to_ulong();
        int expected2 = 1;
        int actual2 = sol.hammingWeight(n2);
        cout << "Test 2: " << (expected2 == actual2 ? "Passed" : "Failed") << endl;
        cout << "Expected: " << expected2 << ", Actual: " << actual2 << endl;
    }

    // Test 3
    {
        Solution sol;
        uint32_t n3 = bitset<32>("11111111111111111111111111111101").to_ulong();
        int expected3 = 31;
        int actual3 = sol.hammingWeight(n3);
        cout << "Test 3: " << (expected3 == actual3 ? "Passed" : "Failed") << endl;
        cout << "Expected: " << expected3 << ", Actual: " << actual3 << endl;
    }

    // Add more test cases here

    return 0;
}
