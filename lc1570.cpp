#include <bits/stdc++.h>
#define testMain main
using namespace std;

class SparseVector {
public:
    vector<int> vec1;
    SparseVector(vector<int> &vec1) {
        // TODO: Initialize the sparse vector representation.
        // For example, iterate over 'nums' and if nums[i] != 0, add {i, nums[i]} to 'sparse'.
        this->vec1=vec1;
    }

    // Return the dotProduct of two sparse vectors.
    int dotProduct(SparseVector& svec2) {
        // TODO: Compute and return the dot product using the sparse representation.
        // You can use a two-pointer approach to iterate over the nonzero pairs in both vectors.
        int i;
        int sumprod=0;
        for(i=0;i<vec1.size();i++) sumprod+=vec1[i]*svec2.vec1[i];
        return sumprod;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums1, vector<int> nums2, int expected) {
    SparseVector v1(nums1);
    SparseVector v2(nums2);
    int result = v1.dotProduct(v2);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: result = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: expected " << expected << " but got "
             << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
    // Expected Output: 8
    runTest(1, {1,0,0,2,3}, {0,3,0,4,0}, 8);

    // Example 2:
    // Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
    // Expected Output: 0
    runTest(2, {0,1,0,0,0}, {0,0,0,0,2}, 0);

    // Example 3:
    // Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
    // Expected Output: 6
    runTest(3, {0,1,0,0,2,0,0}, {1,0,0,0,3,0,4}, 6);

    return 0;
}