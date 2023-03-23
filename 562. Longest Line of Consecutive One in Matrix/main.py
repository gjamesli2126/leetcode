from typing import List


class Solution:
    def longestLine(self, mat: List[List[int]]) -> int:
        maxCount=0
        rowNum=len(mat)
        colNum=len(mat[0])
        count=[[0]*rowNum,[0]*colNum,[0]*(rowNum+colNum),[0]*(rowNum+colNum)        ]
        #       down       right        ascendDiag:down_Right      desDiag:up_Right
        for i in range(rowNum):
            for j in range(colNum):
                num=mat[i][j]
                if num==0:
                    for vec,loc in zip((0,1,2,3),(i,j,i+j,j-i)):#slow -> can deouple into 4 lines will be faster
                        count[vec][loc]=0
                elif num==1:
                    for vec,loc in zip((0,1,2,3),(i,j,i+j,j-i)):
                        count[vec][loc]+=1
                        maxCount=max(maxCount,count[vec][loc])
        return maxCount



if __name__=="__main__":
    c=Solution()
    print(c.longestLine(mat = [[0,1,1,0],[0,1,1,0],[0,0,0,1]]))#3
    # print(c.longestLine(mat = [[1,1,1,1],[0,1,1,0],[0,0,0,1]]))#4