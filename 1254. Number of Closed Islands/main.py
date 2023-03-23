from typing import List
from queue import Queue
class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        ybound=len(grid)-1
        xbound=len(grid[0])-1
        q=Queue()#bfs
        countIsland=0
        for ey in range(1 + ybound):
            for ex in range(xbound+1):
                if ex>xbound or ey>ybound or grid[ey][ex]==1:
                    continue
                touchBound=False
                q.put((ey,ex))
                while not q.empty():# and not touchBound:
                    y,x=q.get()
                    if grid[y][x]==1:
                        continue
                    grid[y][x]=1
                    for dx,dy in ((1,0),(0,1),(-1,0),(0,-1)):
                        nx,ny=x+dx,y+dy
                        if nx>xbound or ny>ybound or nx<0 or ny<0:
                            touchBound=True
                            continue# still need to mod all of them
                        elif grid[ny][nx]==1:
                            continue
                        q.put((ny,nx))
                countIsland+=(not touchBound)
        return countIsland



if __name__ == '__main__':
    c=Solution()
    print(c.closedIsland(grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]))#2
    print(c.closedIsland(grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]))#1
    print(c.closedIsland( grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]))#2



