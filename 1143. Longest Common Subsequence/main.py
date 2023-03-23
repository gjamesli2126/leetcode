from typing import List


class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        memo=[[0]*(len(text1)+1) for _ in range(len(text2)+1)]
        for row in range(1,len(text2)+1):
            for col in range(1,len(text1)+1):
                if text2[row-1]==text1[col-1]:
                    memo[row][col]=1+memo[row-1][col-1]
                else:
                    memo[row][col] = max(memo[row-1][col],memo[row][col-1])
        return memo[-1][-1]

if __name__=="__main__":
    c=Solution()
    print(c.longestCommonSubsequence(text1 = "abcde", text2 = "ace"))#3
    print(c.longestCommonSubsequence(text1 = "abc", text2 = "abc"))#3
    print(c.longestCommonSubsequence(text1 = "abc", text2 = "def"))#0
    print(c.longestCommonSubsequence("abcaaae","ace"))#3