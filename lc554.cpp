#define mainTest main
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int,int> smCountmap;
        for(const vector<int>& roll:wall){
            int sum=0;
            for(int i=0;i<roll.size()-1;++i){
                sum+=roll[i];
                ++smCountmap[sum];
            }
        }
        if(smCountmap.empty()) return wall.size();
        auto maxCount= max_element(smCountmap.begin(),smCountmap.end(),[](const pair<int,int>& a,const pair<int,int>& b){
            return a.second<b.second;
        });

        return wall.size()-maxCount->second;
    }
};

int mainTest() {
    Solution obj1;
    vector<vector<int>> wall1 = {{1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1}};
    int expected1 = 2;
    int output1 = obj1.leastBricks(wall1);
    cout << "Expected: " << expected1 << ", Output: " << output1 << endl;
    if (output1 == expected1) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }

    Solution obj2;
    vector<vector<int>> wall2 = {{1},{1},{1}};
    int expected2 = 3;
    int output2 = obj2.leastBricks(wall2);
    cout << "Expected: " << expected2 << ", Output: " << output2 << endl;
    if (output2 == expected2) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }

    return 0;
}
