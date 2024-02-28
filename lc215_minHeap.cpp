#include <bits/stdc++.h>
using namespace std;

#define mainTest main

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //using minHeap worse: O(nlogk)
        priority_queue<int,vector<int>,greater<int>> minHeap;
        for(const int n:nums){
            minHeap.push(n);
            if(minHeap.size()>k) minHeap.pop();
        }
        return minHeap.top();
    }
};

void printResult(int expected, int output) {
    cout << "Expected: " << expected << ", Output: " << output << endl;
    if (expected == output) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }
}

int mainTest() {
    Solution solution1;
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    int expected1 = 5;
    int output1 = solution1.findKthLargest(nums1, k1);
    printResult(expected1, output1);

    Solution solution2;
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    int expected2 = 4;
    int output2 = solution2.findKthLargest(nums2, k2);
    printResult(expected2, output2);

    return 0;
}
