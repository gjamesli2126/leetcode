from typing import List
from collections import deque
class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        ybound=len(grid)-1
        xbound = len(grid[0]) - 1
        q=deque()#Queue, BFS
        currentMax=0
        for ey in range(ybound+1):
            for ex in range(xbound+1):
                if grid[ey][ex]!=1:
                    continue
                q.append((ey,ex))
        while q:
            y,x=q.popleft()
            # if grid[y][x]<currentMax:
            #     continue
            for dx,dy in ((0,1),(1,0),(-1,0),(0,-1)):
                nx,ny=x+dx,y+dy


                if nx>xbound or nx<0 or ny>ybound or ny<0 or grid[ny][nx]>=1:
                    continue
                q.append((ny,nx))
                expand=grid[y][x]+1
                grid[ny][nx]=expand
                currentMax=max(currentMax,expand)
        return currentMax-1

if __name__=="__main__":
    c=Solution()
    print(c.maxDistance(grid = [[1,0,1],[0,0,0],[1,0,1]]))#2
    print(c.maxDistance(grid = [[1,0,0],[0,0,0],[0,0,0]]))#4
    print(c.maxDistance(grid=[[0, 0, 0], [0, 0, 0], [0, 0, 0]]))  # -1
    print(c.maxDistance([[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1]]))#-1
