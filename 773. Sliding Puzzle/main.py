from collections import deque
import copy
def avail(positionIndex):
    target=[]
    maxIndex=5
    rowElementCount=3
    for vec in (-1,-rowElementCount,+1,+rowElementCount):
        nxt=vec+positionIndex
        if nxt<0 or nxt>maxIndex:
            continue
        elif (vec==1 or vec==-1) and int(nxt/rowElementCount)!=int(positionIndex/rowElementCount):
            continue
        else:
            target.append(nxt)
    return target
class Solution:
    def slidingPuzzle(self, board0: list) -> int:
        goal=[i for i in range(1,6)]+[0]
        board=[]
        for e in board0:
            board+=e
        statusQ=deque([(board,0,board.index(0))])# board,iTH times, 0 at where
        visited=[board]
        while statusQ:
            # print(statusQ)
            status=statusQ.popleft()
            eachBoard, ith, zeroAt = status
            if eachBoard==goal:
                return ith
            # print(avail(zeroAt))
            for nextZeroAt in avail(zeroAt):
                nextBoard=copy.deepcopy(eachBoard)
                nextBoard[zeroAt],nextBoard[nextZeroAt]=nextBoard[nextZeroAt],nextBoard[zeroAt]
                if nextBoard not in visited:
                    visited.append(nextBoard)
                    statusQ.append((nextBoard,ith+1,nextZeroAt))
        return -1



if __name__ == "__main__":
    # for i in range(6):
    #     print(avail(i))
    obj = Solution()
    board = [[1, 2, 3], [4, 0, 5]]
    print(obj.slidingPuzzle(board))#1
    board = [[1, 2, 3], [5, 4, 0]]
    print(obj.slidingPuzzle(board))#-1
    board=[[4, 1, 2], [5, 0, 3]]
    print(obj.slidingPuzzle(board))#5
