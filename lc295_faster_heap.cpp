#include <bits/stdc++.h>
#define testMain main
using namespace std;

class MedianFinder{
private:
private:
    //left: max heap
    //right: minheap
    priority_queue<int> left_maxheap;
    priority_queue<int,vector<int>,greater<int>> right_minheap;
public:
    MedianFinder(){

    }
    void addNum(int n){
        if(left_maxheap.empty() || left_maxheap.top()>=n) left_maxheap.push(n);
        else right_minheap.push(n);
        //if size must be ctrled at: left_size=right_size (+1)
        //sp this call: rebalance
        if(left_maxheap.size()>right_minheap.size()+1){
            right_minheap.push(left_maxheap.top());
            left_maxheap.pop();
        }else if(left_maxheap.size()<right_minheap.size()){
            left_maxheap.push(right_minheap.top());
            right_minheap.pop();
        }
    }
    double findMedian(){
        if(left_maxheap.size()== right_minheap.size()) return (left_maxheap.top()+right_minheap.top())/2.0;
        else return left_maxheap.top();
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