from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        currentSum=nums[0]
        suggestedSum=0
        for each in nums:
            if suggestedSum<0:
                suggestedSum=0
            suggestedSum+=each
            currentSum=max(currentSum,suggestedSum)
        return currentSum

if __name__=="__main__":
    c=Solution()
    print(c.maxSubArray(nums = [-2,1,-3,4,-1,2,1,-5,4]))#6
    print(c.maxSubArray( nums = [1]))#1
    print(c.maxSubArray( nums = [5,4,-1,7,8]))#23
    print(c.maxSubArray(nums=[-1]))  # -1
    print(c.maxSubArray(nums=[-92,-12,-2,-56,-999]))  # -1