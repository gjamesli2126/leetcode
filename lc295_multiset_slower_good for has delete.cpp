#include <bits/stdc++.h>
#define testMain main
using namespace std;

class MedianFinder{
private:
    multiset<int> left,right;
    void rebalance(multiset<int>& smaller,multiset<int>& larger){
        //rebalance with the length
        //left multiset can be: equal or one larger then the right one
        if(smaller.size()>larger.size()+1) {
            larger.insert(*smaller.rbegin());
            smaller.erase(prev(smaller.end()));
        }else if(smaller.size()<larger.size()){
            smaller.insert(*larger.begin());
            larger.erase(larger.begin());
        }
        //rebalance with the number
        //no need as we always add to the left multiset
    }
public:
    MedianFinder(){

    }
    void addNum(int n){
        if(left.empty() || n<=*left.rbegin()) left.insert(n);
        else right.insert(n);
        rebalance(left,right);
    }
    double findMedian(){
        if(left.size()==right.size()) return (*left.rbegin()+*right.begin())/2.0;
        return *left.rbegin();
    }
};

void runMedianTest(int testNum, MedianFinder& mf, double expected) {
    double median = mf.findMedian();
    if (fabs(median - expected) < 1e-5) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: median = " << fixed << setprecision(5) << median
             << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: median = " << fixed << setprecision(5) << median
             << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Sequence:
    // ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
    // [[], [1],       [2],       [],           [3],       []      ]
    // Expected outputs: [null, null, null, 1.5, null, 2.0]

    MedianFinder mf;
    // addNum(1)
    mf.addNum(1);
    // addNum(2)
    mf.addNum(2);
    // findMedian() -> 1.5
    runMedianTest(1, mf, 1.5);
    // addNum(3)
    mf.addNum(3);
    // findMedian() -> 2.0
    runMedianTest(2, mf, 2.0);

    return 0;
}