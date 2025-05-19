#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        //assumming k<=n
        long local_sum=0;
        long global_max;//=-10000;
        int i;
        for(i=0;i<k;i++) local_sum+=nums[i];
        global_max= local_sum;
        for(;i<nums.size();i++){
            local_sum-=nums[i-k];
            local_sum+=nums[i];
            global_max=max(global_max,local_sum);
        }
        return (double)global_max/k;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<int> nums, int k, double expected) {
    Solution sol;
    double result = sol.findMaxAverage(nums, k);
    if (fabs(result - expected) < 1e-5) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: findMaxAverage(";
        printVector(nums);
        cout << ", " << k << ") = " << fixed << setprecision(5) << result
             << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: findMaxAverage(";
        printVector(nums);
        cout << ", " << k << ") = " << fixed << setprecision(5) << result
             << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    // nums = [1,12,-5,-6,50,3], k = 4 -> 12.75000
    runTest(1, {1, 12, -5, -6, 50, 3}, 4, 12.75);

    // Example 2
    // nums = [5], k = 1 -> 5.00000
    runTest(2, {5}, 1, 5.0);

    runTest(3,{8860,-853,6534,4477,-4589,8646,-6155,-5577,-1656,-5779,-2619,-8604,-1358,-8009,4983,7063,3104,-1560,4080,2763,5616,-2375,2848,1394,-7173,-5225,-8244,-809,8025,-4072,-4391,-9579,1407,6700,2421,-6685,5481,-1732,-8892,-6645,3077,3287,-4149,8701,-4393,-9070,-1777,2237,-3253,-506,-4931,-7366,-8132,5406,-6300,-275,-1908,67,3569,1433,-7262,-437,8303,4498,-379,3054,-6285,4203,6908,4433,3077,2288,9733,-8067,3007,9725,9669,1362,-2561,-4225,5442,-9006,-429,160,-9234,-4444,3586,-5711,-9506,-79,-4418,-4348,-5891},93,-594.58065);
    return 0;
}