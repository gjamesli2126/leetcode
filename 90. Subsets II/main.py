from typing import List


class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        result=[]
        nums.sort()
        def backtrack(ind,partialSet):
            #base case
            if len(nums)<=ind:
                result.append(partialSet[:])
                return
            #norm case
            me=nums[ind]
            #all of the subsets include me
            partialSet.append(me)
            backtrack(ind+1,partialSet)

            partialSet.pop()
            #all of the subsets NOT include me
            while ind<len(nums)-1 and me==nums[ind+1]:
                ind+=1
            backtrack(ind+1,partialSet)
        backtrack(0,[])
        return result

if __name__=="__main__":
    c=Solution()
    print(c.subsetsWithDup(nums = [1,2,2]))# [[],[1],[1,2],[1,2,2],[2],[2,2]]
    print(c.subsetsWithDup(nums=[1, 2, 2,3]))  #1223,122,123,12,13,1,22,223,22,23,2,3,[]
    print(c.subsetsWithDup(nums = [0]))#[[],[0]]