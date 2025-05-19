#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
private:
    unordered_map<int,int> compliment_ind;
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        for(int i=0;i<nums.size();i++){
            auto it=compliment_ind.find(target-nums[i]);
            if(it!=compliment_ind.end()) return {i,it->second};
            compliment_ind[nums[i]]=i;//seen!
        }
        return {};
    }
};
