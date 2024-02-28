#include <bits/stdc++.h>
using namespace std;

#define mainTest main


class Solution {
private:
    int quickSelect(vector<int>& nums,int k){
        int pivot=nums[rand()%nums.size()];
        vector<int> smaller,mid,larger;
        for(const int n:nums){
            if(n>pivot) larger.push_back(n);
            else if(n<pivot) smaller.push_back(n);
            else mid.push_back(n);
        }
        if(k<=larger.size()) return quickSelect(larger,k);
        if(larger.size()+mid.size()<k) return quickSelect(smaller,k-larger.size()-mid.size());
        return pivot;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        //using quick select, avg O(n), worse O(n^2)
        return quickSelect(nums,k);
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
