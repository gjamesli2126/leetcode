#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. LeetCode Definition
// ==========================================
struct ListNode {
    int val;
    struct ListNode *next;
};

// ==========================================
// 2. Your Solution (Implement Here)
// ==========================================
void rm_recursion(struct ListNode* node,int* i,struct ListNode* prev){
    //base case
    if(!node) return;
    rm_recursion(node->next,i,node);
    --(*i);
    if(*i==0){
        prev->next=node->next;
        free(node);
    }
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    //using recrusion popping n times;
    struct ListNode dummyHead;
    dummyHead.next=head;//防止裡面 的 prev is a null
    rm_recursion(head,&n,&dummyHead);
    return dummyHead.next;
}

// ==========================================
// 3. Helpers (For Testing)
// ==========================================

// Create a list from an array
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

// Print the list
void printList(struct ListNode* head) {
    printf("[");
    struct ListNode* curr = head;
    while (curr) {
        printf("%d", curr->val);
        if (curr->next) printf(", ");
        curr = curr->next;
    }
    printf("]\n");
}

// Free memory
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Test Runner
void runTest(int* inputArr, int size, int n, int testCaseNum) {
    printf("=== Test Case %d ===\n", testCaseNum);
    printf("Input: head = ");
    struct ListNode* head = createList(inputArr, size);
    printList(head);
    printf("n = %d\n", n);

    // Call your function
    struct ListNode* result = removeNthFromEnd(head, n);

    printf("Output: ");
    printList(result);
    printf("\n");

    // Cleanup (Note: this might double free if you freed nodes inside your function, 
    // but usually safe for simple testing)
    freeList(result);
}

// ==========================================
// 4. Main Test
// ==========================================
int main() {
    // Example 1
    // Input: head = [1,2,3,4,5], n = 2
    // Expected: [1,2,3,5]
    int arr1[] = {1, 2, 3, 4, 5};
    runTest(arr1, 5, 2, 1);

    // Example 2
    // Input: head = [1], n = 1
    // Expected: []
    int arr2[] = {1};
    runTest(arr2, 1, 1, 2);

    // Example 3
    // Input: head = [1,2], n = 1
    // Expected: [1]
    int arr3[] = {1, 2};
    runTest(arr3, 2, 1, 3);

    return 0;
}