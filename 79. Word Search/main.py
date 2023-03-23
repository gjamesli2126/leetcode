from typing import List
class Solution:
    def exist(self, board, word)->bool:
        if len(board)*len(board[0])<len(word):
            return False
        def backtrack(modBoard,srunkWord)->bool:
            xMax=len(modBoard[0])
            yMax=len(modBoard)
            #base case
            if len(srunkWord)==0 or xMax*yMax>len(srunkWord) or 

        return backtrack(board,word)
if __name__=="__main__":
    c=Solution()
    print(c.exist(board = [["A","B","C","E"],
                           ["S","F","C","S"],
                           ["A","D","E","E"]], word = "ABCCED"))#True

    print(c.exist(board = [["A","B","C","E"],
                           ["S","F","C","S"],
                           ["A","D","E","E"]], word = "SEE"))#True

    print(c.exist(board = [["A","B","C","E"],
                           ["S","F","C","S"],
                           ["A","D","E","E"]], word = "ABCB"))#False

    print(c.exist([["A","A","A","A","A","A"],
                   ["A","A","A","A","A","A"],
                   ["A","A","A","A","A","A"],
                   ["A","A","A","A","A","A"],
                   ["A","A","A","A","A","A"],
                   ["A","A","A","A","A","A"]],"AAAAAAAAAAAABAA"))#False