#define mainTest main
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        size_t num=edges.size();
        vector<int> parents(num+1);
        iota(parents.begin()+1,parents.end(),1);//slef's parent==self
        for(const vector<int>& edge:edges){
            int firstNode=edge[0];
            int secondNode=edge[1];
            while(firstNode!=parents[firstNode]) firstNode=parents[firstNode];
            while(secondNode!=parents[secondNode]) secondNode=parents[secondNode];
            if(firstNode==secondNode) return edge;
            else parents[secondNode]=firstNode;
        }
        return {};
    }
};

int mainTest() {
    Solution obj1;
    vector<vector<int>> edges1 = {{1,2},{1,3},{2,3}};
    vector<int> expected1 = {2,3};
    vector<int> output1 = obj1.findRedundantConnection(edges1);
    cout << "Expected: [" << expected1[0] << "," << expected1[1] << "], Output: [" << output1[0] << "," << output1[1] << "]" << endl;
    if (output1 == expected1) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }

    Solution obj2;
    vector<vector<int>> edges2 = {{1,2},{2,3},{3,4},{1,4},{1,5}};
    vector<int> expected2 = {1,4};
    vector<int> output2 = obj2.findRedundantConnection(edges2);
    cout << "Expected: [" << expected2[0] << "," << expected2[1] << "], Output: [" << output2[0] << "," << output2[1] << "]" << endl;
    if (output2 == expected2) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }

    return 0;
}
