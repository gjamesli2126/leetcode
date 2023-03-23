from typing import List
class Solution:
    def twoSum(self,nums,target)->List:
        SET=set()
        res=set()
        for i,num in enumerate(nums):
            compliment=target-num
            if compliment in SET:
                res.add((-target,compliment,num))
            else:
                SET.add(num)
        return res

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        ans=[]
        for ind,each in enumerate(nums):
            if ind>0 and each==nums[ind-1]:
                continue
            target=-each
            SET=self.twoSum(nums[ind+1:],target)
            # print(SET)
            if SET:
                ans+=[list(e) for e in SET]
        return ans

if __name__=="__main__":
    c=Solution()
    print(c.threeSum([-1,0,1,2,-1,-4]))#[[-1,-1,2],[-1,0,1]]
    print(c.threeSum([0,1,1]))#[]
    print(c.threeSum([0,0,0]))#000
    print(c.threeSum([1,1,-2]))#[[-2,1,1]]
    print(c.threeSum([1,2,-2,-1])) #[]
