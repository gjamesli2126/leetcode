#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
private:
    unordered_map<int,int> mp;
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for(int i=0;i<nums.size();i++){
            auto it=mp.find(target-nums[i]);
            if(it!=mp.end()) return {i,it->second};
            mp[nums[i]]=i;//move to the back so that it does not match to itself
        }
        return {-1,-1};
    }
};
