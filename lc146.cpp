#include<bits/stdc++.h>
using namespace std;
#define mainTest main
struct Node{
    int val=-1;
    int key=-1;
    Node *prev= nullptr;
    Node *next= nullptr;
};

class LRUCache {
private:
    int capacity;
    unordered_map<int,Node*> kvmap;
    Node *least,*most;

public:
    LRUCache(int capacity) {
        this->capacity=capacity;
        least=new Node();
        most=new Node();
        least->next=most;
        most->prev=least;
    }

    int get(int key) {
        // Return the value of the key if the key exists, otherwise return -1
        if(!kvmap.contains(key)) return -1;
        remove(kvmap[key]);
        insert(most->prev,kvmap[key],most);
        return kvmap[key]->val;
    }
    void insert(Node *left,Node *target,Node *right){
        left->next=target;
        target->prev=left;
        target->next=right;
        right->prev=target;
    }
    void remove(Node *node){
        Node *left=node->prev,*right=node->next;
        left->next=right;
        right->prev=left;
    }
    void destroy(Node *node){
        remove(node);
        delete node;
    }
    void put(int key, int value) {
        if(kvmap.contains(key)){
            kvmap[key]->val=value;
            remove(kvmap[key]);
        }
        else if(kvmap.size()<capacity){
            Node *node= new Node{.val=value,.key=key};
            kvmap[key]=node;
        }
        else{
            Node *node= new Node{.val=value,.key=key};
            kvmap[key]=node;
            kvmap.erase(least->next->key);
            destroy(least->next);
        }
        insert(most->prev,kvmap[key],most);
    }
};

int mainTest() {
    vector<string> commands = {"LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"};
    vector<vector<int>> inputs = {{3},{1,1},{2,2},{3,3},{4,4},{4},{3},{2},{1},{5,5},{1},{2},{3},{4},{5}};
    vector<int> expected = {0,0,0,0,0,4,3,2,-1,0,-1,2,3,-1,5}; // The first three are null (0 for representation)

    LRUCache* cache = nullptr;

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i] == "LRUCache") {
            cache = new LRUCache(inputs[i][0]);
            cout << "Created an LRUCache with capacity: " << inputs[i][0] << endl;
        } else if (commands[i] == "put") {
            cache->put(inputs[i][0], inputs[i][1]);
            cout << "Put (" << inputs[i][0] << "," << inputs[i][1] << ") into the cache." << endl;
        } else if (commands[i] == "get") {
            int val = cache->get(inputs[i][0]);
            cout << "Get key " << inputs[i][0] << " : " << val << " | Expected: " << expected[i] << endl;
        }
    }

    delete cache; // Cleanup
    return 0;
}
