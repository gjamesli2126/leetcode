from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        rob1=0
        rob2=0
        """
        [rob1,rob2,n,n+1,]
        """
        for e in nums:
            currentMax=max(e+rob1,rob2)
            rob1=rob2
            rob2=currentMax
            print(currentMax,end=" ")
        return rob2

if __name__=="__main__":
    c=Solution()
    # print(c.rob(nums = [1,2,3,1]))#4
    # print(c.rob( nums = [2,7,9,3,1]))#12
    print(c.rob(nums=[1,2, 6, 9, 3, 1,18]))  # 29