#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class LRUCache {
private:
    unordered_map<int,list<pair<int,int>>::iterator> mp;//key,<k,v>_ptr
    list<pair<int,int>> recentlst;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
    }

    int get(int key) {
        auto it=mp.find(key);
        if(it==mp.end()) return -1;
//        auto it=find(recentlst.begin(),recentlst.end(), make_pair(key,mp[key]));

        recentlst.splice(recentlst.begin(),recentlst,it->second);
        return it->second->second;//it->second means *value, the value is a tuple, the second of the tuple is the True_value
    }

    void put(int key, int value) {
        auto it=mp.find(key);
        if(it!=mp.end()){
            //case 1: key exist
            mp[key]->second=value;//mp[key] is a iterator
            recentlst.splice(recentlst.begin(),recentlst,mp[key]);
        }else{
            //case 2: key does not exist
            if(mp.size()==capacity){
                int last_key=recentlst.back().first;
                mp.erase(last_key);
                recentlst.pop_back();
            }
            recentlst.emplace_front(key,value);
            mp[key]=recentlst.begin();//begin() is an iterator, .front() is the value!!
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