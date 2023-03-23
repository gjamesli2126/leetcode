import collections
from typing import List
class Solution:
    def shortestWay(self, source: str, target: str) -> int:
        #time complex: O(N+M), space: O(26M), M=len(source),N=len(target)
        srcDict=collections.defaultdict(list)
        prev={char:-1 for char in source}
        for si,c in enumerate(source):
            srcDict[c].extend([si]*(si-prev[c]))
            prev[c]=si
            print(prev,srcDict)

        pushSrcIndex,count=0,1
        ti=0
        while ti<len(target):
            c=target[ti]
            if c not in srcDict.keys():
                return -1
            elif pushSrcIndex <len(srcDict[c]):
                pushSrcIndex=srcDict[c][pushSrcIndex]+1
                ti+=1
            else:
                count+=1
                pushSrcIndex=0
        return count



    def shortestWay_timeMlogN(self, source: str, target: str) -> int:
        #time cmoplex: O(MlogN)
        pushSrcIndex = 0
        count=0
        maxSrc=len(source)
        maxTar=len(target)
        for ind,tc in enumerate(target):
            if tc not in source:
                return -1
            nextSrcIndex=source[pushSrcIndex:].index(tc)+pushSrcIndex+1
            if ind<maxTar-1 and target[ind+1] not in source[nextSrcIndex:] or nextSrcIndex<=pushSrcIndex or nextSrcIndex>=maxSrc:
                count += 1
                pushSrcIndex = 0
                continue
            pushSrcIndex=nextSrcIndex
        if pushSrcIndex!=0:
            count+=1
        return count




if __name__=="__main__":
    c=Solution()
    # print(c.shortestWay( source = "abc", target = "abcbc"))#2
    # print(c.shortestWay(source = "abc", target = "acdbc"))#-1
    # print(c.shortestWay(source = "xyz", target = "xzyxz"))#3
    # print(c.shortestWay("aaaaa","aaaaaaaaaaaaa"))#3
    print(c.shortestWay("adbsccc","addddddddddddsbc"))#13