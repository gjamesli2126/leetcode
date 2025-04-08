#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        /*此step有多少方法是要從 n-1 & n-2加來的，所以就是廢渣數列*/
        if(n<=3) return n;
        //start from n=4
        n-=3;
        int cur;
        for(int pp=2,p=3;n>0;n--){
            cur=pp+p;
            pp=p;
            p=cur;
        }

        return cur;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, int n, int expected) {
    Solution sol;
    int result = sol.climbStairs(n);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: climbStairs(" << n << ") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: climbStairs(" << n << ") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: n = 2, Expected Output: 2
    runTest(1, 2, 2);

    // Test Case 2:
    // Input: n = 3, Expected Output: 3
    runTest(2, 3, 3);

    // Additional Test Case:
    // Input: n = 4, Expected Output: 5
    runTest(3, 4, 5);

    return 0;
}