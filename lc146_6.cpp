#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class LRUCache {
private:
    unordered_map<int,pair<int,list<int>::iterator>> kv_map;
    list<int> lst;
    int cap;
    list<int>::iterator list_move_to_front(list<int>& lst,list<int>::iterator it){
        int key=*it;
        lst.erase(it);
        lst.emplace_front(key);
        return lst.begin();
    }
    void list_remove(list<int>& lst,list<int>::iterator it){
        lst.erase(it);
    }
    list<int>::iterator list_add_to_front(list<int>& lst,int key){
        lst.emplace_front(key);
        return lst.begin();
    }
public:
    LRUCache(int capacity):cap(capacity) {

    }

    int get(int key) {
        auto mpit=kv_map.find(key);
        if(mpit==kv_map.end()) return -1;
        mpit->second.second=list_move_to_front(lst,mpit->second.second);//update the iter in the map
        return mpit->second.first;
    }

    void put(int key, int value) {
        //put first then check cap
        auto mpit=kv_map.find(key);
        if(mpit==kv_map.end()){
            auto it=list_add_to_front(lst,key);
            kv_map[key]={value,it};
        }else{
            auto it=kv_map[key].second;
            kv_map[key]={value, list_move_to_front(lst,it)};
        }
        if(kv_map.size()>cap){
            //rm the oldest
            auto it=prev(lst.end());
            kv_map.erase(*it);
            lst.pop_back();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int mainTest(){
    auto printCheck = [](const string& name, int got, int expected) {
        if (got == expected) {
            cout << "\033[1;32m"; // green
            cout << "[PASS] ";
        } else {
            cout << "\033[1;31m"; // red
            cout << "[FAIL] ";
        }
        cout << "\033[0m"; // reset
        cout << name
             << " | got = " << got
             << ", expected = " << expected
             << endl;
    };

    LRUCache* cache = new LRUCache(2);

    cache->put(1, 1);       // cache = {1=1}
    cache->put(2, 2);       // cache = {1=1, 2=2}

    int res1 = cache->get(1);  // expect 1
    printCheck("get(1)", res1, 1);

    cache->put(3, 3);       // evicts key 2

    int res2 = cache->get(2);  // expect -1
    printCheck("get(2)", res2, -1);

    cache->put(4, 4);       // evicts key 1

    int res3 = cache->get(1);  // expect -1
    printCheck("get(1)", res3, -1);

    int res4 = cache->get(3);  // expect 3
    printCheck("get(3)", res4, 3);

    int res5 = cache->get(4);  // expect 4
    printCheck("get(4)", res5, 4);

    delete cache;
    return 0;
}