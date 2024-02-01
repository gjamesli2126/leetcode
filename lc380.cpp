#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class RandomizedSet {
private:
    unordered_map<int,int> nimap;//num->index
    vector<int> v;//provide random access
public:
    RandomizedSet(){}

    bool insert(int val) {
        if(nimap.contains(val)) return false;
        v.emplace_back(val);
        nimap[val]=static_cast<int>(v.size())-1;
        return true;
    }

    bool remove(int val) {
        if(!nimap.contains(val)) return false;
        v[nimap[val]]=v.back();
        nimap[v.back()]=nimap[val];
        nimap.erase(val);
        v.pop_back();
        return true;
    }

    int getRandom() {
//        for(const int i:v) cout<<i<<" ";
//        cout<<endl;
        return v[rand()%static_cast<int>(v.size())];
    }
};

int mainTest(){
    vector<string> operations = {"RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"};
    vector<vector<int>> values = {{}, {1}, {2}, {2}, {}, {1}, {2}, {}};
    vector<bool> expectedBoolResults = {true, false, true, true, false};
    vector<int> expectedIntResults = {2, 2}; // These are expected but may vary due to getRandom's nature
    vector<int> actualIntResults;
    vector<bool> actualBoolResults;

    RandomizedSet randomizedSet; // Initializes the RandomizedSet object.
    for(int i = 1; i < operations.size(); i++){
        if(operations[i] == "insert"){
            actualBoolResults.push_back(randomizedSet.insert(values[i][0]));
        }else if(operations[i] == "remove"){
            actualBoolResults.push_back(randomizedSet.remove(values[i][0]));
        }else if(operations[i] == "getRandom"){
            actualIntResults.push_back(randomizedSet.getRandom());
        }
    }

    bool allPass = true;
    for(int i = 0; i < expectedBoolResults.size(); i++){
        if(actualBoolResults[i] != expectedBoolResults[i]){
            cout << "\x1B[31mfail\033[0m Expected: " << expectedBoolResults[i] << ", Got: " << actualBoolResults[i] << endl;
            allPass = false;
        }else{
            cout << "\x1B[32mpass\033[0m Expected: " << expectedBoolResults[i] << ", Got: " << actualBoolResults[i] << endl;
        }
    }

    // Checking if the returned values from getRandom are within the expected set of elements.
    for(int val : actualIntResults){
        if(val != 2){ // Since 2 is expected to be the only element in the set at this point.
            cout << "\x1B[31mfail\033[0m Expected: 2, Got: " << val << endl;
            allPass = false;
        }else{
            cout << "\x1B[32mpass\033[0m Expected: 2, Got: " << val << endl;
        }
    }

    if(allPass){
        cout << "\x1B[34mAll Tests Passed (5/5)\033[0m" << endl;
    }else{
        cout << "\x1B[33mSome Tests Failed\033[0m" << endl;
    }

    return 0;
}
