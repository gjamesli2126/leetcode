#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    vector<int> nums;
    vector<int> numsBak;
    static default_random_engine engine;
public:
    Solution(vector<int>& nums) {
        this->nums=nums;
        this->numsBak=nums;
    }
    
    vector<int> reset() {
        nums=numsBak;
        return nums;
    }
    
    vector<int> shuffle() {
        std::shuffle(nums.begin(),nums.end(),engine);
        return nums;
    }
};
unsigned int seed=chrono::system_clock::now().time_since_epoch().count();
default_random_engine Solution::engine(seed);

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */