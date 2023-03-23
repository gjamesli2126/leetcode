from pprint import pprint as pp
from typing import List
def _print(mat):
    for each in mat:
        print(each)
    print()

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        #  touch wall then turn right; if visited: make num to 1000
        x,y=0,0
        yMax=len(matrix)
        xMax=len(matrix[0])
        result=[]
        vec=[(0,1),(1,0),(0,-1),(-1,0)]#y,x
        switch=0
        result.append(matrix[y][x])
        matrix[y][x] = 999
        dy, dx = vec[switch]
        for _ in range(xMax*yMax-1):
            # _print(matrix)
            nxtx,nxty=x+dx,y+dy
            if nxty>=yMax or nxtx>=xMax or nxtx<0 or nxty<0 or matrix[nxty][nxtx]==999:
                switch+=1
                switch%=4
                dy, dx = vec[switch]
                y += dy
                x += dx
            else:
                x,y=nxtx,nxty
            # else:
            #     nxt=matrix[nxty][nxtx]
            #     if nxt==999:
            #         switch += 1
            #         switch %= 4


            # print(x,dx,"|",y,dy,"|",switch,"|",nxt)
            result.append(matrix[y][x])
            matrix[y][x] = 999





        return result
if __name__=="__main__":
    c=Solution()
    print(c.spiralOrder([[1,2,3],[4,5,6],[7,8,9]]))#[1,2,3,6,9,8,7,4,5]
    print(c.spiralOrder([[1,2,3,4],[5,6,7,8],[9,10,11,12]]))# [1,2,3,4,8,12,11,10,9,5,6,7]
