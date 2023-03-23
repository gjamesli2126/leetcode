from typing import List
class Solution:
    def shortestDistanceColor(self, colors: List[int], queries: List[List[int]]) -> List[int]:
        #could be optimized by adding forward & backward boundary
        lenCol=len(colors)
        indColorTable=[[-1]*3 for _ in range(lenCol)]
        #Forward
        for i,c in enumerate(colors):
            for dist,backtrackIndex in enumerate(range(i,-1,-1)):
                if indColorTable[backtrackIndex][c-1]==-1 or indColorTable[backtrackIndex][c-1]>dist:
                    indColorTable[backtrackIndex][c - 1]=dist
                elif indColorTable[backtrackIndex][c-1]<dist:
                    break
        #Backward
        for i in range(lenCol-1,-1,-1):
            c=colors[i]
            for dist,forwardIndex in enumerate(range(i,lenCol)):
                if indColorTable[forwardIndex][c-1]==-1 or indColorTable[forwardIndex][c-1]>dist:
                    indColorTable[forwardIndex][c - 1]=dist
                elif indColorTable[forwardIndex][c-1]<dist:
                    break
        # print(indColorTable)
        result=[indColorTable[loc][targetCol-1] for loc,targetCol in queries]
        return result
    def shortestDistanceColor_PrecomputeLTE(self, colors: List[int], queries: List[List[int]]) -> List[int]:
        lenCol=len(colors)
        indColorTable=[[-1]*3 for _ in range(lenCol)]
        #Forward
        for i,c in enumerate(colors):
            for dist,backtrackIndex in enumerate(range(i,-1,-1)):
                if indColorTable[backtrackIndex][c-1]==-1 or indColorTable[backtrackIndex][c-1]>dist:
                    indColorTable[backtrackIndex][c - 1]=dist
        #Backward
        for i in range(lenCol-1,-1,-1):
            c=colors[i]
            for dist,forwardIndex in enumerate(range(i,lenCol)):
                if indColorTable[forwardIndex][c-1]==-1 or indColorTable[forwardIndex][c-1]>dist:
                    indColorTable[forwardIndex][c - 1]=dist
        # print(indColorTable)
        result=[indColorTable[loc][targetCol-1] for loc,targetCol in queries]
        return result
    def shortestDistanceColor_BruiteForceTLE(self, colors: List[int], queries: List[List[int]]) -> List[int]:
        colorDict={color:[] for color in range(1,4)}
        result=[]
        for i,color in enumerate(colors):
            colorDict[color].append(i)
        for loc,target in queries:
            options=colorDict[target]
            if not options:
                result.append(-1)
                continue
            minDist=min([abs(loc-dst) for dst in options])
            result.append(minDist)
        return result
if __name__=="__main__":
    c=Solution()

    print(c.shortestDistanceColor( colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]))#[3 0 3]
    print(c.shortestDistanceColor(colors = [1,2], queries = [[0,3]]))#[-1]