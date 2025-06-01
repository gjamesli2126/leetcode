#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        //using a new var
        uint32_t rev=0;
        for(int i=0;i<32;i++){
            rev<<=1;
            rev|=n&1;
            n>>=1;//就不用一直移
        }
        return rev;
    }
};

int mainTest() {
    Solution solution;

    // Define test cases and expected results
    vector<pair<uint32_t, uint32_t>> testCases = {
            {43261596, 964176192},   // Expected reversed value for 43261596
            {4294967293, 3221225471} // Expected reversed value for 4294967293
    };

    // Iterate through test cases
    for (auto& test : testCases) {
        uint32_t result = solution.reverseBits(test.first);
        bool isPass = result == test.second;

        cout << "Test with input: " << test.first << " - ";
        if (isPass) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m. Expected: " << test.second << ", Got: " << result << endl;
        }
    }

    return 0;
}
