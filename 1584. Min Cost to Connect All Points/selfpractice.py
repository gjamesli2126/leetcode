import heapq
from typing import List
from pprint import pprint as pp
class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        #build adj list
        N=len(points)
        adj={i:[] for i in range(N)}
        for i in range(N):
            x1,y1=points[i]
            for j in range(1+i,N):
                x2,y2=points[j]
                dist=abs(x1-x2)+abs(y1-y2)
                adj[i].append([dist,j])
                adj[j].append([dist, i])

        #prim's alg
        visited=set()
        minHeap=[[0,0]]# [cost,neighbor]
        totalCost=0
        while len(visited)<N:
            cost,point=heapq.heappop(minHeap)
            if point in visited:
                continue
            totalCost+=cost
            visited.add(point)
            for neighberCost,neighborPoint in adj[point]:
                if neighborPoint in visited:
                    continue
                heapq.heappush(minHeap,[neighberCost,neighborPoint])
        return totalCost
if __name__=="__main__":
    c=Solution()
    print(c.minCostConnectPoints(points = [[0,0],[2,2],[3,10],[5,2],[7,0]]))#20
    print(c.minCostConnectPoints(points = [[3,12],[-2,5],[-4,1]]))#18
