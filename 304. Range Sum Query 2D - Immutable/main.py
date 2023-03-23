from typing import List
from pprint import pprint as pp

class NumMatrix:
    def __init__(self, matrix: List[List[int]]):
        xMax=len(matrix[0])
        yMax=len(matrix)
        if xMax==0 or yMax==0: return
        self.dp=[[0]*(xMax+1) for _ in range(yMax+1)] # 多一防corner case ==dummy row & dummy col

        for y in range(0,yMax):
            for x in range(0,xMax):
                self.dp[y+1][x+1]=matrix[y][x]+self.dp[y+1][x]+self.dp[y][1+x]-self.dp[y][x]
        # print(self.dp)
    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        point2org=self.dp[row2+1][col2+1]
        upper2org=self.dp[row1][col2+1]
        left2org=self.dp[row2+1][col1]
        leftCorner=self.dp[row1][col1]
        return point2org-upper2org-left2org+leftCorner
if __name__=="__main__":
    numMatrix =NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]])
    print(numMatrix.sumRegion(2, 1, 4, 3))  # return 8 (i.e sum of the red rectangle)
    print(numMatrix.sumRegion(1, 1, 2, 2))  # return 11 (i.e sum of the green rectangle)
    print(numMatrix.sumRegion(1, 2, 2, 4))  # return 12 (i.e sum of the blue rectangle)

    #corner case
    numMatrix = NumMatrix([[-1]])
    print(numMatrix.sumRegion(0,0,0,0))  # -1

    numMatrix =NumMatrix([[-4,-5]])
    print(numMatrix.sumRegion(0, 0, 0, 0))  # -4
    print(numMatrix.sumRegion(0, 0, 0, 1))  # -9
    print(numMatrix.sumRegion(0, 1, 0, 1))  # -5

