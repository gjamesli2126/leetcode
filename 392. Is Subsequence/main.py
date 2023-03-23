class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        tailS = len(s) - 1
        tailT = len(t) - 1
        if tailS>tailT:
            return False
        elif tailS==-1:
            return True
        ptrSind=0
        ptrTind=0

        while ptrTind<=tailT:
            eS=s[ptrSind]
            eT=t[ptrTind]
            if eS==eT:
                ptrSind+=1
                if ptrSind > tailS:
                    return True
            ptrTind+=1

        return False
if __name__=="__main__":
    c=Solution()
    print(c.isSubsequence(s = "abc", t = "ahbgdc"))#True
    print(c.isSubsequence(s = "axc", t = "ahbgdc"))#False
