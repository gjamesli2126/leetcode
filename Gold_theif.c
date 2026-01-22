#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// ==========================================
//  MEMORY LEAK DETECTOR (INTERCEPTOR)
// ==========================================
long long g_active_allocations = 0;
long long g_total_allocations = 0;

void* tracked_malloc(size_t size) {
    if (size == 0) return NULL;
    void* ptr = malloc(size);
    if (ptr) {
        g_active_allocations++;
        g_total_allocations++;
    }
    return ptr;
}

void tracked_free(void* ptr) {
    if (ptr) {
        g_active_allocations--;
        free(ptr);
    }
}

// Macro Magic: Redirect standard calls to our tracker
// (Place this BEFORE user code so user's code uses these versions)
#define malloc tracked_malloc
#define free tracked_free
#define MAX(a,b) ((a) > (b) ? (a) : (b))

// ==========================================
//  USER SOLUTION
// ==========================================
/*
 * Calculate the maximum amount of gold.
 * ! Constraint: O(1) space preferred, but if you malloc, you MUST free.
 */
static inline long long max(long long a,long long b){
    return a>b?a:b;
}
long long stealMaxGold(int* houses, int housesSize) {
    if(!housesSize) return 0;
    if(housesSize==1) return houses[0];
    if(housesSize==2) return max(houses[0],houses[1]);
    long long prev2=houses[0];
    long long prev=max(prev2,houses[1]);//因為他是取 前值 max
    long long  cur;
    for(int i=2;i<housesSize;i++){
        cur=max(houses[i]+prev2,prev);
        prev2=prev;
        prev=cur;
    }
    return cur;
}

// ==========================================
//  TESTING INFRASTRUCTURE
// ==========================================

// Trusted Reference Solver
long long referenceSolver(int* houses, int size) {
    if (!houses || size == 0) return 0;
    if (size == 1) return houses[0];
    long long p2 = 0, p1 = 0;
    for (int i = 0; i < size; i++) {
        long long cur = MAX(p1, p2 + houses[i]);
        p2 = p1;
        p1 = cur;
    }
    return p1;
}

// Helper: Generates random street
// Note: This uses 'tracked_malloc' now because of the macros above.
int* generateRandomStreet(int size, int maxVal) {
    if (size == 0) return NULL;
    int* houses = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        houses[i] = rand() % maxVal;
    }
    return houses;
}

void runTest(int testNum, char* testName, int* houses, int size, long long expected, int* failedTests) {
    // Record memory state before test
    long long memBefore = g_active_allocations;

    long long actual = stealMaxGold(houses, size);

    // Check Logic
    int passed = (actual == expected);

    // Check Memory (Did user leak?)
    // Note: 'houses' is allocated by harness, so we shouldn't free it inside stealMaxGold.
    // The strict check here assumes stealMaxGold manages its OWN internal memory.
    long long memAfter = g_active_allocations;
    int leakDetected = (memAfter > memBefore);

    printf("Test #%d (%-25s): ", testNum, testName);

    if (passed && !leakDetected) {
        printf("\033[32mPassed\033[0m\n");
    } else {
        printf("\033[31mFailed\033[0m\n");
        if (!passed) printf("  [Logic Error] Exp: %lld, Got: %lld\n", expected, actual);
        if (leakDetected) printf("  [Memory Leak] Active blocks increased by %lld\n", memAfter - memBefore);
        (*failedTests)++;
    }
}

int main() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    printf("==========================================\n");
    printf("         CORNER CASE TESTS\n");
    printf("==========================================\n");

    // We must manually allocate/free test cases to play nice with the tracker
    // Or we can use stack arrays (which don't trigger malloc).
    // For simplicity, let's use stack arrays for small static tests 
    // (Macros won't affect stack arrays).

    int t1[] = {1, 2, 3, 1};
    runTest(++totalTests, "Example 1", t1, 4, 4, &failedTests);

    int t2[] = {2, 7, 9, 3, 1};
    runTest(++totalTests, "Example 2", t2, 5, 12, &failedTests);

    int t3[] = {1000};
    runTest(++totalTests, "Single House", t3, 1, 1000, &failedTests);

    runTest(++totalTests, "NULL Input", NULL, 0, 0, &failedTests);

    int t8[] = {2000000000, 10, 2000000000};
    long long exp8 = 4000000000LL;
    runTest(++totalTests, "Integer Overflow", t8, 3, exp8, &failedTests);

    // Verify Leak Detector is working:
    // This assumes the TEST HARNESS itself isn't leaking.
    if (g_active_allocations != 0) {
        printf("\n[SYSTEM WARNING] The Test Harness itself has a leak! Active: %lld\n", g_active_allocations);
    }

    printf("\n==========================================\n");
    printf("         STRESS & LEAK TESTS\n");
    printf("==========================================\n");

    int stressCount = 2000;

    for(int i = 0; i < stressCount; i++) {
        // Prepare Test Case
        int n;
        if (i < 500) n = rand() % 20;
        else n = 100 + rand() % 4900;

        // Harness Allocation (Recorded +1)
        int* houses = generateRandomStreet(n, 1000);

        long long expected = referenceSolver(houses, n);

        // Run Test (Checks for internal leaks inside stealMaxGold)
        // User function is called here.
        long long actual = stealMaxGold(houses, n);

        // Verification
        if (actual != expected) {
            failedTests++;
            printf("Stress Test Logic Failed! Size: %d\n", n);
            free(houses);
            break;
        }

        // Harness Cleanup (Recorded -1)
        free(houses);

        // Global Sanity Check
        // If everything is correct, active allocations must be 0 here.
        if (g_active_allocations != 0) {
            failedTests++;
            printf("\033[31m[CRITICAL MEMORY LEAK]\033[0m Stress test iteration %d.\n", i);
            printf("  You allocated memory but didn't free it.\n");
            printf("  Active Allocations: %lld\n", g_active_allocations);
            break; // Stop immediately on leak
        }

        if (i % 200 == 0) {
            printf("\rRunning Tests... %d/%d", i, stressCount);
            fflush(stdout);
        }
    }
    printf("\rTests Completed.                  \n");

    // Final Report
    printf("\n==========================================\n");
    if (failedTests == 0) {
        printf("\033[32mAll Tests Passed (Logic + Memory Safe)\033[0m\n");
    } else {
        printf("\033[31mFailed %d Tests\033[0m\n", failedTests);
    }
    printf("Total Heap Allocations Monitored: %lld\n", g_total_allocations);
    printf("Final Active Allocations: %lld\n", g_active_allocations);
    printf("==========================================\n");

    return 0;
}