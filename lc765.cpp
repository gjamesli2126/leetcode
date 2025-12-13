#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    inline int findCpInd(int ppl){
        return ppl>>1;//ppl/2;
    }
    vector<int> parent;
    vector<int> rankv;
    int tree_num;
    int find_root(int e){
        if(parent[e]!=e) parent[e]=find_root(parent[e]);
        return parent[e];
    }
    void unite(int a,int b){
        int root_a=find_root(a);
        int root_b=find_root(b);
        if(root_a==root_b) return;//no need to find
        --tree_num;//an element merged into 1 tree;
        //compress
        if(rankv[root_a]<rankv[root_b]) parent[root_a]=root_b;
        else if(rankv[root_a]>rankv[root_b]) parent[root_b]=root_a;
        else {
            parent[root_b]=root_a;
            rankv[root_a]++;//any ++   Rank 越高越接近root
        }
    }
public:
    int minSwapsCouples(vector<int>& row) {
        //give couples groups
        int grpNum=row.size()/2;
        //init tree_num
        tree_num=grpNum;
        parent.resize(grpNum,0);
        rankv.resize(grpNum,0);
        //init parent
        for(int i=0;i<grpNum;i++) parent[i]=i;
        for(int i=0;i<grpNum;i++){
            int cpGrp1= findCpInd(row[2*i]);
            int cpGrp2= findCpInd(row[2*i+1]);
            unite(cpGrp1,cpGrp2);
        }
        return grpNum-tree_num;//vertices - cycle num
    }
};

// === Utility ===
void printResult(int result, int expected) {
    if (result == expected) {
        cout << "\033[1;32mPass\033[0m ";
    } else {
        cout << "\033[1;31mFail\033[0m ";
    }
    cout << "Output: " << result << " Expected: " << expected << endl;
}

int mainTest() {
    Solution sol;

    // Test Case 1
    vector<int> row1 = {0, 2, 1, 3};
    int expected1 = 1;
    printResult(sol.minSwapsCouples(row1), expected1);

    // Test Case 2
    vector<int> row2 = {3, 2, 0, 1};
    int expected2 = 0;
    printResult(sol.minSwapsCouples(row2), expected2);

    // Test Case 3
    vector<int> row3 = {1, 3, 4, 0, 2, 5};
    int expected3 = 2;
    printResult(sol.minSwapsCouples(row3), expected3);

    return 0;
}