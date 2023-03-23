from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        downIndex=0
        upIndex=len(nums)-1
        while downIndex<=upIndex:
            midIndex=(downIndex+upIndex)//2
            midVal=nums[midIndex]
            if midVal==target:
                return midIndex
            elif target>midVal:
                downIndex=midIndex+1
            else:
                upIndex=midIndex-1
        return -1


if __name__=="__main__":
    c=Solution()
    print(c.search(nums = [-1,0,3,5,9,12], target = 9))