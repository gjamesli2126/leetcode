from typing import List

class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        n=len(matrix)
        _print(matrix)
        for i in range(n//2):
            print(i,n-i-1)
            for j in range(i,n-i-1):
                org=matrix[i][j]
                matrix[i][j]=matrix[n-1-j][i]
                matrix[n - 1 - j][i]=matrix[n-1-i][n-1-j]
                matrix[n - 1 - i][n - 1 - j]=matrix[j][n-1-i]
                matrix[j][n - 1 - i]=org
                _print(matrix)




def _print(m):
    for row in m:
        print(row)
    print("---")

if __name__=="__main__":
    c=Solution()
    # matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    # c.rotate(matrix)
    # _print(matrix) #[[7,4,1],[8,5,2],[9,6,3]]
    #
    # matrix = [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]
    # c.rotate(matrix)
    # _print(matrix)  # [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

    matrix=[[i for i in range(1+i*4,5+i*4)] for i in range(4)]
    c.rotate(matrix)
    # _print(matrix)