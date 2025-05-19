#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        // Implement the O(n log k)multiset solution. multiset can sort things w/ logk
        multiset<int> left,right;
        int N=nums.size();
        vector<double> ans;
        if(k>N) return ans;
        int left_size=(k+1)/2;//left 會多一個 if odd num
        auto rebalance=[&](){
            //fix the len
            if(left.size()>left_size){
                right.insert(*left.rbegin());
                left.erase(prev(left.end()));
            }else if(left.size()<left_size && !right.empty()){
                left.insert(*right.begin());
                right.erase(right.begin());
            }
            //fix the val(fix the order)
            if(!left.empty() && !right.empty() && *left.rbegin()>*right.begin()){
                right.insert(*left.rbegin());
                left.insert(*right.begin());
                right.erase(right.begin());
                left.erase(prev(left.end()));
            }
        };
        auto storeMedium=[&]() {
            if (k & 1){//odd
                ans.push_back(*left.rbegin());
            }else ans.push_back(((double)*left.rbegin()+*right.begin())/2.0);
        };
        //first set left & right multiset & rm
        for(int i=0;i<k;i++){
            if(left.empty() || nums[i]<*left.rbegin()) left.insert(nums[i]);
            else right.insert(nums[i]);
            rebalance();
        }
        //first time find medium
        storeMedium();

        //rest of the arr
        for(int i=k;i<N;i++){
            int toAdd=nums[i];
            int toRemove=nums[i-k];
            //insert the new element
            if(toAdd>*left.rbegin()) left.insert(toAdd);
            else right.insert(toAdd);
            //erase the outgoing element just one element
            auto it=left.find(toRemove);
            if(it!=left.end()) left.erase(it);
            else right.erase(right.find(toRemove));//use pointer not value
//            if(left.contains(toRemove)) left.erase(toRemove);//will remove all 'toRemove'
//            else right.erase(toRemove);
            rebalance();
            storeMedium();
        }
        return ans;
    }
};

void printVector(const vector<double>& vec) {
    cout << fixed << setprecision(5) << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<int> nums, int k, vector<double> expected) {
    Solution sol;
    vector<double> result = sol.medianSlidingWindow(nums, k);
    if (result.size() == expected.size() &&
        equal(result.begin(), result.end(), expected.begin(),
              [](double a, double b){ return fabs(a - b) < 1e-5; })) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: medianSlidingWindow(";
        printVector(expected);
        cout << ") = ";
        printVector(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: medianSlidingWindow(...) = ";
        printVector(result);
        cout << ", expected ";
        printVector(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain() {
    // Example 1:
    // nums = [1,3,-1,-3,5,3,6,7], k = 3
    // Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
    runTest(1, {1,3,-1,-3,5,3,6,7}, 3,
            {1.00000, -1.00000, -1.00000, 3.00000, 5.00000, 6.00000});

    // Example 2:
    // nums = [1,2,3,4,2,3,1,4,2], k = 3
    // Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
    runTest(2, {1,2,3,4,2,3,1,4,2}, 3,
            {2.00000, 3.00000, 3.00000, 3.00000, 2.00000, 3.00000, 2.00000});

    runTest(3,{2147483647,2147483647},2,{2147483647});
    return 0;
}