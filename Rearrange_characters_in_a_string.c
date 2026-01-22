#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// ==========================================
//  MEMORY LEAK DETECTOR
// ==========================================
long long g_active_allocations = 0;

void* tracked_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr) g_active_allocations++;
    return ptr;
}

void tracked_free(void* ptr) {
    if (ptr) {
        g_active_allocations--;
        free(ptr);
    }
}

// Redirect standard calls
#define malloc tracked_malloc
#define free tracked_free

// ==========================================
//  USER SOLUTION
// ==========================================
/*
 * Rearrange characters so no two adjacent characters are the same.
 * * @param s: Input string (null-terminated)
 * @return: A NEW allocated string with the result, or NULL if impossible.
 */
unsigned char* rearrangeString(unsigned char* s) {
    if (!s) return NULL;
    int len = strlen((const char*)s);
    unsigned char* new_s=(unsigned char*) calloc(1+len,sizeof(unsigned char));
    //asic max 256
    int bucket[256]={0};
    int max_freq=0;
    unsigned char max_fre_char=0;
    //find max freq; && gather bucket
    for(int i=0;i<len;i++){
        ++bucket[s[i]];
        if(bucket[s[i]]>max_freq){
            max_freq=bucket[s[i]];
            max_fre_char=s[i];
        }
    }

    //test if possible
    if(max_freq > (1+len)/2){
        free(new_s);
        return NULL;
    }
    int filling_ind=0;
    while(bucket[max_fre_char]>0){
        new_s[filling_ind]=max_fre_char;
        filling_ind+=2;
        --bucket[max_fre_char];
    }
    for(int i=0;i<256;i++){
        while(bucket[i]>0){
            if(filling_ind>=len) filling_ind=1;
            new_s[filling_ind]=(unsigned char)i;
            filling_ind+=2;
            --bucket[i];
        }
    }
    new_s[len]='\0';
    return new_s;
}

// ==========================================
//  TESTING INFRASTRUCTURE
// ==========================================

// Helper: Count frequencies for all 256 ASCII chars
void getCounts(const char* s, int* counts) {
    memset(counts, 0, 256 * sizeof(int));
    if (!s) return;
    while (*s) {
        counts[(unsigned char)(*s)]++;
        s++;
    }
}

// Helper: Check if a solution is theoretically possible
// Condition: Max Frequency <= (Length + 1) / 2
int isSolutionPossible(const char* s) {
    if (!s) return 0;
    int counts[256];
    getCounts(s, counts);

    int len = strlen(s);
    int maxFreq = 0;
    for(int i=0; i<256; i++) {
        if (counts[i] > maxFreq) maxFreq = counts[i];
    }

    return maxFreq <= (len + 1) / 2;
}

// Helper: Generates random string
// mode 0: Random uniform (likely possible)
// mode 1: Skewed (likely impossible)
char* generateRandomString(int len, int mode) {
    char* s = (char*)malloc(len + 1);

    if (mode == 1 && len > 0) {
        // Force impossible: fill > 50% with 'a'
        int limit = (len / 2) + 2;
        for(int i=0; i<len; i++) {
            if (i < limit) s[i] = 'a';
            else s[i] = 'b' + (rand() % 5);
        }
    } else {
        // Random
        for(int i=0; i<len; i++) {
            s[i] = 'a' + (rand() % 5); // Small alphabet to force collisions
        }
    }
    s[len] = '\0';
    return s;
}

void runTest(int testNum, char* testName, char* input, int* failedTests) {
    long long memBefore = g_active_allocations;

    // 1. Determine Expectations
    int possible = isSolutionPossible(input);

    // 2. Run User Code
    char* result = rearrangeString(input);

    // 3. Validate
    int passed = 1;
    char failReason[256] = "None";

    if (possible) {
        if (result == NULL) {
            passed = 0;
            sprintf(failReason, "Returned NULL but solution exists");
        } else {
            // Check A: Is it a permutation? (Same counts)
            int countsIn[256], countsOut[256];
            getCounts(input, countsIn);
            getCounts(result, countsOut);

            for(int i=0; i<256; i++) {
                if (countsIn[i] != countsOut[i]) {
                    passed = 0;
                    sprintf(failReason, "Result is not a permutation of input (Char counts mismatch)");
                    break;
                }
            }

            // Check B: Adjacency
            if (passed) {
                int len = strlen(result);
                for(int i=0; i < len - 1; i++) {
                    if (result[i] == result[i+1]) {
                        passed = 0;
                        sprintf(failReason, "Adjacent duplicates found at index %d: '%c'", i, result[i]);
                        break;
                    }
                }
            }
        }
    } else {
        // Impossible case
        if (result != NULL) {
            passed = 0;
            sprintf(failReason, "Should return NULL for impossible input, got \"%s\"", result);
        }
    }

    // 4. Memory Check (User must return allocated string, harness frees it)
    if (result) free(result);
    long long memAfter = g_active_allocations;

    // Output
    printf("Test #%d (%-20s): ", testNum, testName);
    if (passed && memAfter == memBefore) {
        printf("\033[32mPassed\033[0m\n");
    } else {
        printf("\033[31mFailed\033[0m\n");
        printf("  Input:    \"%s\"\n", input);
        printf("  Expected: %s\n", possible ? "Valid String" : "NULL");
        if (!passed) printf("  Reason:   %s\n", failReason);
        if (memAfter != memBefore) printf("  [Memory Leak] Active allocations diff: %lld\n", memAfter - memBefore);
        (*failedTests)++;
    }
}

int main() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    printf("==========================================\n");
    printf("         STANDARD TESTS\n");
    printf("==========================================\n");

    // Test 1: Sample from image
    runTest(++totalTests, "Sample 'bcaaa'", "bcaaa", &failedTests);

    // Test 2: Impossible
    runTest(++totalTests, "Impossible 'aaab'", "aaab", &failedTests);

    // Test 3: Simple valid
    runTest(++totalTests, "Simple 'aab'", "aab", &failedTests);

    // Test 4: Empty
    runTest(++totalTests, "Empty String", "", &failedTests);

    // Test 5: Single char
    runTest(++totalTests, "Single Char", "x", &failedTests);

    // Test 6: Twist - Non-alpha (Numbers)
    runTest(++totalTests, "Numbers '112'", "112", &failedTests);

    printf("\n==========================================\n");
    printf("         STRESS TESTS\n");
    printf("==========================================\n");

    int stressCount = 1000;
    for(int i=0; i<stressCount; i++) {
        int len = 5 + rand() % 15;
        // Mix valid and invalid inputs
        char* input = generateRandomString(len, i % 3 == 0); // 1 in 3 chance of forced failure

        char nameBuffer[32];
        sprintf(nameBuffer, "Random Len %d", len);

        // Suppress print for speed, only print failure
        // We use a simplified inline logic here to avoid spamming console

        int possible = isSolutionPossible(input);
        char* res = rearrangeString(input);

        int valid = 1;
        if (possible && res == NULL) valid = 0;
        else if (!possible && res != NULL) valid = 0;
        else if (possible && res) {
            // Quick adjacency check
            for(int k=0; k<len-1; k++) if(res[k]==res[k+1]) valid=0;
        }

        if (res) free(res);
        free(input);

        if (!valid) {
            printf("Stress Test Failed on iter %d\n", i);
            failedTests++;
            break;
        }

        if (i % 200 == 0) {
            printf("\rRunning... %d/%d", i, stressCount);
            fflush(stdout);
        }
    }
    printf("\rStress Tests Completed.          \n");

    printf("\n==========================================\n");
    if (failedTests == 0) {
        printf("\033[32mAll Tests Passed (Logic + Memory)\033[0m\n");
    } else {
        printf("\033[31mFailed %d Tests\033[0m\n", failedTests);
    }
    printf("==========================================\n");

    return 0;
}