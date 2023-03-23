from typing import List


class Solution:

    def permute(self, nums: List[int]) -> List[List[int]]:
        result=[]
        #base case
        if len(nums)==1:
            return [nums[:]]
        #norm case
        for i in range(len(nums)):
            n=nums.pop(0)
            permutations=self.permute(nums)
            for p in permutations:
                p.append(n)
            result.extend(permutations)
            nums.append(n)
        return result
if __name__=="__main__":
    c=Solution()
    print(c.permute(nums = [1,2,3]))# [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    print(c.permute(nums = [0,1]))# [[0,1],[1,0]]
    print(c.permute(nums = [1]))#[[1]]