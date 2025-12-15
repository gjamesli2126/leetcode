#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class SnapshotArray{
    vector<int> v;
    int snap_id=0;
    vector<map<int,int>> ind_snap_val;
public:
    SnapshotArray(int length):v(length,0),ind_snap_val(length){}

    void set(int index, int val){
        if(index>=v.size() || v[index]==val) return;
        v[index]=val;
        ind_snap_val[index][snap_id]=val;
    }

    int snap(){
        return snap_id++;
    }

    int get(int index, int snap_id){
        if(snap_id>=this->snap_id) return -1;
        auto& snap_val=ind_snap_val[index];
        auto it=snap_val.upper_bound(snap_id);//從誰開始會超過
        if(it==snap_val.begin())return 0;
        --it;
        return it->second;//->first is key, ->second is value
    }
};

void printResult(int result, int expected){
    if (result == expected){
        cout << "\033[1;32mPass\033[0m Expected: " << expected << endl;
    }
    else{
        cout << "\033[1;31mFail\033[0m Expected: " << expected << " Got: " << result << endl;
    }
}

int mainTest(){
    cout << "Test 1" << endl;
    SnapshotArray snapshotArr(3);
    snapshotArr.set(0, 5);
    int snap_id_1 = snapshotArr.snap();
    snapshotArr.set(0, 6);
    int result1 = snapshotArr.get(0, 0);
    printResult(result1, 5);

    cout << "Test 2" << endl;
    SnapshotArray snapshotArr2(2);
    snapshotArr2.set(1, 7);
    int snap_id_2 = snapshotArr2.snap();
    snapshotArr2.set(1, 8);
    int result2 = snapshotArr2.get(1, snap_id_2);
    printResult(result2, 7);

    cout << "Test 3" << endl;
    SnapshotArray snapshotArr3(4);
    snapshotArr3.set(0, 1);
    snapshotArr3.set(1, 2);
    int snap_id_3 = snapshotArr3.snap();
    snapshotArr3.set(1, 3);
    int result3 = snapshotArr3.get(1, snap_id_3);
    printResult(result3, 2);
    return 0;
}