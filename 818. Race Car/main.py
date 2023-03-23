from typing import List
from collections import deque

class Solution:
    def racecar(self, target: int) -> int:
        q=deque()
        q.append((0,0,1))#move,position,speed
        visited=set()
        while q:
            move,position,speed=q.popleft()
            print(move,position,speed)
            if position==target:
                return move
            elif (position,speed) in visited:# when reverse could pass by the same position but with reversed speed
                continue
            else:
                visited.add((position,speed))
                q.append((move + 1, position + speed, speed * 2))# 可以先超過
                #reverse
                if (position+speed>target and speed>0) or (position+speed<target and speed<0):#原來超過了，才退回來
                    if speed>0:
                        speed=-1
                    else:
                        speed=1
                    q.append((move + 1, position, speed))
                # else:
                #     q.append((move+1,position+speed,speed*2))
            # print(visited)
if __name__=="__main__":
    c=Solution()
    # print(c.racecar(target = 3))#2
    print(c.racecar(target = 6))#5