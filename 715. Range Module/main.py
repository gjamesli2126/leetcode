import bisect
class RangeModule:

    def __init__(self):
        self.track = []

    def addRange(self, left, right):
        startIndex=bisect.bisect_left(self.track,left)
        endIndex=bisect.bisect_right(self.track,right)
        # if Index outside the range
        subtrack=[]
        if startIndex%2==0:
            subtrack.append(left)
        if endIndex%2==0:
            subtrack.append(right)
        self.track[startIndex:endIndex]=subtrack


    def removeRange(self, left, right):
        startIndex=bisect.bisect_left(self.track,left)
        endIndex=bisect.bisect_right(self.track,right)
        #if index in the range then REMOVE
        subtrack=[]
        if startIndex%2==1:
            subtrack.append(left)
        if endIndex%2==1:
            subtrack.append(right)
        self.track[startIndex:endIndex]=subtrack


    def queryRange(self, left, right):
        #if index are in the same range and they are IN
        startIndex=bisect.bisect_right(self.track,left)
        endIndex=bisect.bisect_left(self.track,right)
        return startIndex==endIndex and startIndex%2==1


if __name__=="__main__":
    # Your RangeModule object will be instantiated and called as such:
    obj = RangeModule()

    obj.addRange(10,20)
    obj.removeRange(14,16)

    print(obj.queryRange(10,14))
    print(obj.queryRange(13, 15))
    print(obj.queryRange(16, 17))

