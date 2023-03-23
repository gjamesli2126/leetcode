from typing import List
class FreqStack:
    def __init__(self):
        self.groupStacks={}#{freq:stack}
        self.freq={}#{elem:freq}
        self.maxFreq=0
    def push(self, val: int) -> None:
        if val not in self.freq.keys():
            self.freq[val]=0
        self.freq[val]+=1
        self.maxFreq=max(self.maxFreq,self.freq[val])
        if self.maxFreq not in self.groupStacks.keys():
            self.groupStacks[self.maxFreq]=[]
        self.groupStacks[self.freq[val]].append(val)
    def pop(self) -> int:
        topElement=self.groupStacks[self.maxFreq].pop()
        self.freq[topElement]-=1
        if not self.groupStacks[self.maxFreq]:
            self.maxFreq-=1
        return topElement



if __name__=="__main__":
    # Your FreqStack object will be instantiated and called as such:
    freqStack = FreqStack()
    freqStack.push(5)
    freqStack.push(7)
    freqStack.push(5)
    freqStack.push(7)
    freqStack.push(4)
    freqStack.push(5)
    z=freqStack.pop() # return 5, as 5 is the    most    frequent.The   stack    becomes[5, 7, 5, 7, 4].
    x=freqStack.pop() # return 7, as 5 and 7 is the     most    frequent, but    7 is closest    to    the    top.The    stack    becomes[5, 7, 5, 4].
    c=freqStack.pop()# return 5, as 5 is the    most    frequent.The    stack    becomes[5, 7, 4].
    v=freqStack.pop()# return 4, as 4, 5 and 7 is the     most    frequent, but     4 is closest    to    the    top.The    stack    becomes[5, 7].
    print(z,x,c,v)