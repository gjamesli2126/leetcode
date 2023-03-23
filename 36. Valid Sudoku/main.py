from typing import List


class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        # 9 small sqr
        starts=[(x,y) for x in (0,3,6) for y in (0,3,6)]
        for st in starts:
            x0, y0 = st
            count=0
            SET=set()
            for dy in range(3):
                y = dy+y0
                for dx in range(3):
                    x=dx+x0
                    e=board[y][x]
                    if e==".":
                        continue
                    count+=1
                    SET.add(e)
            if len(SET)<count:
                return False




        # 9 rows
        for row in board:
            SET=set()
            count=0
            for e in row:
                if e==".":
                    continue
                SET.add(e)
                count+=1
            if len(SET)<count:
                return False
        #9 columns
        for x in range(9):
            SET=set()
            count = 0
            for y in range(9):
                e=board[y][x]
                if e==".":
                    continue
                SET.add(e)
                count+=1
            if len(SET)<count:
                return False

        return True
if __name__=="__main__":
    c=Solution()
    print(c.isValidSudoku(board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]))#True

    print(c.isValidSudoku(board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]))#False
