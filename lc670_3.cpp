#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        //from the back
        string ns= to_string(num);
        int nsl=ns.length();
        int max_num_i=-1;
        int sw_src_i=-1;
        int sw_tar_i=-1;
        for(int i=nsl-1;i>=0;i--){
            if(max_num_i==-1 || ns[i]>ns[max_num_i]) max_num_i=i;
            else if(ns[i]<ns[max_num_i]){
                sw_src_i=max_num_i;
                sw_tar_i=i;
            }
        }
        if(sw_src_i!=-1 && sw_tar_i!=-1) swap(ns[sw_src_i],ns[sw_tar_i]);
        return stoi(ns);
    }
};
void runTest(int testNum, int num, int expected) {
    Solution sol;
    int result = sol.maximumSwap(num);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: maximumSwap(" << num << ") = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: maximumSwap(" << num << ") = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: num = 2736
    // Expected Output: 7236
    runTest(1, 2736, 7236);

    // Test Case 2:
    // Input: num = 9973
    // Expected Output: 9973
    runTest(2, 9973, 9973);

    return 0;
}