#include <bits/stdc++.h>
// #define testMain main
using namespace std;

class Solution {
private:
    inline long long  count(int len,const vector<int>& ribbons){
        long long sum=0;
        for(int rib:ribbons) sum+=rib/len;
        return sum;
    }
public:
    int maxLength(vector<int>& ribbons, int k) {
        // Implement the O(n log m) binary search solution.段數lower_bound=長度的 upperbound
        int l=1,r=*max_element(ribbons.begin(),ribbons.end())+1;
        /*We maintain [l,r) as our search space, meaning l is a candidate that might work,
         * and r is the smallest length we’ve already ruled out.*/
        if(count(1,ribbons)<k) return 0;
        //l,r here mean the length
        while(l<r){
            int mid=l+(r-l)/2;
            if(count(mid,ribbons)>=k){//len too short, get upperbound of len(lowerbound of count)
                l=mid+1;
            }
            else r=mid;//if count is perfectly match to k
        }
        return l-1;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, const vector<int>& ribbons, int k, int expected) {
    Solution sol;
    int result = sol.maxLength(const_cast<vector<int>&>(ribbons), k);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: maxLength(";
        printVector(ribbons);
        cout << ", " << k << ") = " << result;
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: maxLength(";
        printVector(ribbons);
        cout << ", " << k << ") = " << result
             << ", expected " << expected;
        cout << "\033[0m" << endl;
    }
}

int testMain() {
    // Example 1:
    // ribbons = [9,7,5], k = 3 -> output = 5
    runTest(1, {9, 7, 5}, 3, 5);

    // Example 2:
    // ribbons = [7,5,9], k = 4 -> output = 4
    runTest(2, {7, 5, 9}, 4, 4);

    // Example 3:
    // ribbons = [5,7,9], k = 22 -> output = 0
    runTest(3, {5, 7, 9}, 22, 0);

    return 0;
}