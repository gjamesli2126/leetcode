from typing import List

class DoubleLinkList:
    def __init__(self,val0=-1,next0=None,prev0=None):
        self.val=val0
        self.next=next0
        self.prev=prev0
class LRUCache:
    def __init__(self, capacity: int):
        self.head=DoubleLinkList()
        self.dic={}# {key:DLL}
    def ranker(self,lastlyTouch):

    def get(self, key: int) -> int:
        self.ranker(key)
        return self.dic[key].val if key in self.dic.keys() else -1
    def put(self, key: int, value: int) -> None:
        self.dic[key]=DoubleLinkList(value)
        if self.head.val==-1:
            self.head.val=value
        self.ranker(key)



if __name__=="__main__":
    lRUCache=LRUCache(2)
    lRUCache.put(1, 1) # cache is {1 = 1}
    lRUCache.put(2, 2)# // cache is {1 = 1, 2 = 2}
    lRUCache.get(1)# // return 1
    lRUCache.put(3, 3)# // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache.get(2)# // returns - 1(not found)
    lRUCache.put(4, 4)# // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache.get(1)# // return -1(not found)
    lRUCache.get(3)#    // return 3
    lRUCache.get(4)#    // return 4




