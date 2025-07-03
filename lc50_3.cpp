#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {

public:
    double myPow(double x, long n0) {//提醒: n=(-2^31)~(2^31-1)，因此若是強制轉正 會遇到 int overflow
        if(x==0) return 0;
        else if(n0==0) return 1;
        double ans=1;
        bool x_minus=x<0;
        bool n_minus=n0<0;
        x=abs(x);
        long n=abs(n0);
        //assuming x>0 && n>0
        while(n>1){
            //odd or even
            if(n%2){
                ans*=x;
                n--;
            }
            //must be even
            x*=x;
            n/=2;
        }
        //one more as n=1;
        ans*=x;
        if(n_minus) ans=1/ans;
//        cout<<x_minus<<n0%2<<endl;
        if(x_minus && n0%2) ans=-ans;
        return ans;
    }
};

// Helper function to compare doubles with a tolerance.
bool areEqual(double a, double b, double tol = 1e-4) {
    return fabs(a - b) < tol;
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, double x, int n, double expected) {
    Solution sol;
    double result = sol.myPow(x, n);
    if (areEqual(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: myPow(" << x << ", " << n
             << ") = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: myPow(" << x << ", " << n
             << ") = " << result << ", expected " << expected << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: x = 2.00000, n = 10
    // Expected Output: 1024.00000
    runTest(1, 2.0, 10, 1024.0);

    // Example 2:
    // Input: x = 2.10000, n = 3
    // Expected Output: 9.26100
    runTest(2, 2.1, 3, 9.261);

    // Example 3:
    // Input: x = 2.00000, n = -2
    // Expected Output: 0.25000
    runTest(3, 2.0, -2, 0.25);

    // Additional Test Cases with large n:
    // Test Case 4: x = 1.0, n = INT_MAX (largest exponent)
    // Any number raised to any power when the number is 1 should be 1.
    runTest(4, 1.0, 2147483647, 1.0);

    // Test Case 5: x = 0.9999, n = 1000000.
    // Expected output computed using the standard library pow function.
    runTest(5, 0.9999, 1000000, pow(0.9999, 1000000));

    // Test Case 6: x = 1.000001, n = -1000000.
    // Expected output computed using the standard library pow function.
    runTest(6, 1.000001, -1000000, pow(1.000001, -1000000));

    runTest(7,-13.62608,3,-2529.95504);

    runTest(8,-2,2,4);
    runTest(9,1,-2147483648,1);

    return 0;
}