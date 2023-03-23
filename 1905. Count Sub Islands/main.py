from typing import List
from queue import Queue# sync ---> slow
class Solution:
    def countSubIslands(self, grid1: List[List[int]], grid2: List[List[int]]) -> int:
        ybound=len(grid2)-1
        xbound=len(grid2[0])-1
        q=Queue()
        islandCount=0
        for ex in range(xbound+1):
            for ey in range(ybound+1):
                if ex>xbound or ey>ybound or grid2[ey][ex]==0:
                    continue
                q.put((ey,ex))
                allCover=True
                while not q.empty():
                    y,x=q.get()
                    if grid2[y][x]==0:
                        continue
                    elif grid1[y][x]==0:
                        allCover=False
                    grid2[y][x]=0
                    for dx,dy in ((1,0),(0,1),(-1,0),(0,-1)):
                        nx,ny=x+dx,y+dy
                        if nx<0 or ny<0 or nx>xbound or ny>ybound or grid2[ny][nx]==0:
                            continue
                        q.put((ny,nx))
                islandCount+=allCover
        return islandCount
if __name__=="__main__":
    c=Solution()
    print(c.countSubIslands(grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]))#3
    print(c.countSubIslands(grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]], grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]))#2
