class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n=nums.size();
        
        unordered_map<int,int> dict;
        for(int i=0;i<n;i++){
            int oth=target-nums[i];
            if(dict.find(oth)!=dict.end()){
                return {i,dict[oth]};
            }
            else{
                dict[nums[i]]=i;
            }
        }
        return {};
    }
};