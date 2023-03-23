from typing import List
class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        ans=[nums[0]]
        for i,e in enumerate(nums[1:]):
            ans.append(e + ans[i])

        return ans
if __name__=="__main__":
    c=Solution()
    print(c.runningSum([1,2,3,4]))
