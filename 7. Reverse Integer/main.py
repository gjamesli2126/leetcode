from typing import List


class Solution:
    def reverse(self, x: int) -> int:
        result=0
        negative=x<0
        x=abs(x)
        while x!=0:
            tail=x%10
            x=x//10
            # print(x)
            #test overflow
            if result>0x7fffffff//10 or result==0x7fffffff//10 and tail>7:
                return 0


            result=10*result+tail
        if negative:
            result*=-1
        return result

if __name__=="__main__":
    c=Solution()
    print(c.reverse(123))#321
    print(c.reverse(-123))#-321
    print(c.reverse(120))#21