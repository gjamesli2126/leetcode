from collections import OrderedDict
class DLL():
    def __init__(self,rank,set0,prev=None,next=None):
        self.rank=rank
        self.set=set0 # to store all kinds of string with the same ank
        self.prev=prev
        self.next=next
def insertNode(node:DLL,newPrev:DLL,newNext:DLL):
    newPrev.next=node
    node.prev=newPrev
    node.next=newNext
    newNext.prev=node
def removeNode(node:DLL):#,myPrev:DLL,myNext:DLL):
    myPrev=node.prev
    myNext=node.next
    myPrev.next=node.next
    myNext.prev=node.prev
class AllOne():
    def __init__(self):
        #give a dummy head and dummy tail
        self.dummyHead=DLL(rank=0,set0=None) # min=dummyHEad's next
        self.dummyTail=DLL(rank=-1,set0=None,prev=self.dummyHead) # max=dummyTail's prev
        self.dummyHead.next=self.dummyTail
        self.dic={} #string:dll
    def inc(self, key: str) -> None:
        if key not in self.dic.keys():
            if self.dummyHead.next.rank==1:
                firstRankDll=self.dummyHead.next
                firstRankDll.set.add(key)
            else:
                firstRankDll=DLL(rank=1,set0={key})
                insertNode(firstRankDll,self.dummyHead,self.dummyHead.next)
            self.dic[key] = firstRankDll
        else:
            dll=self.dic[key]
            if dll.next.rank==dll.rank+1:
                nextRankDll = dll.next
                dll.set.remove(key)
                nextRankDll.set.add(key)
            else:
                nextRankDll=DLL(rank=dll.rank+1,set0={key})
                insertNode(nextRankDll,dll,dll.next)
                dll.set.remove(key)
            if not dll.set:
                removeNode(dll)
            self.dic[key]=nextRankDll

    def dec(self, key: str) -> None:
        dll=self.dic[key]
        newRank=dll.rank-1
        prevRankDll =dll.prev
        dll.set.remove(key)
        if not dll.set:
            removeNode(dll)
        if newRank==0:
            del self.dic[key]
        else:
            if prevRankDll.rank==newRank:
                prevRankDll.set.add(key)
                self.dic[key]=prevRankDll
            else:
                newDll=DLL(rank=newRank,set0={key})
                insertNode(newDll,prevRankDll,prevRankDll.next)
                self.dic[key]=newDll

    def getMaxKey(self) -> str:
        return next(iter(self.dummyTail.prev.set)) if self.dic.keys() else ""
    def getMinKey(self) -> str:
        return next(iter(self.dummyHead.next.set)) if self.dic.keys() else ""
def _print(all1:AllOne):
    dll=all1.dummyHead
    while dll:
        print(f"{dll.rank,dll.set}",end="->")
        dll=dll.next
    print("|")
    print("|",end="")
    dll = all1.dummyTail
    while dll:
        print(f"<-{dll.rank, dll.set}", end="")
        dll=dll.prev
    print()

if __name__=="__main__":
    allOne =AllOne()  #
    allOne.inc("hello")  #
    allOne.inc("hello")  #
    print(allOne.getMaxKey())  # return "hello"
    print(allOne.getMinKey())  # return "hello"
    allOne.inc("leet")
    # _print(allOne)
    print(allOne.getMaxKey())  # return "hello"
    print(allOne.getMinKey())  # return "leet"