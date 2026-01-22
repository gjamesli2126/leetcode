#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定義 mainTest
#define mainTest main

// 顏色定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge2Lists(struct ListNode* l1,struct ListNode* l2){
    struct ListNode head;
    struct ListNode* cur=&head;
    while(l1 && l2){
        if(l1->val<l2->val) {cur->next=l1;l1=l1->next;}
        else {cur->next=l2;l2=l2->next;}
        cur=cur->next;
    }
    cur->next=l1?l1:l2;
    return head.next;
}
// 主函式：Merge K Sorted Lists

// ==========================================
// --- 以下是測試輔助工具 (Helper Functions) ---
// ==========================================

// 1. 建立單一鏈結串列
struct ListNode* createList(int* arr, int size) {
    if (size == 0) return NULL;
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;
    struct ListNode* curr = head;
    for (int i = 1; i < size; i++) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = arr[i];
        newNode->next = NULL;
        curr->next = newNode;
        curr = newNode;
    }
    return head;
}

// 2. 印出鏈結串列
void printList(struct ListNode* head) {
    printf("[");
    struct ListNode* curr = head;
    while (curr != NULL) {
        printf("%d", curr->val);
        if (curr->next != NULL) printf(",");
        curr = curr->next;
    }
    printf("]");
}

// 3. 驗證結果
bool compareList(struct ListNode* l1, int* expectedArr, int size) {
    struct ListNode* curr = l1;
    for (int i = 0; i < size; i++) {
        if (curr == NULL) return false;
        if (curr->val != expectedArr[i]) return false;
        curr = curr->next;
    }
    return curr == NULL;
}

// 4. 釋放記憶體
void freeList(struct ListNode* head) {
    struct ListNode* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// --- 測試執行器 ---
// inputArrays: 二維陣列 (每個元素是一個 int 陣列)
// inputSizes: 一維陣列 (紀錄每個 list 的長度)
// k: lists 的數量
void runTest(int** inputArrays, int* inputSizes, int k, int* expArr, int expSize) {
    // 1. 建構 ListNode** lists (模擬 LeetCode 輸入)
    struct ListNode** lists = (struct ListNode**)malloc(sizeof(struct ListNode*) * k);

    printf("Input: lists = [");
    for(int i=0; i<k; i++) {
        lists[i] = createList(inputArrays[i], inputSizes[i]);
        printList(lists[i]);
        if(i < k-1) printf(", ");
    }
    printf("] -> ");

    // 2. 執行
    struct ListNode* result = mergeKLists(lists, k);

    // 3. 輸出結果
    printf("Got: ");
    printList(result);

    // 4. 驗證
    if (compareList(result, expArr, expSize)) {
        printf(" %sPASS%s\n", COLOR_GREEN, COLOR_RESET);
    } else {
        printf(" Expected: [");
        for(int i=0; i<expSize; i++) {
            printf("%d", expArr[i]);
            if(i < expSize-1) printf(",");
        }
        printf("] %sFAIL%s\n", COLOR_RED, COLOR_RESET);
    }

    // 5. 清理 (Result 包含了原本所有節點)
    freeList(result);
    // 注意：如果是空結果，lists 裡面的節點可能沒被串起來，嚴謹的測試應該要分開 free，
    // 但在 merge 後通常 lists[i] 會被破壞，這裡簡化處理。
    free(lists);
}

int mainTest() {
    printf("=== LeetCode 23: Merge k Sorted Lists ===\n");

    // Example 1: [[1,4,5],[1,3,4],[2,6]]
    int a1[] = {1, 4, 5};
    int a2[] = {1, 3, 4};
    int a3[] = {2, 6};
    int* input1[] = {a1, a2, a3};
    int sizes1[] = {3, 3, 2};
    int exp1[] = {1, 1, 2, 3, 4, 4, 5, 6};
    runTest(input1, sizes1, 3, exp1, 8);

    // Example 2: [] (Empty input)
    int* input2[] = {};
    int sizes2[] = {};
    int exp2[] = {};
    runTest(input2, sizes2, 0, exp2, 0);

    // Example 3: [[]] (One empty list inside)
    int a_empty[] = {};
    int* input3[] = {a_empty};
    int sizes3[] = {0};
    int exp3[] = {};
    runTest(input3, sizes3, 1, exp3, 0);

    // Additional: [[], [1], [2,3], []] (Mixed empty/non-empty)
    int b1[] = {};
    int b2[] = {1};
    int b3[] = {2, 3};
    int b4[] = {};
    int* input4[] = {b1, b2, b3, b4};
    int sizes4[] = {0, 1, 2, 0};
    int exp4[] = {1, 2, 3};
    runTest(input4, sizes4, 4, exp4, 3);

    return 0;
}