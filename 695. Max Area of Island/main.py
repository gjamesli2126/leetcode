from typing import List
from queue import Queue
class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        xbound=len(grid[0])-1
        ybound=len(grid)-1
        maxArea=0
        q=Queue()#bfs
        for ex in range(xbound+1):
            for ey in range(ybound+1):
                if grid[ey][ex] == 0 or ey>ybound or ex>xbound:
                    continue
                q.put((ey,ex))
                area=0
                while not q.empty():
                    y,x=q.get()
                    if grid[y][x]==0:
                        continue
                    area+=1
                    grid[y][x]=0
                    for dy,dx in ((1,0),(0,1),(0,-1),(-1,0)):
                        ny,nx=y+dy,x+dx
                        if ny<0 or nx<0 or ny>ybound or nx>xbound or grid[ny][nx]==0:
                            continue
                        q.put((ny,nx))
                maxArea=max(area,maxArea)
        return maxArea



if __name__=="__main__":
    c=Solution()
    print(c.maxAreaOfIsland(grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]))#6
    print(c.maxAreaOfIsland(grid = [[0,0,0,0,0,0,0,0]]))#0
    print(c.maxAreaOfIsland([[1]]))#1
    print(c.maxAreaOfIsland([[1,1],[0,1]]))  # 3
    print(c.maxAreaOfIsland([[1, 1,1,1,0]]))  # 4
    print(c.maxAreaOfIsland([[1,1],[1,1],[1,0],[1,1]]))  #7