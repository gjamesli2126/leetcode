from typing import List
class Solution:
    def helper(self,s,wordDict,memo):
        if s in memo.keys():
            return memo[s]
        elif not s:
            return []
        res=[]
        for word in wordDict:
            if not s.startswith(word):
                continue
            elif len(s)==len(word):
                res.append(word)
            else:
                resultOfTheRest=self.helper(s[len(word):],wordDict,memo)
                for item in resultOfTheRest:
                    item=word+' '+item
                    res.append(item)
        memo[s]=res
        return res

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        return self.helper(s,wordDict,{})
if __name__=="__main__":
    c=Solution()
    print(c.wordBreak(s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]))#["cats and dog","cat sand dog"]
    print(c.wordBreak(s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]))
    #["pine apple pen apple","pineapple pen apple","pine applepen apple"]