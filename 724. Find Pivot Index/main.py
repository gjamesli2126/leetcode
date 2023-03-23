from typing import List


class Solution:
    def pivotIndex(self, nums: List[int]) -> int:
        leftSum=0
        rightSum=sum(nums[1:])
        prevE=nums[0]
        for pivotIndex,e in enumerate(nums):
            if pivotIndex>0:
                leftSum+=prevE
                rightSum-=e
            if leftSum==rightSum:
                return pivotIndex
            prevE=e


        return -1
if __name__=="__main__":
    c=Solution()
    print(c.pivotIndex([1,7,3,6,5,6]))#3