from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        subset=[]
        結果=[]
        def dfs(ind):

            if ind>=len(nums):
                結果.append(subset.copy())
                return

            # 要加
            subset.append(nums[ind])
            dfs(ind+1)
            # 不要加
            subset.pop()
            dfs(ind + 1)

        dfs(0)
        return 結果

if __name__=="__main__":
    c=Solution()
    print(c.subsets(nums = [1,2,3]))#[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
    # print(c.subsets(nums = [0]))#[[],[0]]