
class DoubleLinkList:
    def __init__(self,key0=-1,val0=-1,next0=None,prev0=None):
        self.key=key0
        self.val=val0
        self.next=next0
        self.prev=prev0

class LRUCache:
    def __init__(self, capacity: int):
        self.headKey=-1#DoubleLinkList()
        self.tailKey=-1#self.head
        self.dic={}# {key:DLL}
        self.capacity=capacity
    def ranker(self,lastlyTouchKey):
        #priortize recently used node
        if lastlyTouchKey==self.headKey:
            return
        elif lastlyTouchKey==self.tailKey:
            self.tailKey=self.dic[self.tailKey].prev.key
        newhead = self.dic[lastlyTouchKey]
        prevNode = newhead.prev
        nextNode = newhead.next
        if prevNode:
            prevNode.next = nextNode #must have previous node
            newhead.prev = None
        if nextNode:
            nextNode.prev=prevNode

        newhead.next=self.dic[self.headKey]
        self.dic[self.headKey].prev=newhead
        self.headKey=lastlyTouchKey

            # omit least used node if node number exceed limit
        if len(self.dic) > self.capacity:
            oldtailKey=self.tailKey
            newtail=self.dic[self.tailKey].prev
            newtail.next = None
            self.tailKey = newtail.key
            del self.dic[oldtailKey]



    def get(self, key: int) -> int:
        if key in self.dic.keys():
            self.ranker(key)
            return self.dic[key].val
        else:
            return -1

    def put(self, key: int, value: int) -> None:
        if self.headKey==-1:
            self.dic[key]=DoubleLinkList(key0=key,val0=value)
            self.headKey=key
            self.dic[self.headKey].key=key
            self.dic[self.headKey].val=value
            self.tailKey=key
        else:
            if key not in self.dic.keys():
                self.dic[key]=DoubleLinkList(key0=key,val0=value)
            else:
                self.dic[key].val = value
            self.ranker(key)


def _print(dll_head:DoubleLinkList,lru:LRUCache):
    print(lru.headKey,end="__\t")
    while dll_head:
        if dll_head.prev:
            print(f"{dll_head.prev.key,dll_head.prev.val}<-",end="")
        else:
            print("|<-",end="")
        print(f"({dll_head.key,dll_head.val})",end="")
        if dll_head.next:
            print(f"->({dll_head.next.key,dll_head.next.val})",end="")
        else:
            print("->|",end="")
        print("\t\t",end="")
        dll_head=dll_head.next
    print("\t__",lru.tailKey)

if __name__=="__main__":
    lRUCache=LRUCache(2)
    lRUCache.put(1, 1) # cache is {1 = 1}
    lRUCache.put(2, 2)#  cache is {1 = 1, 2 = 2}
    print(lRUCache.get(1))#  return 1
    lRUCache.put(3, 3)#  LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    print(lRUCache.get(2))#  returns - 1(not found)
    lRUCache.put(4, 4)#  LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    print(lRUCache.get(1))#  return -1(not found)
    print(lRUCache.get(3))#     return 3
    print(lRUCache.get(4))#     return 4

    lRUCache = LRUCache(3)
    lRUCache.put(1, 1)#1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    lRUCache.put(2, 2)#2->1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    lRUCache.put(3, 3)#3->2->1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    lRUCache.put(4, 4)#4->3->2
    print(lRUCache.get(4))#4; 4->3->2
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(3))#3; 3->4->2
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(2))#2; 2->3->4
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(1))#-1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    lRUCache.put(5, 5)#5->2->3
    _print(lRUCache.dic[lRUCache.headKey],lRUCache)
    print(lRUCache.get(1))#-1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(2))#2->5->3
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(3))#3->2->5
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(4))#-1
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)
    print(lRUCache.get(5))#5->3->2
    _print(lRUCache.dic[lRUCache.headKey], lRUCache)



