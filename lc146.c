#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h> // For sleep (optional visual effect)

// 定義 mainTest
#define mainTest main

// 顏色與格式定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE  "\033[0;34m"
#define COLOR_RESET "\033[0m"

// ==========================================
// 資料結構定義 (Data Structures)
// ==========================================

// 雙向鏈結串列節點
typedef struct DNode {
    unsigned key;//反向查詢專用
    int val;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// LRU Cache 主結構
typedef struct {
    int cap;
    DNode* arr[10001];
    DNode* dumbHead;
    DNode* dumbTail;
} LRUCache;

// ==========================================
// TODO: 請在此處實作你的解答
// ==========================================

LRUCache* lRUCacheCreate(int capacity) {
    // TODO: Initialize struct, dummy nodes, connect head/tail
    LRUCache* lruCache=(LRUCache*) calloc(1,sizeof(LRUCache));
    //and calloc automatically set the arr to all NULLs
    lruCache->cap=capacity;
    lruCache->dumbHead=(DNode*)malloc(sizeof(DNode));
    lruCache->dumbTail=(DNode*)malloc(sizeof(DNode));
    lruCache->dumbHead->prev=NULL;
    lruCache->dumbHead->next=lruCache->dumbTail;

    lruCache->dumbTail->prev=lruCache->dumbHead;
    lruCache->dumbTail->next=NULL;
    return lruCache;
}
void insert_to_head(LRUCache* obj, DNode* node){
    DNode* dumbHead=obj->dumbHead;
    DNode* org_head=dumbHead->next;
    node->next=org_head;
    org_head->prev=node;

    dumbHead->next=node;
    node->prev=dumbHead;
}
void move_to_head(LRUCache* obj,DNode* node){
    DNode* prev=node->prev;
    DNode* next=node->next;
    prev->next=next;
    next->prev=prev;
    insert_to_head(obj,node);
}

void remove_tail(LRUCache* obj){
    DNode* dumbTail=obj->dumbTail;
    DNode* last=dumbTail->prev;
    if(last==obj->dumbHead) return;
    last->prev->next=dumbTail;
    dumbTail->prev=last->prev;
    obj->arr[last->key]=NULL;//反查用在此
    free(last);
}

int lRUCacheGet(LRUCache* obj, int key) {
    // TODO: Check map -> Move to head -> Return value
    if(!obj->arr[key]) return -1;
    DNode* node=obj->arr[key];
    move_to_head(obj,node);
    return node->val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    // TODO: Update existing or Insert new (Evict if full)
    DNode* node=obj->arr[key];
    //if exist
    if(node){
        node->val=value;
        move_to_head(obj,node);
    }
    else{
        //if not exist
        node=(DNode*)malloc(sizeof(DNode));//the stack ptr is now pointing to a new heap memory
        node->key=key;
        node->val=value;
        insert_to_head(obj,node);
        if(obj->cap>0) --obj->cap;
        else remove_tail(obj);
        obj->arr[key]=node;//now is obj->arr[key] is pointing to the heap memory
    }
}

void lRUCacheFree(LRUCache* obj) {
    // TODO: Free all nodes and the struct
    DNode* node=obj->dumbHead;
    while(node){
        DNode* next=node->next;
        free(node);
        node=next;
    }//So all of the used elements in the arr are freed.
    free(obj);
}

// ==========================================
// --- 測試輔助工具 (Test Helpers) ---
// ==========================================

void printProgressBar(int current, int total) {
    const int barWidth = 50;
    float progress = (float)current / total;
    int pos = barWidth * progress;

    printf("\r" COLOR_BLUE "Stress Test: [" COLOR_RESET);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf(COLOR_BLUE "] %d%%" COLOR_RESET, (int)(progress * 100.0));
    fflush(stdout); // 強制刷新緩衝區，讓進度條動起來
}

void assertInt(int result, int expected, const char* msg) {
    if (result == expected) {
        // printf("  [OK] %s\n", msg); // Optional: verbose
    } else {
        printf("\n  %s[FAIL] %s: Got %d, Expected %d%s\n", COLOR_RED, msg, result, expected, COLOR_RESET);
        exit(1); // Fail fast
    }
}

// ==========================================
// --- 測試案例 (Test Cases) ---
// ==========================================

void runExample1() {
    printf("\n%s=== Running Example 1 (Standard) ===%s\n", COLOR_YELLOW, COLOR_RESET);
    /*
     Explanation:
     LRUCache lRUCache = new LRUCache(2);
     lRUCache.put(1, 1); // cache is {1=1}
     lRUCache.put(2, 2); // cache is {1=1, 2=2}
     lRUCache.get(1);    // return 1
     lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
     lRUCache.get(2);    // returns -1 (not found)
     lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
     lRUCache.get(1);    // return -1 (not found)
     lRUCache.get(3);    // return 3
     lRUCache.get(4);    // return 4
    */

    LRUCache* obj = lRUCacheCreate(2);
    if (!obj) { printf("Create failed (returned NULL)\n"); return; }

    lRUCachePut(obj, 1, 1);
    lRUCachePut(obj, 2, 2);

    assertInt(lRUCacheGet(obj, 1), 1, "Get(1) after putting 1,2"); // 1 is now MRU

    lRUCachePut(obj, 3, 3); // Evicts 2 (LRU)

    assertInt(lRUCacheGet(obj, 2), -1, "Get(2) should be evicted");

    lRUCachePut(obj, 4, 4); // Evicts 1 (LRU)

    assertInt(lRUCacheGet(obj, 1), -1, "Get(1) should be evicted");
    assertInt(lRUCacheGet(obj, 3), 3, "Get(3) should be present");
    assertInt(lRUCacheGet(obj, 4), 4, "Get(4) should be present");

    lRUCacheFree(obj);
    printf("%sPASS: Example 1%s\n", COLOR_GREEN, COLOR_RESET);
}

void runCornerCases() {
    printf("\n%s=== Running Corner Cases ===%s\n", COLOR_YELLOW, COLOR_RESET);

    // Case 1: Capacity 1 (Smallest capacity)
    // Put A, Put B -> A evicted.
    printf("1. Testing Capacity 1...\n");
    LRUCache* obj1 = lRUCacheCreate(1);
    lRUCachePut(obj1, 10, 100);
    lRUCachePut(obj1, 20, 200); // 10 evicted
    assertInt(lRUCacheGet(obj1, 10), -1, "Capacity 1: 10 should be evicted");
    assertInt(lRUCacheGet(obj1, 20), 200, "Capacity 1: 20 should exist");
    lRUCacheFree(obj1);

    // Case 2: Update Existing Key
    // Put A(100), Put A(200) -> Value becomes 200, A becomes MRU.
    printf("2. Testing Update Existing Key...\n");
    LRUCache* obj2 = lRUCacheCreate(2);
    lRUCachePut(obj2, 1, 100);
    lRUCachePut(obj2, 2, 200);
    lRUCachePut(obj2, 1, 111); // Update 1. 1 is now MRU. 2 is LRU.
    lRUCachePut(obj2, 3, 300); // Should evict 2.

    assertInt(lRUCacheGet(obj2, 1), 111, "Update: Key 1 value incorrect");
    assertInt(lRUCacheGet(obj2, 2), -1, "Update: Key 2 should be evicted");
    assertInt(lRUCacheGet(obj2, 3), 300, "Update: Key 3 should exist");
    lRUCacheFree(obj2);

    // Case 3: Zero Capacity (Edge case - though constraint says >= 1, good to handle safely)
    // Usually standard impl handles this gracefully or crashes if not careful.
    // Given constraints say 1 <= capacity, we skip 0 test to avoid confusing standard solutions.

    printf("%sPASS: Corner Cases%s\n", COLOR_GREEN, COLOR_RESET);
}

void runBigDataTest() {
    printf("\n%s=== Running Big Data Stress Test ===%s\n", COLOR_YELLOW, COLOR_RESET);

    int capacity = 1000;
    int ops = INT32_MAX; // Constraints: at most 2*10^5 calls
    LRUCache* obj = lRUCacheCreate(capacity);

    printf("Capacity: %d, Operations: %d\n", capacity, ops);

    // Phase 1: Fill Cache (0 to 999)
    // Phase 2: Access them to mix things up
    // Phase 3: Overflow (1000 to 1999) -> Should evict 0 to 999

    for (int i = 0; i < ops; i++) {
        if (i % 1000 == 0) printProgressBar(i, ops);

        if (i < capacity) {
            // Phase 1: Fill
            lRUCachePut(obj, i, i);
        } else if (i < capacity * 2) {
            // Phase 2: Verify Existence (should exist)
            int checkKey = i - capacity;
            int res = lRUCacheGet(obj, checkKey);
            if (res != checkKey) {
                printf("\n%sFAIL: Key %d missing during fill check!%s\n", COLOR_RED, checkKey, COLOR_RESET);
                exit(1);
            }
        } else if (i < capacity * 3) {
            // Phase 3: Overflow (Evict old ones)
            // Insert capacity to 2*capacity
            int newKey = i - capacity; // ranges from 1000 to 1999
            lRUCachePut(obj, newKey, newKey);
        } else if (i < capacity * 4) {
            // Phase 4: Verify Eviction
            // Check if 0 to 999 are gone
            int oldKey = i - capacity * 4; // ranges from 0...
            // 這裡邏輯簡化，只做隨機抽樣或特定檢查
            // 檢查 0 是否還在 (應該被擠掉了)
            if (lRUCacheGet(obj, 0) != -1) {
                printf("\n%sFAIL: Key 0 should have been evicted!%s\n", COLOR_RED, COLOR_RESET);
                exit(1);
            }
            // 檢查最新的是否還在
            if (lRUCacheGet(obj, capacity + 5) == -1) {
                printf("\n%sFAIL: Recent key should be present!%s\n", COLOR_RED, COLOR_RESET);
                exit(1);
            }
        }
    }

    printProgressBar(ops, ops);
    printf("\n%sPASS: Big Data Test Completed%s\n", COLOR_GREEN, COLOR_RESET);
    lRUCacheFree(obj);
}

int mainTest() {
    runExample1();
    runCornerCases();
    runBigDataTest();
    return 0;
}