#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class LRUCache {
    int capacity;
    unordered_map<int,list<pair<int,int>>::iterator> mp;
    list<pair<int,int>> recentList;
public:
    LRUCache(int capacity):capacity(capacity) {}

    int get(int key) {
        auto it=mp.find(key);
        if(it==mp.end()) return -1;
        //update the recent list
        recentList.splice(recentList.begin(),recentList,it->second);
        return it->second->second;//it->second is the iter to the list
    }

    void put(int key, int value) {
        auto it=mp.find(key);
        //case1 k exist
        if(it!=mp.end()){
            it->second->second=value;
            recentList.splice(recentList.begin(),recentList,it->second);
        }
        //case 2 k does not exist
        else{
            if(mp.size()==capacity){
                int leastRecentVal=recentList.rbegin()->first;
                mp.erase(leastRecentVal);
                recentList.pop_back();
            }
            recentList.emplace_front(key,value);
            mp[key]=recentList.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
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