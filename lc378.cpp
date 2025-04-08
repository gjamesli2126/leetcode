#include <bits/stdc++.h>
#define testMain main
using namespace std;
struct vrc{
    vrc(int v,int r,int c):v(v),r(r),c(c){};
    int v;
    int r;
    int c;
};
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        //using minHeap && only mem the left most, each element=(val,r,c)
        auto cmp=[&matrix](vrc vrc1,vrc vrc2){
            return vrc1.v>vrc2.v;//return true then vrc2 pop first
        };
        priority_queue<vrc,vector<vrc>,decltype(cmp)> minHeap(cmp);
        for(int r=0;r<matrix.size();r++) minHeap.push(vrc(matrix[r][0],r,0));
        while(--k){
            vrc topvrc=minHeap.top();
            minHeap.pop();
            int r=topvrc.r;
            int c=topvrc.c+1;
            if(c>=matrix[0].size()) continue;
            minHeap.push(vrc(matrix[r][c],r,c));
        }
        return minHeap.top().v;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> matrix, int k, int expected) {
    Solution sol;
    int result = sol.kthSmallest(matrix, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: kthSmallest(matrix, " << k << ") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: kthSmallest(matrix, " << k << ") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
    // Expected Output: 13
    runTest(1, {{1,5,9}, {10,11,13}, {12,13,15}}, 8, 13);

    // Test Case 2:
    // Input: matrix = [[-5]], k = 1
    // Expected Output: -5
    runTest(2, {{-5}}, 1, -5);

    return 0;
}