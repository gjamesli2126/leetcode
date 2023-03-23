from typing import List


class Solution:
    def minCost(self, costs: List[List[int]]) -> int:
        for h,(c0,c1,c2) in enumerate(costs):
            if h==0:
                continue
            costs[h]=[
                c0+min(costs[h-1][1:]),
                c1+min(costs[h-1][0],costs[h-1][-1]),
                c2+min(costs[h-1][:-1])]
        return min(costs[-1])

if __name__=="__main__":
    c=Solution()
    print(c.minCost(costs = [[17,2,17],[16,16,5],[14,3,19]]))#10
    print(c.minCost(costs=[[17, 2, 17], [16, 16, 5], [14, 3, 19],[7,6,2],[3,8,4]]))  # 15
    print(c.minCost( costs = [[7,6,2]]))#2