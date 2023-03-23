from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        results=[]


        def dfs(ind,total,subList):
            #base case
            if total>target:# or ind>=len(candidates):
                return
            elif total==target:
                results.append(subList)
                return

            #norm case
            for i in range(ind,len(candidates)):
                dfs(i,total+candidates[i],subList+[candidates[i]])
                dfs(i+1, total, subList)

        dfs(0,0,[])
        return results

if __name__=="__main__":
    c=Solution()
    print(c.combinationSum(candidates = [2,3,6,7], target = 7))#[[2,2,3],[7]]
    print(c.combinationSum(candidates = [2,3,5], target = 8))#[[2,2,2,2],[2,3,3],[3,5]]
    print(c.combinationSum(candidates = [2], target = 1))#[]
