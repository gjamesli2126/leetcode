#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int findStInd(vector<int>& arr,int tar){//find upperbound(inclusive), lower then equal or equal
        int l=0;
        int r=arr.size()-1;
        while(l<r){
            int mid=l+(r-l)/2;
            if(arr[mid]<=tar) l=mid+1;
            else r=mid;
        }
        return max(0,l-1);//avoid out of bound
    }
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> ans;
        //implement binary search + two-pointer
        //b-search find uppperBound
        int stInd= findStInd(arr,x);
        //while seek on left first, and seek right
        int l=stInd;
        int r=stInd+1;
        while((l>=0 || r<arr.size()) && k){
            //compare choose which
            if(l==-1) ans.push_back(arr[r++]);
            else if(r==arr.size()) ans.push_back(arr[l--]);//avoid the out of bound
            else if(abs(x-arr[l])<=abs(arr[r]-x)) ans.push_back(arr[l--]);
            else ans.push_back(arr[r++]);
            k--;
        }
        //sort ans
        sort(ans.begin(),ans.end());
        return ans;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<int> arr, int k, int x, const vector<int>& expected) {
    Solution sol;
    vector<int> result = sol.findClosestElements(arr, k, x);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: findClosestElements(";
        printVector(arr);
        cout << ", " << k << ", " << x << ") = ";
        printVector(result);
        cout << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: findClosestElements(";
        printVector(arr);
        cout << ", " << k << ", " << x << ") = ";
        printVector(result);
        cout << ", expected ";
        printVector(expected);
        cout << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    runTest(1, {1,2,3,4,5}, 4, 3, {1,2,3,4});

    // Example 2
    runTest(2, {1,1,2,3,4,5}, 4, -1, {1,1,2,3});

    // Additional tests:
    // k == arr.size()
    runTest(3, {1,2,3}, 3, 2, {1,2,3});

    // x exactly matches an element
    runTest(4, {1,3,5,7,9}, 3, 5, {3,5,7});

    // ties broken by smaller value
    runTest(5, {1,2,3,4}, 2, 3, {2,3});
    runTest(6, {1}, 1,1, {1});


    return 0;
}