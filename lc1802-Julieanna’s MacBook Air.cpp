#include <vector>
#include <iostream>
using namespace std;
class Solution {
private:
    long testIfValidSum(const long& midVal, const long& targetIndex, const long& n){
        long s=0;
        long leftVal=max(midVal-targetIndex,0L);//最左邊的值為0 or 超過minIndex的高度, 若A[leftIndex>0]=0表示 A[0]也必為0
        s+=(midVal+leftVal)*(midVal-leftVal+1)/2;//上底加下底 乘 高 除以2 -> 這裡的高因為「植樹問題」因此要＋1; 直差多少，index就差多少
        long rightVal=max(midVal-(n-1-targetIndex),0L);//((n - 1) - targetIndex) calculates the distance from the index to the last element.
        //midVal-(n-1-targetIndex) 即為最大可移動幅度 or 若 midVal超過最大可移動幅度 則 rightVal則為差值
        s+=(midVal+rightVal)*(midVal-rightVal+1)/2;
        s-=midVal;//中間重複計算要扣掉
        return s;
    }
public:
    long maxValue(long n, long index, long maxSum) {
        //binary search for right mid
        maxSum-=n;//呼應return l+1
        long l=0;//lowest possible midVal 
        long r=maxSum;//highest possible midVal
        while(l<r){
            long midVal=(l+r+1)/2;//'+1' to let binary search does not lean to leftbound
            if(testIfValidSum(midVal,index,n)<=maxSum){
                l=midVal;
            }
            else r=midVal-1;
        }
        return l+1;// + 1 becasue all values must be 1+calculated value
    }
};


// long main(){
//     Solution s;
//     cout<<s.maxValue(4, 2, 6);
//     return 0;
// }

/*
1802. Maximum Value at a Given Index in a Bounded Array
Medium


You are given three positive longegers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:

nums.length == n
nums[i] is a positive longeger where 0 <= i < n.
abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
The sum of all the elements of nums does not exceed maxSum.
nums[index] is maximized.
Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

 

Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3
2 3 2 1 1 1
11234321
 

Constralongs:

1 <= n <= maxSum <= 109
0 <= index < n

hlongs:
What if the problem was instead determining if you could generate a valid array with nums[index] == target?
To generate the array, set nums[index] to target, nums[index-i] to target-i, and nums[index+i] to target-i. Then, this will give the minimum possible sum, so check if the sum is less than or equal to maxSum.
n is too large to actually generate the array, so you can use the formula 1 + 2 + ... + n = n * (n+1) / 2 to quickly find the sum of nums[0...index] and nums[index...n-1].
Binary search for the target. If it is possible, then move the lower bound up. Otherwise, move the upper bound down.

*/