from typing import List
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        validRange=(1,len(nums)) # 1~len(nums)
        #invalid: out of range
        ptr=0
        while ptr<len(nums):
            n1=nums[ptr]
            # print(n1)
            if n1 >=validRange[0] and n1<=validRange[1] and n1!=nums[n1-1]:
                nums[n1-1],nums[ptr]=n1,nums[n1-1]
            else:
                ptr+=1
        for i,n in enumerate(nums):
            if i+1!=n:
                return i+1
        return len(nums)+1

if __name__=="__main__":
    c=Solution()
    print(c.firstMissingPositive([1,2,0]))#3
    print(c.firstMissingPositive([3,4,-1,1]))#2
    print(c.firstMissingPositive([7,8,9,11,12]))#1
