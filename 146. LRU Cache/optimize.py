from collections import OrderedDict


class LRUCache(OrderedDict):

    def __init__(self, capacity):
        self.capacity = capacity

    def get(self, key):
        if key not in self:
            return - 1

        self.move_to_end(key)
        return self[key]

    def put(self, key, value):
        if key in self:
            self.move_to_end(key)
        self[key] = value
        if len(self) > self.capacity:
            self.popitem(last=False)


if __name__=="__main__":
    lRUCache = LRUCache(3)
    lRUCache.put(1, 1)  # 1
    lRUCache.put(2, 2)  # 2->1
    lRUCache.put(3, 3)  # 3->2->1
    lRUCache.put(4, 4)  # 4->3->2
    print(lRUCache.get(4))  # 4; 4->3->2
    print(lRUCache.get(3))  # 3; 3->4->2
    print(lRUCache.get(2))  # 2; 2->3->4
    print(lRUCache.get(1))  # -1
    lRUCache.put(5, 5)  # 5->2->3
    print(lRUCache.get(1))  # -1
    print(lRUCache.get(2))  # 2->5->3
    print(lRUCache.get(3))  # 3->2->5
    print(lRUCache.get(4))  # -1
    print(lRUCache.get(5))  # 5->3->2
    