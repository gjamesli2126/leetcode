#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Toggle this to enable/disable Standalone Mode
#define mainTest main

// ==========================================
// 1. LeetCode Struct Definition (Guarded)
// ==========================================
#ifdef mainTest
struct ListNode {
    int val;
    struct ListNode *next;
};
#endif

// ==========================================
// 2. Solution Implementation
// ==========================================
typedef struct ListNode ListNode_t;

bool hasCycle(struct ListNode *head) {
    // Write your Floyd's Cycle-Finding Algorithm (Tortoise and Hare) here
    if(!head || !head->next) return false;
    ListNode_t* slow=head;
    ListNode_t* fast=head;//->next;
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
        if(slow==fast) return true;
    }
    return false;
}

// ==========================================
// 3. Test Suite (Only compiled in mainTest mode)
// ==========================================
#ifdef mainTest

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// Helper: Create a standard list
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

// Helper: Connect tail to index 'pos' to create a cycle
// Returns the tail node so we can break the cycle later for cleanup
struct ListNode* createCycle(struct ListNode* head, int pos) {
    if (pos == -1 || head == NULL) return NULL;

    struct ListNode* tail = head;
    struct ListNode* target = NULL;
    int index = 0;

    // Find tail and the target node
    while (tail->next != NULL) {
        if (index == pos) target = tail;
        tail = tail->next;
        index++;
    }
    // Check if tail itself is the target (case where pos is the last index)
    if (index == pos) target = tail;

    if (target != NULL) {
        tail->next = target; // Create the cycle
        return tail;         // Return tail so we can break it later
    }
    return NULL;
}

// Helper: Free List (Standard)
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void runTest(int* inputArr, int size, int pos, int testCaseNum) {
    printf("Test Case %d: ", testCaseNum);
    struct ListNode* head = createList(inputArr, size);

    // Create cycle and keep track of tail to avoid infinite loops during free
    struct ListNode* tail = createCycle(head, pos);

    // Run Solution
    bool result = hasCycle(head);

    // Verify
    bool expected = (pos != -1);
    if (result == expected) {
        printf(COLOR_GREEN "PASS" COLOR_RESET " (Output: %s)\n", result ? "true" : "false");
    } else {
        printf(COLOR_RED "FAIL" COLOR_RESET " (Expected: %s, Got: %s)\n",
               expected ? "true" : "false", result ? "true" : "false");
    }

    // Cleanup: Break the cycle first!
    if (tail != NULL) {
        tail->next = NULL;
    }
    freeList(head);
}

int mainTest() {
    printf("=== LeetCode 141: Linked List Cycle ===\n\n");

    // Test Case 1
    // Input: head = [3,2,0,-4], pos = 1
    int arr1[] = {3, 2, 0, -4};
    runTest(arr1, 4, 1, 1);

    // Test Case 2
    // Input: head = [1,2], pos = 0
    int arr2[] = {1, 2};
    runTest(arr2, 2, 0, 2);

    // Test Case 3
    // Input: head = [1], pos = -1
    int arr3[] = {1};
    runTest(arr3, 1, -1, 3);

    // Test Case 4: Empty List
    int arr4[] = {};
    runTest(arr4, 0, -1, 4);

    return 0;
}
#endif