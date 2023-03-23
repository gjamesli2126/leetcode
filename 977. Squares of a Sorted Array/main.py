from typing import List
from collections import deque
class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        #close to 0 wil be the min
        ans=deque()
        lptr=0
        rptr=len(nums)-1
        while lptr<=rptr:
            sqrL=nums[lptr]**2
            sqrR=nums[rptr]**2
            if sqrL>sqrR:
                ans.appendleft(sqrL)
                lptr+=1
            else:
                ans.appendleft(sqrR)
                rptr -= 1

        return list(ans)


if __name__=="__main__":
    c=Solution()
    print(c.sortedSquares(nums = [-4,-1,0,3,10]))