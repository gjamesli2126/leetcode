#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // using bin-search to achieve O(log(min(m,n))
        if(nums1.size()>nums2.size()) swap(nums1,nums2);//make sure nums1 is shorter
        int m=nums1.size();
        int n=nums2.size();
        int l=0,r=m;
        while(l<=r){
            //nums1
            int mid1= l+(r-l)/2;
            int nums1_left=mid1==0?INT_MIN:nums1[mid1-1];//"left" means portion
            int nums1_right=mid1==m?INT_MAX:nums1[mid1];
            //nums2
            int mid2=(m+n)/2-mid1;//m+n-1??
            int nums2_left=mid2==0?INT_MIN:nums2[mid2-1];
            int nums2_right=mid2==n?INT_MAX:nums2[mid2];

            //if found a good to return
            if(nums1_left<=nums2_right && nums2_left<=nums1_right){
                if((m+n)%2==0) return (max(nums1_left,nums2_left)+min(nums1_right,nums2_right))/2.0;
                return min(nums1_right,nums2_right);
            }
            else if(nums2_left>nums1_right) l=mid1+1;
            else r=mid1-1;`
        }


        return 87426;
    }
};

void printDouble(double d) {
    cout << fixed << setprecision(5) << d;
}

void runTest(int testNum, vector<int> nums1, vector<int> nums2, double expected) {
    Solution sol;
    double result = sol.findMedianSortedArrays(nums1, nums2);
    if (fabs(result - expected) < 1e-6) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: median = ";
        printDouble(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: median = ";
        printDouble(result);
        cout << ", expected ";
        printDouble(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain() {
    // Test Case 1:
    // nums1 = [1,3], nums2 = [2] -> median = 2.00000
    runTest(1, {1, 3}, {2}, 2.00000);

    // Test Case 2:
    // nums1 = [1,2], nums2 = [3,4] -> median = 2.50000
    runTest(2, {1, 2}, {3, 4}, 2.50000);

    return 0;
}