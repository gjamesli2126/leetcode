class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        if len(s)!=len(t):
            return False
        hashTableST = {}
        hashTableTS={}
        for se,te in zip(s,t):
            if se not in hashTableST.keys() and te not in hashTableTS.keys():
                hashTableST[se]=te
                hashTableTS[te]=se
            elif se not in hashTableST.keys() or te not in hashTableTS.keys() or hashTableST[se]!=te or hashTableTS[te]!=se:
                return False
        return True


if __name__=="__main__":
    c=Solution()
    print(c.isIsomorphic(s = "egg", t = "add"))#T
    print(c.isIsomorphic(s = "foo", t = "bar"))#F
    print(c.isIsomorphic(s = "paper", t = "title"))#T
    print(c.isIsomorphic("badc","baba"))#F