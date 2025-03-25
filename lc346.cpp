#include <bits/stdc++.h>
#define testMain main
using namespace std;

class MovingAverage {
    int size;
    vector<int> circular_vec;
    int ptr;
    int alloc;
    double res;
public:
    MovingAverage(int size0):size(size0),ptr(0),alloc(0),res(0){
        circular_vec.resize(size);
    }

    double next(int val) {

        int old_num=circular_vec[ptr];
        circular_vec[ptr]=val;
        ptr=(ptr+1)%size;
        res=res*alloc-old_num+val;
        if(alloc<size) alloc++;
        res/=alloc;
        return res;
    }
};

// Helper function to compare doubles with a tolerance.
bool areEqual(double a, double b, double tol = 1e-5) {
    return fabs(a - b) < tol;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, int windowSize, vector<int> stream, vector<double> expected) {
    MovingAverage ma(windowSize);
    vector<double> outputs;
    for (int val : stream) {
        outputs.push_back(ma.next(val));
    }
    bool pass = (outputs.size() == expected.size());
    for (size_t i = 0; i < outputs.size() && pass; i++) {
        if (!areEqual(outputs[i], expected[i])) {
            pass = false;
        }
    }
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        for (auto d: outputs) cout << d << " ";
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Got ";
        for (auto d: outputs) cout << d << " ";
        cout << "Expected ";
        for (auto d: expected) cout << d << " ";
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: 
    // MovingAverage movingAverage = new MovingAverage(3);
    // movingAverage.next(1); // should return 1.0 = 1 / 1
    // movingAverage.next(10); // should return 5.5 = (1 + 10) / 2
    // movingAverage.next(3); // should return 4.66667 = (1 + 10 + 3) / 3
    // movingAverage.next(5); // should return 6.0 = (10 + 3 + 5) / 3
    vector<int> stream1 = {1, 10, 3, 5};
    vector<double> expected1 = {1.0, 5.5, 4.66667, 6.0};
    runTest(1, 3, stream1, expected1);

    return 0;
}