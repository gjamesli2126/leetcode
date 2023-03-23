from collections import deque
class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if not s1 and not s2 and not s2:
            return True
        ptr1=0
        ptr2=0
        l1=len(s1)
        l2=len(s2)
        stack=[]
        for e3 in s3:
            if  ptr1<l1 and e3==s1[ptr1]:
                ptr1+=1
            elif  ptr2<l2 and e3==s2[ptr2]:
                ptr2+=1
            else:
                return False
        if ptr1==l1 and ptr2==l2:
            return True
        return False

if __name__=="__main__":
    c=Solution()
    print(c.isInterleave(s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"))#True
    print(c.isInterleave(s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"))#false
    print(c.isInterleave(s1 = "", s2 = "", s3 = ""))#true