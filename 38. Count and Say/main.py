from typing import List
class Solution:
    def stringGen(self,string:str)->str:
        output=""
        count=1
        for i,c in enumerate(string):
            if i==0:
                continue
            elif c==string[i-1]:
                count+=1
                continue
            output = "".join([output, str(count), string[i - 1]])
            count = 1
        output = "".join([output, str(count), string[-1]])
        return output

    def countAndSay(self, n: int) -> str:
        if n==1:
            return "1"
        elif n==2:
            return "11"
        stringNum="1"
        for _ in range(n-1):
            stringNum=self.stringGen(stringNum)
        return stringNum
if __name__=="__main__":
    c=Solution()
    # print(c.countAndSay(1))#1
    print(c.countAndSay(30))#1211
