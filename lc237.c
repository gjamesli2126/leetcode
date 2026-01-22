#include <stdio.h>
#include <stdlib.h>

// Renaming main to avoid conflicts if needed
#define mainTest main

// 顏色定義，讓 Output 漂亮一點
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ==========================================
// 1. LeetCode 定義的結構
// ==========================================
struct ListNode {
    int val;
    struct ListNode *next;
};

// ==========================================
// 2. 你的解答實作 (Solution)
// ==========================================
void deleteNode(struct ListNode* node) {
    //trick: make this node become the next node, and del the next node;
    if(!node) return;
    if(!node->next){
        node=NULL;
        return;
    }
    struct ListNode* nextNode=node->next;
    node->val=nextNode->val;
    node->next=nextNode->next;
    free(nextNode);
}

// ==========================================
// 3. 測試輔助工具 (Helper Functions)
// ==========================================

// Helper: 透過陣列建立 Linked List
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

// Helper: 印出 List
void printList(struct ListNode* head) {
    struct ListNode* curr = head;
    printf("[");
    while (curr) {
        printf("%d", curr->val);
        if (curr->next) printf(", ");
        curr = curr->next;
    }
    printf("]\n");
}

// Helper: 釋放 List 記憶體
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Helper: 特殊功能 - 找到特定值的 Node 指標 (模擬題目輸入)
struct ListNode* findNode(struct ListNode* head, int val) {
    struct ListNode* curr = head;
    while (curr) {
        if (curr->val == val) return curr;
        curr = curr->next;
    }
    return NULL;
}

// Helper: 執行單一測試案例
void runTest(int* inputArr, int size, int valToDelete, int testCaseNum) {
    printf("Test Case %d: Input List ", testCaseNum);

    // 準備資料
    struct ListNode* head = createList(inputArr, size);
    printList(head);

    // 模擬題目情境：取得要刪除的節點指標
    struct ListNode* targetNode = findNode(head, valToDelete);

    if (targetNode == NULL) {
        printf(COLOR_RED "  Error: Node %d not found in list!\n" COLOR_RESET, valToDelete);
        freeList(head);
        return;
    }

    printf("  Target to delete: Node(%d)\n", targetNode->val);

    // 執行你的函式 (注意：只傳入 targetNode，不傳入 head)
    deleteNode(targetNode);

    // 驗證結果 (我們檢查 head 來確認 targetNode 是否真的「消失」了)
    printf("  Result:   " COLOR_GREEN);
    printList(head);
    printf(COLOR_RESET);

    printf("--------------------------------------------------\n");

    // 清理記憶體
    freeList(head);
}

// ==========================================
// 4. Main Test
// ==========================================
int mainTest() {
    printf("=== LeetCode 237: Delete Node in a Linked List ===\n\n");

    // Test Case 1
    // Input: head = [4,5,1,9], node = 5
    int arr1[] = {4, 5, 1, 9};
    runTest(arr1, 4, 5, 1);

    // Test Case 2
    // Input: head = [4,5,1,9], node = 1
    int arr2[] = {4, 5, 1, 9};
    runTest(arr2, 4, 1, 2);

    // Test Case 3: Longer list
    // Input: head = [1, 2, 3, 4, 5], node = 3
    int arr3[] = {1, 2, 3, 4, 5};
    runTest(arr3, 5, 3, 3);

    return 0;
}