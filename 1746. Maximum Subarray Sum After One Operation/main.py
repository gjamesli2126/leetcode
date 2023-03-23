from typing import List


class Solution:
    def maxSumAfterOperation(self, nums: List[int]) -> int:
        sqred=nums[0]**2
        notSqred=nums[0]
        result=max(sqred,notSqred)
        for num in nums[1:]:
            oldSqred=sqred
            oldNotSqred=notSqred
            notSqred=max(num,num+oldNotSqred)
            sqred=max(oldSqred+num,oldNotSqred+num**2,num**2)
            result=max(result,sqred)
        return result

if __name__=="__main__":
    c=Solution()
    print(c.maxSumAfterOperation(nums = [2,-1,-4,-3]))#17
    print(c.maxSumAfterOperation(nums = [1,-1,1,1,-1,-1,1]))#4