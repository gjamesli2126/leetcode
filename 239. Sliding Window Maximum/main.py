from typing import List
from collections import deque
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        q=deque([])
        res=[]
        for i,n in enumerate(nums):
            while q and n>=nums[q[-1]]:
                q.pop()
            q.append(i)
            if i-k >= q[0]: q.popleft()
            if i+1>=k: res.append(nums[q[0]])
        return res
if __name__=="__main__":
    c=Solution()
    print(c.maxSlidingWindow(nums = [1,3,-1,-3,5,3,6,7], k = 3))#[3,3,5,5,6,7]
    print(c.maxSlidingWindow(nums = [1], k = 1))#1
    print(c.maxSlidingWindow([1,-9],1))#[1,-9]
