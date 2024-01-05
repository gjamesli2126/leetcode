#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Define the TimeMap class based on the provided structure
class TimeMap {
private:
    unordered_map<string,map<int,string >> kvmap;//contains map w/ timeStamp:val

public:
    TimeMap() {
    }
    void set(string key, string value, int timestamp) {
        kvmap[key][timestamp]=value;
    }

    string get(string key, int timestamp) {
        if(!kvmap.contains(key)) return "";
        else if(kvmap[key].contains(timestamp)) return kvmap[key][timestamp];

        auto lb= kvmap[key].lower_bound(timestamp);
        if(lb!=kvmap[key].begin()) return (--lb)->second;
        return "";
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](const string& obtained, const string& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        bool correct= obtained == expected;
        string result = correct? GREEN + "PASS" : RED + "FAIL";
        cout << result << RESET << ": " << testName << " - Expected: " << expected << ", Obtained: " << obtained << endl;
    };

    // Initialize TimeMap object
    TimeMap* timeMap = new TimeMap();

    // Test setting and getting values
    timeMap->set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
    test(timeMap->get("foo", 1), "bar", "Test Case 1");  // return "bar"
    test(timeMap->get("foo", 3), "bar", "Test Case 2");  // return "bar", as the only value at or before timestamp 3 is at timestamp 1

    timeMap->set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
    test(timeMap->get("foo", 4), "bar2", "Test Case 3"); // return "bar2"
    test(timeMap->get("foo", 5), "bar2", "Test Case 4"); // return "bar2", as the only value at or before timestamp 5 is at timestamp 4

    // Clean up
    delete timeMap;
    return 0;
}
