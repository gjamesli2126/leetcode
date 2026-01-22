#include <stdio.h>
#include <stdlib.h>

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
struct ListNode* removeElements(struct ListNode* head,int val_to_remove){
    struct ListNode dumbHead;
    dumbHead.next=head;
    struct ListNode* cur=head;
    struct ListNode* prev=&dumbHead;
    while(cur){
        if(cur->val==val_to_remove){
            struct ListNode* nxt=cur->next;
            prev->next=nxt;
            free(cur);
            cur=nxt;
        }else{
            prev=cur;
            cur=cur->next;
        }
    }
    return dumbHead.next;
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

// Helper: 執行單一測試案例
void runTest(int* inputArr, int size, int val, int* expectArr, int expectSize, int testCaseNum) {
    printf("Test Case %d: remove %d from ", testCaseNum, val);

    // 準備資料
    struct ListNode* head = createList(inputArr, size);
    printList(head); // 印出 Input

    // 執行你的函式
    struct ListNode* resultHead = removeElements(head, val);

    // 驗證結果
    printf("  Result:   ");
    printList(resultHead);

    // 簡單比對 (這裡只比對 Output 長相，嚴格測試可以用迴圈比對數值)
    // 為了顯示方便，這裡直接人工判讀 Result

    printf("--------------------------------------------------\n");

    // 清理記憶體
    freeList(resultHead);
}

// ==========================================
// 4. Main Test
// ==========================================
int main() {
    printf("=== LeetCode 203: Remove Linked List Elements ===\n\n");

    // Test Case 1: Standard
    // Input: head = [1,2,6,3,4,5,6], val = 6
    int arr1[] = {1, 2, 6, 3, 4, 5, 6};
    int exp1[] = {1, 2, 3, 4, 5};
    runTest(arr1, 7, 6, exp1, 5, 1);

    // Test Case 2: Empty List
    // Input: head = [], val = 1
    int arr2[] = {};
    int exp2[] = {};
    runTest(arr2, 0, 1, exp2, 0, 2);

    // Test Case 3: Remove All
    // Input: head = [7,7,7,7], val = 7
    int arr3[] = {7, 7, 7, 7};
    int exp3[] = {};
    runTest(arr3, 4, 7, exp3, 0, 3);

    // Test Case 4: Head Removal (Mixed)
    // Input: head = [1, 2, 3], val = 1
    int arr4[] = {1, 2, 3};
    int exp4[] = {2, 3};
    runTest(arr4, 3, 1, exp4, 2, 4);

    return 0;
}