from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        sorted(candidates)
        results=[]
        subList=[]

        def dfs(ind,total):
            if total>target or ind>=len(candidates):
                return
            elif total==target:
                results.append(subList.copy())
                return

            #add me
            subList.append(candidates[ind])
            dfs(ind,total+candidates[ind])
            #don't add me
            subList.pop()
            dfs(ind+1,total)
        dfs(0,0)
        return results

if __name__=="__main__":
    c=Solution()
    print(c.combinationSum(candidates = [2,3,6,7], target = 7))#[[2,2,3],[7]]
    print(c.combinationSum(candidates = [2,3,5], target = 8))#[[2,2,2,2],[2,3,3],[3,5]]
    print(c.combinationSum(candidates = [2], target = 1))#[]
