from typing import List
class Solution:
    def rob1(self, nums: List[int]) -> int:
        rob1=0
        rob2=0
        for e in nums:
            currentMax=max(e+rob1,rob2)
            rob1=rob2
            rob2=currentMax
        return rob2
    def rob(self, nums: List[int]) -> int:
        if len(nums)==1:
            return nums[0]
        return max(self.rob1(nums[1:]),self.rob1(nums[:-1]))
if __name__=="__main__":
    c=Solution()
    print(c.rob([2,3,2]))#3
    print(c.rob(nums = [1,2,3,1]))#4
    print(c.rob([3,1,2,6,9,3,1,18]))#29
    print(c.rob([1]))#1