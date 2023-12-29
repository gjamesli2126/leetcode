#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    int atmostK(const vector<int>& nums,const int& k){
        int len=int(nums.size());
        int pf=0,pb,res=0;//~-k,-1
        unordered_map<int,int> count;
        for(pb=0;pb<len;++pb){
            ++count[nums[pb]];
            while(count.size()>k){//means pb pulling pf, pf++
                --count[nums[pf]];
                if(!count[nums[pf]]) count.erase(nums[pf]);
                ++pf;
            }
            res+=pb-pf+1;
        }
        return res;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atmostK(nums,k)- atmostK(nums,k-1);
    }
};
//int main() {
//    Solution solution; // Create an instance of the Solution class
//
//    // Test Case 1
//    vector<int> nums1 = {1, 2, 1, 2, 3}; // Input array
//    int k1 = 2; // Number of distinct integers
//    cout << "Test Case 1 - Number of subarrays with exactly " << k1 << " distinct integers: "
//         << solution.subarraysWithKDistinct(nums1, k1) << endl;
//}