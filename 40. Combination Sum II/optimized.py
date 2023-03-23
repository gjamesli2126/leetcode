from typing import List
class Solution:
    def combinationSum2(self, candidates, target):
        ret = []
        candidates.sort()

        def backtrack(total, ind, partialREsult):
            #base Case
            if total == target:
                ret.append(partialREsult)
                return
            elif total >target:
                return

            #norm case
            for i in range(ind, len(candidates)):
                if i > ind and candidates[i] == candidates[i - 1]:
                    continue
                backtrack(total + candidates[i], i + 1, partialREsult + [candidates[i]])

        backtrack(0,0,[])
        return ret



if __name__=="__main__":
    c=Solution()
    print(c.combinationSum2(candidates = [10,1,2,7,6,1,5], target = 8))#[[1,1,6],[1,2,5],[1,7],[2,6]]

    print(c.combinationSum2(candidates = [2,5,2,1,2], target = 5))#[[1,2,2],[5]]
