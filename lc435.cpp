#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution{
private:
    static bool compare_second(const vector<int>& a,const vector<int>& b){
        return a[1]<b[1];//return ture -> a appears BEFORE b
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals){
        //sort with End time
        sort(intervals.begin(),intervals.end(), compare_second);
        int latest_end=INT_MIN;
        int counter=0;
        for(vector<int>& v:intervals){
            int start_time=v[0];
            int end_time=v[1];
            if(start_time>=latest_end) latest_end=end_time;
            else counter++;
        }
        return counter;
    }
};
/*
 * Imagine you’re booking meetings in a conference room:
	•	You want to fit as many meetings as possible.
	•	If you always pick the meeting that ends earliest, you free the room sooner → more total meetings fit.
	•	If you pick the one that starts earliest, you might pick a 3-hour meeting and block five 30-minute ones.
 * */
void printResult(int result, int expected){
    if (result == expected){
        cout << "\033[1;32mPass\033[0m Expected: " << expected << endl;
    }
    else{
        cout << "\033[1;31mFail\033[0m Expected: " << expected << " Got: " << result << endl;
    }
}

int mainTest(){
    Solution sol;

    cout << "Test 1" << endl;
    vector<vector<int>> intervals1 = {{1,2},{2,3},{3,4},{1,3}};
    int expected1 = 1;
    printResult(sol.eraseOverlapIntervals(intervals1), expected1);

    cout << "Test 2" << endl;
    vector<vector<int>> intervals2 = {{1,2},{1,2},{1,2}};
    int expected2 = 2;
    printResult(sol.eraseOverlapIntervals(intervals2), expected2);

    cout << "Test 3" << endl;
    vector<vector<int>> intervals3 = {{1,2},{2,3}};
    int expected3 = 0;
    printResult(sol.eraseOverlapIntervals(intervals3), expected3);

    cout << "Test 4" << endl;
    vector<vector<int>> intervals4 = {{-10,-8},{-8,-6},{-6,-4},{-5,-3}};
    int expected4 = 1; // remove one overlap (-6,-4) overlaps with (-5,-3)
    printResult(sol.eraseOverlapIntervals(intervals4), expected4);

    cout << "Test 5" << endl;
    vector<vector<int>> intervals5 = {{1,100},{11,22},{1,11},{2,12}};
    int expected5 = 2;
    printResult(sol.eraseOverlapIntervals(intervals5), expected5);

    return 0;
}