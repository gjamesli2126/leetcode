from typing import List
class Solution:
    def fizzBuzz(self, n: int) -> List[str]:
        counter_3=0
        counter_5=0
        lst=[]
        for i in range(1,n+1):
            string=""
            counter_3+=1
            counter_5+=1
            if counter_3==3:
                string+="Fizz"
                counter_3=0
            if counter_5==5:
                string+="Buzz"
                counter_5=0
            if not string:
                string=str(i)
            lst.append(string)
        return lst
if __name__=="__main__":
    c=Solution()
    print(c.fizzBuzz(3))#1 2 Fizz
    print(c.fizzBuzz(5))#["1","2","Fizz","4","Buzz"]