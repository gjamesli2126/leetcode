#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    void printBitset(const auto& canMake){
        for(int i=0;i<canMake.size();++i){
            if(canMake.test(i)) cout<<i<<" ";
        }
        cout<<endl;
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        int totalSum = accumulate(stones.begin(), stones.end(), 0);
        int target = totalSum / 2;
        bitset<1501> canMake;  // Stores which sums can be made. 1501 to include 0 to 1500.// target=100*30/2
        canMake.set(0);  // You can always make a sum of 0.

        for (int stone : stones) {
            // Shift the bitset by 'stone' and OR it with itself. This represents adding 'stone' to all previously possible sums.
            canMake |= canMake << stone;
        }

        // Find the closest possible sum to half of the total sum.
        for (int sum = target; sum >= 0; --sum) { // 因為我是從target(totalSum/2)向下減，因此可以保證 sum不到totalSum的一半 因此可以totalSum-2sum
            if (canMake.test(sum)) {
                return totalSum - 2 * sum;  // The difference between the two partitions.
            }
        }
        return 87426;  // If no sums are possible, return the total sum (this should not happen with the given constraints).
    }
};


int mainTest() {
    Solution solution;
    vector<vector<int>> testCases = {
            {2,7,4,1,8,1},   // Example 1
            {31,26,33,21,40} // Example 2
    };

    vector<int> expectedOutputs = {1, 5}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.lastStoneWeightII(testCases[i]);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Input: stones = [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j];
            if (j < testCases[i].size() - 1) cout << ", ";
        }
        cout << "], Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
