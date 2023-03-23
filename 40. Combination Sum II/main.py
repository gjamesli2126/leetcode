from typing import List

class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        result=[]

        partialREsult=[]
        candidates.sort()
        def backtrack(ind, total=0):
            #base case
            if total==target:
                result.append(partialREsult[:])
                return
            elif ind>=len(candidates) or total>target:
                return
            #norm case
            me=candidates[ind]
            #add me
            partialREsult.append(me)
            total+=me
            backtrack(ind+1,total)

            partialREsult.pop()#O(1)
            total-=me
            #not add me
            while ind<len(candidates)-1 and me==candidates[ind+1]:
                ind+=1
            backtrack(ind+1,total)
        backtrack(0)
        return result
if __name__=="__main__":
    c=Solution()
    print(c.combinationSum2(candidates = [10,1,2,7,6,1,5], target = 8))#[[1,1,6],[1,2,5],[1,7],[2,6]]

    print(c.combinationSum2(candidates = [2,5,2,1,2], target = 5))#[[1,2,2],[5]]
