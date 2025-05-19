#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int N=flowerbed.size();

        if(N==1 && n==1) return flowerbed[0]==0;
        for(int i=0;i<N && n;i++){
            bool emptyLeft= (i==0 || flowerbed[i-1]==0);
            bool emptyRight= (i==N-1 || flowerbed[i+1]==0);
            if(emptyLeft && emptyRight && flowerbed[i]==0){
                n--;
                flowerbed[i]=1;
                i++;
            }else if(flowerbed[i]==1) i++;
            else if(!emptyRight) i+=2;//boost --but overengineer
        }
        return n==0;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<int> flowerbed, int n, bool expected) {
    Solution sol;
    bool result = sol.canPlaceFlowers(flowerbed, n);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: canPlaceFlowers(";
        printVector(flowerbed);
        cout << ", " << n << ") = " << boolalpha << result
             << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: canPlaceFlowers(";
        printVector(flowerbed);
        cout << ", " << n << ") = " << boolalpha << result
             << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Example 1:
    // flowerbed = [1,0,0,0,1], n = 1 -> true
    runTest(1, {1,0,0,0,1}, 1, true);

    // Example 2:
    // flowerbed = [1,0,0,0,1], n = 2 -> false
    runTest(2, {1,0,0,0,1}, 2, false);

    // Additional tests:
    // All empty, can plant maximum
    runTest(3, {0,0,0,0,0}, 3, true);
    runTest(4, {0,0,0,0,0}, 4, false);

    // Edge cases
    runTest(5, {1,0,1,0,1,0,1}, 0, true);
    runTest(6, {0}, 1, true);
    runTest(7, {0}, 2, false);
    runTest(8,{1,0,1,0,1,0,1},1,false);
    runTest(9,{0,1,0},1, false);
    runTest(10,{0,1,0,1,0,1,0,0},1, true);
    return 0;
}