#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        //left<-----right by one-pass
        int max_num_id=-1;
        int sw_src_i=-1;
        int sw_tar_i=-1;
        string snum=to_string(num);
        for(int i=snum.size()-1;i>=0;--i){

            if(max_num_id==-1 || snum[i]>snum[max_num_id]) max_num_id=i;
            else if(snum[i]<snum[max_num_id]) {
                sw_src_i=max_num_id;
                sw_tar_i=i;
            }
        }
        //swap sw_src_i & sw_tar_i
        if(sw_src_i!=-1 && sw_tar_i!=-1) swap(snum[sw_src_i],snum[sw_tar_i]);
        return stoi(snum);
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