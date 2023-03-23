from typing import List
from pprint import pprint as pp
"""
每行未填滿就靠左，每行填滿就左space>右space
"""
def divider(spaceNum:int,totalSpace:int)->list:
    # print(spaceNum,totalSpace,end="--->")
    if totalSpace%spaceNum==0:
        return [totalSpace//spaceNum,spaceNum,0]# last two are place holders
    else:
        spaceS=totalSpace//spaceNum
        # print(spaceS,end="--------->")
        untilIndex=totalSpace-spaceS*spaceNum-1
        return [spaceS+1,untilIndex,spaceS]# use "spaceS+1" until "untilIndex" then use "spaceS"
def padSpace(orgList:list,maxwidth:int,last=False)->str:
    length=len(orgList)
    if length==1 and not last:
        out=orgList[0]+(maxwidth-len(orgList[0]))*' '
    elif length==2 and not last:
        out = orgList[0] + (maxwidth - len(orgList[0])-len(orgList[1])) * ' ' + orgList[1]
    elif not last:
        middle = ""
        remainSpot=maxwidth-len(orgList[0])#-len(orgList[-1])
        alphaCharc=sum(len(e) for e in orgList[1:])
        # print(remainSpot,alphaCharc,end="] ")
        leftSpaceS,untilIndex,rightSpaceS=divider(length-2+1,remainSpot-alphaCharc)
        # print(leftSpaceS,untilIndex,rightSpaceS)
        for ind,e in enumerate(orgList[1:]):
            if ind<=untilIndex:
                middle += leftSpaceS * ' ' # space
                middle+=e#word
            else:
                middle+=rightSpaceS*' '
                middle+=e
        out=orgList[0]  + middle
    elif last:
        middle = ""
        # remainSpot = maxwidth - 2 - len(orgList[0])
        for e in orgList[1:]:
            middle+=' '
            middle+=e
        out = orgList[0]+middle
        out+=(maxwidth-len(out))*' '

    else:
        out="Bug:(\t"
    return out
class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        result=[]
        tmpStringList=[]
        remainCharc=maxWidth
        for e in words:
            length=len(e)
            remainCharc-=length
            # print(e,len(e),remainCharc,len(tmpStringList))
            if remainCharc-(len(tmpStringList)-1)<=0:
                tmpString=padSpace(tmpStringList,maxWidth)
                tmpStringList=[]
                remainCharc=maxWidth-length
                result.append(tmpString)
            tmpStringList.append(e)
        tmpString = padSpace(tmpStringList,maxWidth,last=True)
        result.append(tmpString)
        return result
if __name__=="__main__":
    c=Solution()
    pp(c.fullJustify(["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16))
    # [
    #     "This    is    an",
    #     "example  of text",
    #     "justification.  "
    # ]

    pp(c.fullJustify(["What","must","be","acknowledgment","shall","be"], maxWidth = 16))
    # [
    #     "What   must   be",
    #     "acknowledgment  ",
    #     "shall be        "
    # ]

    pp(c.fullJustify(["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20))
    # [
    #     "Science  is  what we",
    #     "understand      well",
    #     "enough to explain to",
    #     "a  computer.  Art is",
    #     "everything  else  we",
    #     "do                  "
    # ]