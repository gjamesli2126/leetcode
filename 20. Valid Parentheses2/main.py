from collections import deque
from typing import List
class Solution:
    def isValid(self, s: str) -> bool:
        #不可以看odd, even 因為萬一有其他符號 If 有follow up
        #binary search 有屁用only if the array is sorted



if __name__=="__main__":
    c=Solution()
    print(c.isValid("{ { } [ ] [ [ [ ] ] ] } "))#T
    print(c.isValid("{ { ( { } ) } }"))#T
    print(c.isValid("()[]{}"))#T
    print(c.isValid("]")) #F
    print(c.isValid("(])")) #F
    print(c.isValid(""))#T
