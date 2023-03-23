from typing import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        if len(nums)==0 or sum(nums)%2!=0:
            return False
        dp={0}
        for n in nums:
            nextDP=dp.copy()
            for t in dp:
                nextDP.add(t+n)
            dp=nextDP

        return sum(nums)//2 in dp
if __name__=="__main__":
    c=Solution()
    print(c.canPartition( nums = [1,5,11,5]))#True
    print(c.canPartition(nums = [1,2,3,5]))#F