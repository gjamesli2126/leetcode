#include <iostream>
#include <vector>
#include <climits> // For INT_MAX and INT_MIN
using namespace std;
#define mainTest main

class Solution {
public:
    int reverse(int x) {
        int result=0;
        while(x){
            int lsDigit=x%10;
            x/=10;
            if(result>INT_MAX/10 || result==INT_MAX/10 && lsDigit>INT_MAX%10) return 0;
            else if(result<INT_MIN/10 || result==INT_MIN/10 && lsDigit<INT_MIN%10) return 0;//INT_MIN%10=-8
            result*=10;
            result+=lsDigit;
        }
        return result;
    }
};

void printTestResult(int testNum, int expected, int actual) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32mPassed\033[0m\n"; // Green for passed
    } else {
        cout << "\033[31mFailed. Expected: " << expected << ", Actual: " << actual << "\033[0m\n"; // Red for failed
    }
}

int mainTest() {
    vector<pair<int, int>> testCases = {
            {123, 321},
            {-123, -321},
            {120, 21},
            {0, 0},
            // These cases might overflow, expected result is 0
            {INT_MAX, 0},
            {INT_MIN, 0}
    };
    int testNum = 0;

    for (auto& testCase : testCases) {
        Solution solution; // New object for each test case
        int actual = solution.reverse(testCase.first);
        printTestResult(++testNum, testCase.second, actual);
    }

    return 0;
}