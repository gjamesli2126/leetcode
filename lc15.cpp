class Solution {
private:
    int N;
    vector<vector<int>> ans;
public:
    void twoSum(const vector<int>&nums,int target,int startInd){
        vector<int> res;
        int lp=startInd,rp=N-1;
        // for(int i=startInd;i<N && lp<rp;i++){
        while (lp < rp) {
            int s=nums[lp]+nums[rp];
            const int curr_rp = nums.at(rp), curr_lp = nums.at(lp);// so not out of bound
            if(s>target) while(lp < rp && nums[rp]==curr_rp) rp--;//too large
            else if(s<target) while(lp < rp && nums[lp]==curr_lp) lp++;//too small
            else {
                ans.push_back({-target,nums[lp],nums[rp]});
                while(lp < rp && nums[rp]==curr_rp) rp--;//too large
                while(lp < rp && nums[lp]==curr_lp) lp++;//too small
            }
        }
        
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        N=nums.size();
        
        int first=-100001;
        for(int i=0;i<N;i++) {
            if(first==nums[i]) continue;
            first=nums[i];
            twoSum(nums,-nums[i],i+1);
            
        }
        return ans;
    }
};

/*

{-3, -2, -1, 0, 4, 5}
 p1
 two sum {-2, -1, 0, 4, 5}
        {-2, 5}, {-1, 4}

*/