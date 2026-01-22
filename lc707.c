#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 定義 mainTest
#define mainTest main

// 顏色與格式定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RESET "\033[0m"

// ==========================================
// 資料結構定義 (Data Structures)
// ==========================================
typedef struct Node{
    struct Node* prev, *next;
    int val;
} Node_t;

typedef struct MyLinkedList{
    Node_t* dumbHead;
    Node_t* dumbTail;
    int size;
} MyLinkedList;
// Size info: 8(ptr) + 8(ptr) + 4(int) + 4(padding) = 24 bytes aligned.

// ==========================================
// 你的實作 (已修正邏輯以通過測試)
// ==========================================

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* dll = (MyLinkedList*) malloc(sizeof(MyLinkedList));
    dll->dumbHead = (Node_t*) calloc(1, sizeof(Node_t));
    dll->dumbTail = (Node_t*) calloc(1, sizeof(Node_t));

    // 連接哨兵節點
    dll->dumbHead->next = dll->dumbTail;
    dll->dumbTail->prev = dll->dumbHead;

    // 初始化大小 (這行很重要)
    dll->size = 0;
    return dll;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if(!obj || index < 0 || index >= obj->size) return -1;

    Node_t* node = obj->dumbHead->next; // 從第 0 個開始

    // 優化：這裡改成簡單的 index-- 邏輯
    while(node != obj->dumbTail && index > 0){
        node = node->next;
        index--;
    }

    if(node == obj->dumbTail) return -1;
    return node->val;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    if(!obj) return;
    Node_t* dh = obj->dumbHead;
    Node_t* org_head = dh->next;
    Node_t* new_head = (Node_t*)malloc(sizeof(Node_t));

    new_head->val = val;

    dh->next = new_head;
    new_head->prev = dh;

    org_head->prev = new_head;
    new_head->next = org_head;

    obj->size++;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    if(!obj) return;
    Node_t* dt = obj->dumbTail;
    Node_t* old_tail = dt->prev;
    Node_t* new_tail = (Node_t*)malloc(sizeof(Node_t));

    new_tail->val = val;

    old_tail->next = new_tail;
    new_tail->prev = old_tail;

    new_tail->next = dt;
    dt->prev = new_tail;

    obj->size++;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if(!obj || index > obj->size || index < 0) return;

//    // 為了簡化邏輯，如果 index == size，直接呼叫 AddAtTail
//    if (index == obj->size) {
//        myLinkedListAddAtTail(obj, val);
//        return;
//    }
//    // 如果 index == 0，直接呼叫 AddAtHead
//    if (index == 0) {
//        myLinkedListAddAtHead(obj, val);
//        return;
//    }

    Node_t* curr; // 這是我們要插在它 "前面" 的那個節點

    if(index < obj->size / 2){
        // --- 從頭找 ---
        curr = obj->dumbHead->next;
        while(index > 0){
            curr = curr->next;
            index--;
        }
    } else {
        // --- 從尾找 ---
        // 【修正邏輯】
        // 目標：找到 index 號節點。
        // 從 dumbTail 往回走。 dumbTail 視為 index = size。
        // 步數 = size - index。
        curr = obj->dumbTail;
        int steps = obj->size - index;
        while(steps > 0){
            curr = curr->prev;
            steps--;
        }
    }

    // 執行插入 (插在 curr 之前)
    Node_t* prev = curr->prev;
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    new_node->val = val;

    // 建立新連結
    prev->next = new_node;
    new_node->prev = prev;

    new_node->next = curr;
    curr->prev = new_node;

    obj->size++;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if(!obj || index < 0 || index >= obj->size) return;

    Node_t* node; // 要刪除的目標節點

    if(index < obj->size / 2){
        // --- 從頭找 ---
        node = obj->dumbHead->next;
        while(node && index > 0){
            node = node->next;
            --index;
        }
    }
    else{
        // --- 從尾找 ---
        // 【修正邏輯】
        // 最後一個元素的 index 是 size - 1。
        // 目標是從 dumbTail->prev 往回走 (size - 1 - index) 步。
        node = obj->dumbTail;
        int steps = obj->size - index;
        while(node && steps > 0){
            node = node->prev;
            --steps;
        }
    }

    // 執行刪除
    Node_t* prev = node->prev;
    Node_t* next = node->next;

    prev->next = next;
    next->prev = prev;

    free(node);
    --obj->size;
}

void myLinkedListFree(MyLinkedList* obj) {
    if(!obj) return;
    Node_t* node = obj->dumbHead;
    while(node){
        Node_t* next = node->next;
        free(node);
        node = next;
    }
    free(obj);
}

// ==========================================
// --- 測試輔助工具 (Updated for your Struct) ---
// ==========================================

void printList(MyLinkedList* obj, const char* msg) {
    if (!obj) return;
    printf("List (%s): [Head] <-> ", msg);
    // 【修正】使用 dumbHead 和 dumbTail
    Node_t* curr = obj->dumbHead->next;
    while (curr != obj->dumbTail) {
        printf("%d <-> ", curr->val);
        curr = curr->next;
    }
    printf("[Tail] (Size: %d)\n", obj->size);
}

void assertInt(int result, int expected, const char* msg) {
    if (result == expected) {
        // printf("  [OK] %s\n", msg);
    } else {
        printf("\n  %s[FAIL] %s: Got %d, Expected %d%s\n", COLOR_RED, msg, result, expected, COLOR_RESET);
        exit(1);
    }
}

// ==========================================
// --- 測試案例 (Test Cases) ---
// ==========================================

void runExample1() {
    printf("\n%s=== Running Example 1 (LeetCode) ===%s\n", COLOR_YELLOW, COLOR_RESET);
    MyLinkedList* obj = myLinkedListCreate();
    if (!obj) { printf("Create failed (returned NULL)\n"); return; }

    myLinkedListAddAtHead(obj, 1);
    printList(obj, "addHead(1)");

    myLinkedListAddAtTail(obj, 3);
    printList(obj, "addTail(3)");

    myLinkedListAddAtIndex(obj, 1, 2);
    printList(obj, "addAtIndex(1, 2)");
    // List should be: 1 -> 2 -> 3

    // 驗證 Index 1 的值
    assertInt(myLinkedListGet(obj, 1), 2, "Get(1) should return 2");

    myLinkedListDeleteAtIndex(obj, 1);
    printList(obj, "deleteAtIndex(1)");
    // List should be: 1 -> 3

    assertInt(myLinkedListGet(obj, 1), 3, "Get(1) should return 3");

    myLinkedListFree(obj);
    printf("%sPASS: Example 1%s\n", COLOR_GREEN, COLOR_RESET);
}

void runCornerCases() {
    printf("\n%s=== Running Corner Cases ===%s\n", COLOR_YELLOW, COLOR_RESET);

    MyLinkedList* obj = myLinkedListCreate();

    // 1. 測試空 List 刪除/獲取
    printf("1. Empty List Operations...\n");
    assertInt(myLinkedListGet(obj, 0), -1, "Get from empty list");
    myLinkedListDeleteAtIndex(obj, 0); // Should do nothing

    // 2. 測試頭部操作
    printf("2. Head Operations...\n");
    myLinkedListAddAtHead(obj, 10); // [10]
    myLinkedListDeleteAtIndex(obj, 0); // []
    assertInt(myLinkedListGet(obj, 0), -1, "List should be empty again");

    // 3. 測試 addAtIndex 的邊界
    printf("3. AddAtIndex Boundary...\n");
    myLinkedListAddAtTail(obj, 10); // [10]

    myLinkedListAddAtIndex(obj, 2, 20); // Index > size (1), do nothing.
    assertInt(myLinkedListGet(obj, 1), -1, "Index > size should fail");

    myLinkedListAddAtIndex(obj, 1, 20); // Index == size (1), append. [10, 20]
    printList(obj, "Added 20 at tail");
    assertInt(myLinkedListGet(obj, 1), 20, "Index == size should append");

    myLinkedListAddAtIndex(obj, 0, 5); // Index == 0, head insert. [5, 10, 20]
    printList(obj, "Added 5 at head");
    assertInt(myLinkedListGet(obj, 0), 5, "Index == 0 should be head");

    myLinkedListFree(obj);
    printf("%sPASS: Corner Cases%s\n", COLOR_GREEN, COLOR_RESET);
}

void runStressTest() {
    printf("\n%s=== Running Stress Test (2000 Ops) ===%s\n", COLOR_YELLOW, COLOR_RESET);

    MyLinkedList* obj = myLinkedListCreate();
    int LIMIT = 2000;

    // 1. 大量插入 (Tail)
    for (int i = 0; i < LIMIT; i++) {
        myLinkedListAddAtTail(obj, i);
    }
    assertInt(obj->size, LIMIT, "Size check after mass insert");
    assertInt(myLinkedListGet(obj, LIMIT-1), LIMIT-1, "Last element check");

    // 2. 大量刪除 (Head)
    for (int i = 0; i < LIMIT / 2; i++) {
        myLinkedListDeleteAtIndex(obj, 0);
    }

    assertInt(myLinkedListGet(obj, 0), 1000, "Head check after mass delete");
    assertInt(obj->size, LIMIT / 2, "Size check after mass delete");

    myLinkedListFree(obj);
    printf("%sPASS: Stress Test Completed%s\n", COLOR_GREEN, COLOR_RESET);
}

int mainTest() {
    runExample1();
    runCornerCases();
    runStressTest();
    return 0;
}