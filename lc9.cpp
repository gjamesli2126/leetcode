#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        // TODO: Implement the palindrome check. 反正就是頭尾互砍遊戲--> not too good as leading zero might affect
        //better approach: folding
        if(x<0 || x%10==0 && x!=0) return false;
        int rev=0;//reverse
        while(x>rev){
            rev=10*rev+x%10;
            x/=10;
        }
        return rev==x || rev/10==x;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, int x, bool expected) {
//    if(testNum!=5) return;
    Solution sol;
    bool result = sol.isPalindrome(x);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isPalindrome(" << x << ") = "
             << (result ? "true" : "false") << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isPalindrome(" << x << ") = "
             << (result ? "true" : "false") << ", expected "
             << (expected ? "true" : "false") << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: x = 121
    // Output: true
    runTest(1, 121, true);

    // Example 2:
    // Input: x = -121
    // Output: false
    runTest(2, -121, false);

    // Example 3:
    // Input: x = 10
    // Output: false
    runTest(3, 10, false);

    // Additional Test Case:
    // Input: x = 0
    // Output: true
    runTest(4, 0, true);
    runTest(5,1000021, false);
    runTest(6,100020001, true);
    return 0;
}