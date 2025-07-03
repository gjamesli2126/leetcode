#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    vector<int> rec_loc_stInd;
    int sum;
public:
    Solution(vector<int>& w){
        int ws=w.size();
        rec_loc_stInd.resize(ws);
        int this_ind=0;
        for(int i=0;i<ws;i++){
            rec_loc_stInd[i]=this_ind;
            this_ind+=w[i];//此 this 到 下一個 this
        }
        sum=this_ind;
    }
    int pickIndex() {
        //choose a target
        int target=rand()%sum;
        //find the attribute
        //“Find the largest start‐index ≤ my random pick.” So it is upper_bound && inclusive
        int l=0,r=rec_loc_stInd.size(),mid;
        while(l<r){
            mid=l+(r-l)/2;
            if(rec_loc_stInd[mid]<=target) l=mid+1;
            else r=mid;
        }
        return l-1;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
// Helper function to run a test case for pickIndex.
// expected: expected probabilities for each index (e.g., {0.25, 0.75})
// iterations: number of times pickIndex is called to estimate frequency
// tol: tolerance for deviation from expected probabilities.
void runTest(int testNum, vector<int> w, vector<double> expected, int iterations = 10000, double tol = 0.05) {
    // Instantiate the solution with the given weight vector.
    Solution sol(w);
    vector<int> count(w.size(), 0);

    // Run pickIndex() for a number of iterations and count the frequency of each index.
    for (int i = 0; i < iterations; i++) {
        int idx = sol.pickIndex();
        if (idx < 0 || idx >= w.size()) {
            cout << "\033[1;31mTest Case " << testNum
                 << " Failed: pickIndex() returned invalid index " << idx
                 << "\033[0m" << endl;
            return;
        }
        count[idx]++;
    }

    // Compare the observed frequencies with the expected probabilities.
    bool pass = true;
    for (int i = 0; i < w.size(); i++) {
        double freq = static_cast<double>(count[i]) / iterations;
        if (fabs(freq - expected[i]) > tol) {
            pass = false;
        }
    }

    if (pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: Frequency distribution within tolerance.\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: Frequency distribution out of tolerance.\033[0m" << endl;
        cout << "Observed Frequencies: ";
        for (int i = 0; i < w.size(); i++) {
            cout << fixed << setprecision(4) << static_cast<double>(count[i]) / iterations;
            if (i < w.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

int testMain(){
    // Test Case 1: Single element array; should always return index 0.
    // Expected probability: [1.0]
    runTest(1, {1}, {1.0});

    // Test Case 2: Weights [1, 3]
    // Expected probabilities: index 0 -> 1/(1+3)=0.25, index 1 -> 3/(1+3)=0.75
    runTest(2, {1, 3}, {0.25, 0.75});

    // Test Case 3: Weights [2, 5, 3]
    // Expected probabilities: index 0 -> 0.2, index 1 -> 0.5, index 2 -> 0.3
    runTest(3, {2, 5, 3}, {0.2, 0.5, 0.3});
//    runTest(4,{10,7,8,10},{})

    return 0;
}