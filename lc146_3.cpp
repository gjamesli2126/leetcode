#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class LRUCache {
private:
    list<pair<int,int>> dblist;//(key,val)
    unordered_map<int, list<pair<int,int>>::iterator> mp;
    int capacity;
public:
    LRUCache(int capacity):capacity(capacity) {
        //no need
    }

    int get(int key) {
        if(!mp.contains(key)) return -1;
        auto it=mp[key];

        dblist.splice(dblist.begin(),dblist, it);
        return it->second;
    }

    void put(int key, int value) {
        //case 1 exist
        if(mp.contains(key)){
            dblist.emplace_front(key,value);
            auto old_itmp=mp[key];
            mp[key]=dblist.begin();
            dblist.erase(old_itmp);
        }
        //case 2 does not exist
        else{
            dblist.emplace_front(key,value);
            mp[key]=dblist.begin();
            if(dblist.size()>capacity){
                mp.erase(dblist.back().first);
                dblist.pop_back();
            }
        }

    }
};

int mainTest(){
    // Example test case:
    // LRUCache cache = new LRUCache(2);
    // cache.put(1, 1);       // cache is {1=1}
    // cache.put(2, 2);       // cache is {1=1, 2=2}
    // cache.get(1);          // returns 1
    // cache.put(3, 3);       // evicts key 2, cache becomes {1=1, 3=3}
    // cache.get(2);          // returns -1 (not found)
    // cache.put(4, 4);       // evicts key 1, cache becomes {3=3, 4=4}
    // cache.get(1);          // returns -1 (not found)
    // cache.get(3);          // returns 3
    // cache.get(4);          // returns 4

    LRUCache* cache = new LRUCache(2);
    cache->put(1, 1);       // cache = {1=1}
    cache->put(2, 2);       // cache = {1=1, 2=2}
    int res1 = cache->get(1);  // should return 1
    cache->put(3, 3);       // evicts key 2, cache = {1=1, 3=3}
    int res2 = cache->get(2);  // should return -1
    cache->put(4, 4);       // evicts key 1, cache = {3=3, 4=4}
    int res3 = cache->get(1);  // should return -1
    int res4 = cache->get(3);  // should return 3
    int res5 = cache->get(4);  // should return 4

    cout << "Test Outputs:" << endl;
    cout << "get(1): " << res1 << endl;
    cout << "get(2): " << res2 << endl;
    cout << "get(1): " << res3 << endl;
    cout << "get(3): " << res4 << endl;
    cout << "get(4): " << res5 << endl;

    // Expected outputs:
    // get(1) -> 1
    // get(2) -> -1
    // get(1) -> -1
    // get(3) -> 3
    // get(4) -> 4

    delete cache;
    return 0;
}