#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定義 mainTest
#define mainTest main
// 顏色定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

typedef struct ListNode{
    int val;
    struct ListNode* next;
}ListNode_t;
//#define ListNode_t struct ListNode
ListNode_t* mergeTwoLists(ListNode_t* l1,ListNode_t* l2){
    if(!l1) return l2;
    if(!l2) return l1;
        if(l1->val<l2->val){
            l1->next= mergeTwoLists(l1->next,l2);//l1是冠軍 所以上層要接我 那我要接誰呢？就@這行
            return l1;
        }
        else{
            l2->next= mergeTwoLists(l1,l2->next);
            return l2;
        }
}
// ==========================================
// --- 以下是測試輔助工具 (Helper Functions) ---
// ==========================================

// 1. 建立鏈結串列 (Array -> LinkedList)
struct ListNode* createList(int* arr, int size) {
    if (size == 0) return NULL;

    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;

    struct ListNode* current = head;
    for (int i = 1; i < size; i++) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
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

// 3. 釋放記憶體
void freeList(struct ListNode* head) {
    struct ListNode* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// 4. 比較結果
bool compareList(struct ListNode* l1, int* expectedArr, int size) {
    struct ListNode* curr = l1;
    for (int i = 0; i < size; i++) {
        if (curr == NULL) return false; // 長度不足
        if (curr->val != expectedArr[i]) return false; // 值不符
        curr = curr->next;
    }
    return curr == NULL; // 確保長度剛好
}

// --- 測試執行器 ---
void runTest(int* arr1, int size1, int* arr2, int size2, int* expArr, int expSize) {
    // 建立輸入
    struct ListNode* l1 = createList(arr1, size1);
    struct ListNode* l2 = createList(arr2, size2);

    // 印出輸入
    printf("Input: l1=");
    printList(l1);
    printf(", l2=");
    printList(l2);
    printf(" -> ");

    // 執行解答
    struct ListNode* result = mergeTwoLists(l1, l2);

    // 印出輸出
    printf("Got: ");
    printList(result);

    // 驗證
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

    // 記憶體清理
    // 注意：mergeTwoLists 通常是 in-place 修改，所以 l1 和 l2 的節點現在都在 result 裡
    // 我們只需要 free result 即可，不需要分開 free l1 和 l2
    freeList(result);
}

int mainTest() {
    printf("=== LeetCode 21: Merge Two Sorted Lists ===\n");

    // Example 1
    int a1[] = {1, 2, 4};
    int b1[] = {1, 3, 4};
    int exp1[] = {1, 1, 2, 3, 4, 4};
    runTest(a1, 3, b1, 3, exp1, 6);

    // Example 2
    int a2[] = {};
    int b2[] = {};
    int exp2[] = {};
    runTest(a2, 0, b2, 0, exp2, 0);

    // Example 3
    int a3[] = {};
    int b3[] = {0};
    int exp3[] = {0};
    runTest(a3, 0, b3, 1, exp3, 1);

    // Additional Test (One list longer)
    int a4[] = {5};
    int b4[] = {1, 2, 6};
    int exp4[] = {1, 2, 5, 6};
    runTest(a4, 1, b4, 3, exp4, 4);

    return 0;
}