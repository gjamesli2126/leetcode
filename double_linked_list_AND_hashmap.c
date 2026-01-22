#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// 定義 mainTest
#define mainTest main

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ==========================================
// PART 1: Doubly Linked List (DLL)
// ==========================================

// 雙向節點
typedef struct DNode {
    int val;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// 雙向鏈表管理結構 (使用 Dummy Head & Tail 簡化邊界處理)
typedef struct {
    DNode* head; // Dummy Head
    DNode* tail; // Dummy Tail
    int size;
} DList;

// --- TODO: 請實作以下 DLL 函式 ---

// 初始化 DList (配置 dummy head/tail 並連接)
DList* dListCreate() {
    // 提示: head->next = tail; tail->prev = head;
    /*為了避免整天avoid corner case，要增添 dumbHead & dumbTail
     * */
    DList* lst=(DList*)malloc(sizeof(DList));
    lst->size=0;
    lst->head=(DNode*) malloc(sizeof(DNode));
    lst->tail=(DNode*) malloc(sizeof(DNode));
    lst->head->prev=NULL;
    lst->head->next=lst->tail;
    lst->tail->prev=lst->head;
    lst->tail->next=NULL;
    return lst;
}

// 建立新節點
DNode* createDNode(int val) {
    DNode* node= (DNode*)malloc(sizeof(DNode));
    node->val=val;
    return node;
}

// 加到頭部 (Add to Head) - 這是 LRU 的核心動作
void dListAddHead(DList* list, DNode* node) {
    // 提示: 操作 head, head->next 和 node
    DNode* dummy_head=list->head;
    DNode* org_real_head=dummy_head->next;
    dummy_head->next=node;
    node->prev=dummy_head;
    node->next=org_real_head;
    org_real_head->prev=node;
    ++list->size;
}

// 移除特定節點 (Remove Node) - 這是 LRU 的核心動作
void dListDetach(DList* list, DNode* node) {
    // 提示: 操作 node->prev 和 node->next
    DNode* prev=node->prev;
    DNode* nxt=node->next;
    prev->next=nxt;
    nxt->prev=prev;
//    free(node);// no need if hashmap still need it's access
    --list->size;
//    if(!(list->size)) free(list);// no need if hashmap still need it's access
// 4. (選用) 為了安全，把 node 的手腳剁掉，避免它還連著舊鏈表
    node->prev = NULL;
    node->next = NULL;
}

// 釋放記憶體
void dListFree(DList* list) {
    // 記得釋放 dummy nodes 和中間的所有 nodes
    DNode* cur=list->head;//從 dummy head開使 free
    while(cur){
        DNode* nxt=cur->next;
        free(cur);
        cur=nxt;
    }//free到 dummy tail
    free(list);
}

// 輔助: 印出 List (用來檢查順序)
void dListPrint(DList* list) {
    if (!list) return;
    DNode* curr = list->head->next;
    printf("List: [");
    while (curr != list->tail) {
        printf("%d", curr->val);
        if (curr->next != list->tail) printf(" <-> ");
        curr = curr->next;
    }
    printf("]\n");
}

// ==========================================
// PART 2: Hash Map (Chaining)
// ==========================================

#define MAP_SIZE 10 // 故意設小一點，方便測試 Hash Collision

// Hash Map 節點 (單向鏈表，用於解決衝突)
typedef struct HNode {
    int key;
    int value;
    struct HNode* next;
} HNode;

// Hash Map 結構
typedef struct {
    HNode* buckets[MAP_SIZE]; // 指標陣列 若整坨 Hashmap是在 heap上建立---> 該 bucket也是在 heap上建立
} HashMap;

// --- TODO: 請實作以下 Hash Map 函式 ---

// 初始化
HashMap* hashMapCreate() {
    // 配置記憶體，並確保 buckets 都是 NULL
    HashMap* hmap=(HashMap*)calloc(1,sizeof(HashMap));
    return hmap;
}

// Hash Function
static inline int hash(int key) {
    // 回傳 key % MAP_SIZE (取絕對值)
    return abs(key%MAP_SIZE);
}

// Put: 新增或更新
void hashMapPut(HashMap* map, int key, int value) {
    // 1. 算出 index
    int index= hash(key);
    // 2. 遍歷該 bucket 的鏈表
    HNode* head=map->buckets[index];
    HNode* node=head;
    while(node && node->key!=key) node=node->next;
    // 3. 如果 key 存在 -> 更新 value
    if(node) node->value=value;
    // 4. 如果 key 不存在 -> 建立新節點插在 bucket 頭部
    else{
        HNode* newNode=(HNode*)malloc(sizeof(HNode));
        newNode->key=key;
        newNode->value=value;
        newNode->next=head;
        map->buckets[index]=newNode;//要update new HEAD!!
    }
}

// Get: 取得數值 (找不到回傳 -1)
int hashMapGet(HashMap* map, int key) {
    // 1. 算出 index
    int index= hash(key);
    // 2. 遍歷鏈表尋找 key
    HNode* node=map->buckets[index];
    while(node && node->key!=key) node=node->next;
    if(node) return node->value;
    return -1;
}

// Remove: 刪除 Key
void hashMapRemove(HashMap* map, int key) {
    // 這是單向鏈表刪除，需要維護 prev 指標
    int index= hash(key);
    HNode* head=map->buckets[index];
    HNode* node=head;
    HNode* prev=NULL;
    while(node && node->key!=key){
        prev=node;
        node=node->next;
    }
    if(!node) return;

    if(!prev) map->buckets[index]=node->next;//但萬一要刪除的是head呢！
    else prev->next=node->next;
    free(node);
}

// 釋放
void hashMapFree(HashMap* map) {
    if(!map) return;//sanity check!
    for(int i=0;i<MAP_SIZE;i++){
        HNode* node=map->buckets[i];
        while(node){
            HNode* nxt=node->next;
            free(node);
            node=nxt;
        }
    }
    free(map);
}

// ==========================================
// --- 測試執行區 (Test Runner) ---
// ==========================================

void testDLL() {
    printf("\n=== Testing Doubly Linked List ===\n");

    DList* list = dListCreate();
    if (!list) { printf("DList Create Failed\n"); return; }

    DNode* n1 = createDNode(10);
    DNode* n2 = createDNode(20);
    DNode* n3 = createDNode(30);

    // 1. Add Head
    dListAddHead(list, n1); // [10]
    dListAddHead(list, n2); // [20 <-> 10]
    dListAddHead(list, n3); // [30 <-> 20 <-> 10]

    dListPrint(list);

    // 簡單驗證
    if (list->head->next->val == 30 && list->tail->prev->val == 10)
        printf("%sPASS: Add Head Order Correct%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sFAIL: Add Head Order Incorrect%s\n", COLOR_RED, COLOR_RESET);

    // 2. Remove Middle (20)
    dListDetach(list, n2); // [30 <-> 10]
    printf("Removed 20: ");
    dListPrint(list);

    if (n3->next == n1 && n1->prev == n3)
        printf("%sPASS: Remove Middle Correct%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sFAIL: Remove Middle Incorrect%s\n", COLOR_RED, COLOR_RESET);

    dListFree(list); // 這裡應該要 free n1, n2, n3
    // 注意：上面的 n1, n2, n3 指標在 free 後會變懸空指標，測試中不再使用
}

void testHashMap() {
    printf("\n=== Testing Hash Map (Chaining) ===\n");

    HashMap* map = hashMapCreate();
    if (!map) { printf("HashMap Create Failed\n"); return; }

    // 1. Basic Put/Get
    hashMapPut(map, 1, 100);
    hashMapPut(map, 2, 200);

    int v1 = hashMapGet(map, 1);
    if (v1 == 100) printf("%sPASS: Get(1) == 100%s\n", COLOR_GREEN, COLOR_RESET);
    else printf("%sFAIL: Get(1) Expected 100, Got %d%s\n", COLOR_RED, v1, COLOR_RESET);

    // 2. Update Value
    hashMapPut(map, 1, 111); // Update key 1
    v1 = hashMapGet(map, 1);
    if (v1 == 111) printf("%sPASS: Update(1) == 111%s\n", COLOR_GREEN, COLOR_RESET);
    else printf("%sFAIL: Update(1) Expected 111, Got %d%s\n", COLOR_RED, v1, COLOR_RESET);

    // 3. Collision Handling (MAP_SIZE is 10)
    // 5 和 15 % 10 都是 5，應該要發生碰撞但能獨立存取
    hashMapPut(map, 5, 50);
    hashMapPut(map, 15, 150);

    int v5 = hashMapGet(map, 5);
    int v15 = hashMapGet(map, 15);

    if (v5 == 50 && v15 == 150)
        printf("%sPASS: Collision Handling (5 & 15)%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sFAIL: Collision Failed. Got %d, %d%s\n", COLOR_RED, v5, v15, COLOR_RESET);

    // 4. Remove
    hashMapRemove(map, 5);
    if (hashMapGet(map, 5) == -1 && hashMapGet(map, 15) == 150)
        printf("%sPASS: Remove Key 5 (Key 15 stays)%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sFAIL: Remove Failed%s\n", COLOR_RED, COLOR_RESET);

    hashMapFree(map);
}

int mainTest() {
    testDLL();
    testHashMap();
    return 0;
}