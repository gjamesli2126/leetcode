from typing import List
from queue import Queue
class Solution:
    def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
        ybound=len(image)-1
        xbound=len(image[0])-1
        q=Queue()
        q.put([sr,sc])
        centerColor=image[sr][sc]
        if centerColor==color:
            return image
        while not q.empty():
            center=q.get()#center
            y, x=center
            image[y][x]=color
            #4 directions
            for dy,dx in ([0,1],[1,0],[-1,0],[0,-1]):
                # occupied=[y+dy,x+dx]
                occy,occx=y+dy,x+dx
                if occy<0 or occy>ybound or occx<0 or occx>xbound:
                    continue
                elif image[occy][occx]!=centerColor:
                    continue
                q.put([occy,occx])
        return image


if __name__=="__main__":
    c=Solution()
    print(c.floodFill(image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2))#[[2,2,2],[2,2,0],[2,0,1]]
    print(c.floodFill(image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0))#[[0,0,0],[0,0,0]]
    print(c.floodFill(image=[[0, 0, 0], [0, 0, 0]], sr=0, sc=0, color=1))  # [[1,1,1],[1,1,1]]
