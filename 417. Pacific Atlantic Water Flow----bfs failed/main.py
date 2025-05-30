from typing import List
from collections import deque
from queue import Queue
class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        ybound=len(heights)-1
        xbound=len(heights[0])-1
        q=deque()
        # q=Queue()
        ans=[]
        visited = set()
        for ey in range(ybound+1):
            for ex in range(xbound+1):
                pacificTouch=False
                atlanticTouch=False
                q.append((ey,ex))
                # q.put((ey,ex))
                while q:
                    y,x=q.popleft()
                    # y,x=q.get()
                    visited.add((y,x))
                    for dx,dy in ((0,1),(1,0),(0,-1),(-1,0)):
                        nx,ny=x+dx,y+dy
                        pacificTouch|=nx<0 or ny<0
                        atlanticTouch|=nx>xbound or ny>ybound
                        if nx<0 or ny<0 or nx>xbound or ny>ybound or (ny,nx) in visited:
                            continue
                        elif heights[ny][nx]<=heights[y][x]:
                            q.append((ny, nx))
                            # q.put((ny,nx))
                    if pacificTouch and atlanticTouch:
                        ans.append([ey,ex])
                        break
        return ans


if __name__=="__main__":
    c=Solution()
    print(c.pacificAtlantic(heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]))
    # Output: [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
    # print(c.pacificAtlantic(heights = [[2,1],[1,2]]))
    # Output: [[0, 0], [0, 1], [1, 0], [1, 1]]