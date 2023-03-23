from typing import List
class Solution:
    def minMovesToMakePalindrome(self, s: str) -> int:
        s=list(s)
        result=0
        while s:
            topElem=s[-1]
            firstMetIndex=s.index(topElem)
            #if match Exist
            if firstMetIndex!=len(s)-1:
                result+=firstMetIndex# shift to the front need firstMetIndex moves
                s.pop(firstMetIndex)
            else:#the only one match nothing
                result+=firstMetIndex//2#must be shift to the middle
            s.pop()
        return result
if __name__=="__main__":
    c=Solution()
    print(c.minMovesToMakePalindrome(s = "aabb"))#2
    print(c.minMovesToMakePalindrome(s = "letelt"))#2
    print(c.minMovesToMakePalindrome(s = "letelzt"))#4