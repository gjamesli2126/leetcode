from typing import List
from heapq import heapify,heappop,heappush
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        ends=[]
        roomSize=0
        for st,ed in intervals:
            heappush(ends,ed)
            if st>=ends[0]:
                heappop(ends)
            else:
                roomSize+=1
            # roomSize = max(roomSize, len(ends)) #slower
        return roomSize
if __name__=="__main__":
    c=Solution()
    print(c.minMeetingRooms(intervals = [[0,30],[5,10],[15,20]]))#2
    print(c.minMeetingRooms(intervals = [[7,10],[2,4]]))#1