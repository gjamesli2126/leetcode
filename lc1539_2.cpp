#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        //missing is beyond r
        int missingToLast=arr.back()-arr.size();
        if(k>missingToLast) return arr.back()+(k-missingToLast);
        //missing is either below l Or between l~r
        int l=0,r=arr.size()-1;
        while(l<r){
            int mid=l+(r-l)/2;
            int missingSoFar=arr[mid]-(mid+1);//+1 cause from 1 to ..
            if(missingSoFar<k) l=mid+1;//too few missing, go right
            else r=mid;
        }
        // prefix [0 .. l-1] has < k missing, prefix [0 .. l] has ≥ k missing

        return l+k;//missing + values
    }
};
/*
 * Let’s break down the derivation of the formula:

￼

which simplifies to:

￼

Here’s what each part means:
	1.	￼ — The count of actual numbers in the sequence up to the gap:
In a perfect sequence starting at 1 (i.e. ￼), if there were no missing numbers, the number at index ￼ (where indices start at 0) would be ￼.
For example, if ￼, then the first 5 numbers would be ￼.
	2.	￼ — The offset from that point to the kth missing number:
The idea is that if you’re looking for the first missing number (i.e. when ￼), you don’t need to add any extra offset; the gap starts right after the ￼ count.
However, if ￼ is greater than 1, you need to “step forward” ￼ additional numbers from that baseline.
In other words, once you know there are ￼ numbers present in the natural order up to the gap, the kth missing number is not just ￼ because that would overshoot by one. The ￼ adjusts for the fact that when ￼, the missing number is immediately after ￼.
	•	Example:
If ￼, then the formula gives:
￼.
This makes sense because the very first missing number should come right after the ￼ elements that are in place.
For ￼ and ￼, the formula gives:
￼.
This means that after accounting for the 5 actual numbers in the perfect sequence (which would be 1 through 5), you need to jump 4 numbers ahead to reach the 5th missing number.

In summary:
	•	The term ￼ represents the expected number in a perfect sequence at that point.
	•	The term ￼ adjusts for the offset needed because the first missing number doesn’t require any additional shift—it starts right at the boundary. For every missing number beyond the first, you add one more to the count.
	•	Thus, the kth missing number is ￼, or simply ￼.

This ￼ is crucial because it converts from a count (starting at 1) to an offset relative to the position in the array (which is 0-indexed), ensuring that when ￼ is 1, you don’t add any extra offset.
 * */

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> arr, int k, int expected) {
    Solution sol;
    int result = sol.findKthPositive(arr, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: findKthPositive(arr, " << k << ") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: findKthPositive(arr, " << k << ") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: arr = [2,3,4,7,11], k = 5
    // Expected Output: 9
    runTest(1, {2,3,4,7,11}, 5, 9);

    // Test Case 2:
    // Input: arr = [1,2,3,4], k = 2
    // Expected Output: 6
    runTest(2, {1,2,3,4}, 2, 6);
    runTest(3, {2}, 1,1);
    return 0;
}