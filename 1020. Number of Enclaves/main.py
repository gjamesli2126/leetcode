from typing import List
from queue import Queue
class Solution:
    def numEnclaves(self, grid: List[List[int]]) -> int:
        ybound=len(grid)-1
        xbound=len(grid[0])-1
        q=Queue()
        blockNum=0
        for ex in range(1+xbound):
            for ey in range(1+ybound):
                if ex>xbound or ey>ybound or grid[ey][ex]==0:
                    continue
                q.put((ey,ex))
                touchBound=False
                area=0
                while not q.empty():
                    y,x=q.get()
                    if grid[y][x]==0:
                        continue
                    grid[y][x]=0
                    area+=1
                    for dx,dy in ((0,1),(1,0),(0,-1),(-1,0)):
                        nx,ny=x+dx,y+dy
                        if nx<0 or ny<0 or ny>ybound or nx>xbound:
                            touchBound=True
                            continue
                        elif grid[ny][nx]==0:
                            continue
                        q.put((ny,nx))
                blockNum+=area*(not touchBound)

        return blockNum

if __name__=="__main__":
    c=Solution()
    print(c.numEnclaves(grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]))#3
    print(c.numEnclaves(grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]))#0
    print(c.numEnclaves([[0,0,0,1,1,1,0,1,0,0],
                         [1,1,0,0,0,1,0,1,1,1],
                         [0,0,0,1,1,1,0,1,0,0],
                         [0,1,1,0,0,0,1,0,1,0],
                         [0,1,1,1,1,1,0,0,1,0],
                         [0,0,1,0,1,1,1,1,0,1],
                         [0,1,1,0,0,0,1,1,1,1],
                         [0,0,1,0,0,1,0,1,0,1],
                         [1,0,1,0,1,1,0,0,0,0],
                         [0,0,0,0,1,1,0,0,0,1]]))#3