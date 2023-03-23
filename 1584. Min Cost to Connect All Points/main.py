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
            for j in range(i+1,N):
                x2,y2=points[j]
                dist=abs(x1-x2)+abs(y1-y2)
                adj[i].append([dist,j])
                adj[j].append([dist,i])
        #prim's alg
        totalCost=0
        visited=set()
        minHeap=[[0,0]]# cost, point
        while len(visited)<N:
            print(minHeap)
            cost,point=heapq.heappop(minHeap)
            if point in visited:
                continue
            totalCost+=cost
            visited.add(point)
            for neighberCost,neighberPoint in adj[point]:
                if neighberPoint in visited:
                    continue
                heapq.heappush(minHeap,[neighberCost,neighberPoint])
        return totalCost


if __name__=="__main__":
    c=Solution()
    print(c.minCostConnectPoints(points = [[0,0],[2,2],[3,10],[5,2],[7,0]]))#20
    print(c.minCostConnectPoints(points = [[3,12],[-2,5],[-4,1]]))#18
