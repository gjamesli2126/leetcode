from typing import List
from collections import deque

class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        ybound=len(heights)-1
        xbound=len(heights[0])-1
        q=deque()



if __name__=="__main__":
    c=Solution()
    print(c.pacificAtlantic(heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]))
    # Output: [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
    # print(c.pacificAtlantic(heights = [[2,1],[1,2]]))
    # Output: [[0, 0], [0, 1], [1, 0], [1, 1]]