import collections
import copy


class Solution:
    def slidingPuzzle(self, board: list) -> int:
        swaps = {
            0: [1, 3],
            1: [0, 2, 4],
            2: [1, 5],
            3: [0, 4],
            4: [1, 3, 5],
            5: [2, 4]
        }
        goal = [1, 2, 3] + [4, 5, 0]
        board = board[0] + board[1]
        i = board.index(0)
        q = collections.deque([(board, 0, i)])
        visited = {tuple(board)}# set, tuple: immutable
        while q:
            # print(q)
            board, moves, i = q.popleft()
            if board == goal:
                return moves
            # print(swaps[i])
            for j in swaps[i]:
                nxt = copy.deepcopy(board)
                nxt[i], nxt[j] = nxt[j], nxt[i]
                if tuple(nxt) not in visited:
                    visited.add(tuple(nxt))
                    q.append((nxt, moves + 1, j))
        return -1
if __name__=="__main__":
    obj=Solution()
    # board = [[1, 2, 3], [4, 0, 5]]
    # print(obj.slidingPuzzle(board)==1)
    board = [[1, 2, 3], [5, 4, 0]]
    print(obj.slidingPuzzle(board)==-1)
    # board=[[4, 1, 2], [5, 0, 3]]
    # print(obj.slidingPuzzle(board)==5)
