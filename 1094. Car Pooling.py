class Solution:
    def carPooling(self, trips:list[list], capacity: int) -> bool:
        timestamp=[]# time,event
        for pas,st,end in trips:
            if st>end:
                return False
            timestamp.append([st,pas])
            timestamp.append([end, -pas])
        timestamp.sort()
        cap=0
        for _,event in timestamp:
            cap+=event
            if cap>capacity:
                return False
        return True



if __name__ =="__main__":
    C=Solution()
    print(C.carPooling([[2,1,5],[3,3,7]], capacity=4))
    print(C.carPooling(trips = [[2,1,5],[3,3,7]], capacity=5))
