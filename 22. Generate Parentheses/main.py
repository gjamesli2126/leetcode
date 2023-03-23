from typing import List
class Solution:
    def backTracking(self,n,string,result,numOpen,numClose):
        if n*2==len(string):
            result.append(string)
            return
        if numOpen<n:
            self.backTracking(n, string + "(", result, numOpen+1,  numClose)
        if numOpen>numClose:
            self.backTracking(n,string+")",result,numOpen,1+numClose)
    def generateParenthesis(self, n: int) -> List[str]:
        lst=[]
        self.backTracking(n,"",lst,0,0)
        return lst
if __name__=="__main__":
    c=Solution()
    print(c.generateParenthesis(3)) #["((()))","(()())","(())()","()(())","()()()"]
    print(c.generateParenthesis(1))#()