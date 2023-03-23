from typing import List


class Solution:
    def minCostII(self, costs: List[List[int]]) -> int:
        def validMin(lst, ind):
            validList = [e for i, e in enumerate(lst) if i != ind]
            return min(validList)
        for h,cs in enumerate(costs):
            if h==0:
                continue
            for ind,c in enumerate(cs):
                costs[h][ind]=c+validMin(costs[h-1],ind)

        return min(costs[-1])
if __name__=="__main__":
    c=Solution()
    print(c.minCostII(costs = [[1,5,3],[2,9,4]]))#5
    print(c.minCostII(costs = [[1,3],[2,4]]))#5