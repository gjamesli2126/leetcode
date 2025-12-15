#include <bits/stdc++.h>
#define mainTest main
using namespace std;
class LFUCache {
private:
    struct Node{
        int value;
        unsigned freq;
        list<int>::iterator lru_it;
    };
    unordered_map<int,Node> kv;
    unordered_map<int,list<int>> freq_lruKey;
    int cap;
    int minFreq;
    void freq_inc(int key){
        auto& [val,freq,lru_it]=kv[key];
        freq_lruKey[freq].erase(lru_it);
        if(freq_lruKey[freq].empty()) {
            freq_lruKey.erase(freq);
            if(freq==minFreq) minFreq++;
        }
        freq++;
        freq_lruKey[freq].push_front(key);
        lru_it=freq_lruKey[freq].begin();
    }
    void remove_least_freq_lru(){
        auto& lru_lst=freq_lruKey[minFreq];
        int key=lru_lst.back();
        lru_lst.pop_back();
        if(lru_lst.empty()) freq_lruKey.erase(minFreq);
        kv.erase(key);
    }
    list<int>::iterator insert_freq_lruKey(int freq,int key){
        freq_lruKey[freq].push_front(key);
        return freq_lruKey[freq].begin();
    }
public:
    LFUCache(int capacity):cap(capacity),minFreq(0) {
    }

    int get(int key) {
        auto mpit=kv.find(key);
        if(mpit==kv.end()) return -1;
        freq_inc(key);
        return mpit->second.value;
    }

    void put(int key, int value) {
        if(cap<=0) return;
        auto mpit=kv.find(key);
        //existing key
        if(mpit!=kv.end()){
            auto& [val,freq,lru_it]=mpit->second;
            val=value;
            freq_inc(key);
        }else{
        //new key
            if(cap==kv.size()) remove_least_freq_lru();
            kv[key]={value,1, insert_freq_lruKey(1,key)};
            minFreq=1;
        }

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int mainTest() {
    auto printCheck = [](string name, int got, int expected) {
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

    LFUCache* lfu = new LFUCache(2);

    lfu->put(1, 1);
    lfu->put(2, 2);

    printCheck("get(1)", lfu->get(1), 1);

    lfu->put(3, 3);   // evict key 2

    printCheck("get(2)", lfu->get(2), -1);
    printCheck("get(3)", lfu->get(3), 3);

    lfu->put(4, 4);   // evict key 1 (tie, LRU)

    printCheck("get(1)", lfu->get(1), -1);
    printCheck("get(3)", lfu->get(3), 3);
    printCheck("get(4)", lfu->get(4), 4);

    delete lfu;
    return 0;
}