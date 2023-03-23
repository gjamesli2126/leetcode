from collections import deque
from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        """
        DP
        """
        candidates.sort()
        memo = [[]] * (target + 1)

        # Explore all targets from 1 to target
        for sub_target in range(1, target + 1):
            new_dp = []

            # Explore candidates smaller than partial target (in order)
            for candidate in candidates:

                if candidate > sub_target:
                    break

                # Candidate equals partial target
                if candidate == sub_target:
                    new_dp.append([candidate])
                    break

                for prev_combo in memo[sub_target - candidate]:
                    # Avoid double-counting by extending only to
                    # ordered combinations (e.g. [3,2],[2,3] => [2,3])
                    if candidate >= prev_combo[-1]:
                        new_dp.extend([prev_combo + [candidate]])

            memo[sub_target] = new_dp

        return memo[-1]
if __name__=="__main__":
    c=Solution()
    print(c.combinationSum(candidates = [2,3,6,7], target = 7))#[[2,2,3],[7]]
    print(c.combinationSum(candidates = [2,3,5], target = 8))#[[2,2,2,2],[2,3,3],[3,5]]
    print(c.combinationSum(candidates = [2], target = 1))#[]
