#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    bool isOdd(const int& num){
        return num%2!=0;
    }
    int atmostK(const vector<int>& nums,const int& k){
        int fp,bp,res=0;
        int countOdd=0;
        int len=int(nums.size());
        for(fp=0,bp=0;bp<len;bp++){
            if(isOdd(nums[bp])) ++countOdd;
            while(countOdd>k){
                if(isOdd(nums[fp])) --countOdd;
                ++fp;
            }
            res+=bp-fp+1;
        }
        return res;
    }
public:
    int numberOfSubarrays_okversion(vector<int>& nums, int k) {
        return atmostK(nums,k)- atmostK(nums,k-1);
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        int res=0,fp=0,bp,count=0,len=int(nums.size()),countOdd=0;
        for(bp=0;bp<len;++bp){
            if(isOdd(nums[bp])){
                ++countOdd;
                count=0;
            }
            while(countOdd==k){
                if(isOdd(nums[fp])) --countOdd;
                ++fp;
                ++count;
            }
            res+=count;
        }
        return res;
    }

};

int mainTest() {
    Solution solution; // Create an instance of the Solution class

    // Test Case 1
    vector<int> nums1 = {1, 1, 2, 1, 1};
    int k1 = 3;
    cout << "Test Case 1 - Expected: 2, Actual: " << solution.numberOfSubarrays(nums1, k1) << endl;

    // Test Case 2
    vector<int> nums2 = {2, 4, 6};
    int k2 = 1;
    cout << "Test Case 2 - Expected: 0, Actual: " << solution.numberOfSubarrays(nums2, k2) << endl;

    // Test Case 3
    vector<int> nums3 = {2, 2, 2, 1, 2, 2, 1, 2, 2, 2};
    int k3 = 2;
    cout << "Test Case 3 - Expected: 16, Actual: " << solution.numberOfSubarrays(nums3, k3) << endl;

    return 0;
}
