from typing import List
import bisect
from collections import deque
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        if len(nums)==1:
            return len(nums)
        stack=[nums[0]]
        for n in nums[1:]:
            if n>stack[-1]:
                stack.append(n)
                continue
            i=bisect.bisect_left(stack,n)
            stack[i]=n

        # print(stack)
        return len(stack)
if __name__=="__main__":
    c=Solution()
    print(c.lengthOfLIS(nums = [10,9,2,5,3,7,101,18]))#4
    print(c.lengthOfLIS(nums = [0,1,0,3,2,3]))#4
    print(c.lengthOfLIS(nums = [7,7,7,7,7,7,7]))#1
