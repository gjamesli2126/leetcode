#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int c=INT_MAX;
        int p=0;
        for(int price:prices){
            c=min(c,price);
            p=max(p,price-c);
        }
        return p;
    }
};

void runTest(int testNum, vector<int> prices, int expected) {
    Solution sol;
    int result = sol.maxProfit(prices);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: maxProfit(prices) = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: maxProfit(prices) = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: prices = [7,1,5,3,6,4]
    // Expected Output: 5
    runTest(1, {7,1,5,3,6,4}, 5);

    // Example 2:
    // Input: prices = [7,6,4,3,1]
    // Expected Output: 0
    runTest(2, {7,6,4,3,1}, 0);

    return 0;
}