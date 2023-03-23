class Solution:
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:
        total = 0
        boxTypes.sort(key=lambda x: x[1], reverse = True)
        for boxes, units in boxTypes:
            maxFit = min(truckSize, boxes)
            total += maxFit * units
            truckSize -= maxFit
            if not truckSize: break
        return total