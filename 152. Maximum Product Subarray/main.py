import sys
from typing import List


class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        localMin=nums[0]
        globalMin=nums[0]
        localMax=nums[0]
        globalMax=nums[0]
        for num in nums[1:]:
            # if num==0:
            #     localMin=1
            #     localMax=1
            # else:
            oldlocalMin=localMin
            oldlocalMax=localMax
            localMin=min(num,oldlocalMin*num,oldlocalMax*num)
            localMax=max(num,oldlocalMax*num,oldlocalMin*num)
            globalMax=max(globalMax,localMax)
            globalMin=min(globalMin,localMin)

        return globalMax
if __name__=="__main__":
    c=Solution()
    print(c.maxProduct(nums = [2,3,-2,4]))#6
    print(c.maxProduct(nums = [-2,0,-1]))#0
    print(c.maxProduct(nums=[89,0, 2, 1]))  # 89
