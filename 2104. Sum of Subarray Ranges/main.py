from operator import lt, gt
from typing import List
class Solution:
    def subArrayRangesOn2(self, nums: List[int]) -> int:
        lastIdx=len(nums)
        result=0
        for i,e in enumerate(nums):
            ma=e
            mi=e
            for j in range(i,lastIdx):
                el=nums[j]
                ma=max(ma,el)
                mi=min(mi,el)
                result+=ma-mi
        return result

    def subArrayRanges(self, nums: List[int]) -> int:

        def fn(op):
            """Return min sum (if given gt) or max sum (if given lt)."""
            ans = 0
            stack = []
            for i in range(len(nums) + 1):
                while stack and (i == len(nums) or op(nums[stack[-1]], nums[i])):# op(現有的最後一個,新assign的Target)
                    mid = stack.pop()
                    ii = stack[-1] if stack else -1
                    ans += nums[mid] * (i - mid) * (mid - ii) # (後進min-ChosenMin)*(ChosenMin-先前min)
                stack.append(i)
            return ans

        return fn(lt) - fn(gt) #sum(max)-sum(min)
if __name__=="__main__":
    c=Solution()
    # print(c.subArrayRanges([1,2,3]))#4
    print(c.subArrayRanges([1,3,3]))#4