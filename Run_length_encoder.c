#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ==========================================
//  MEMORY LEAK DETECTOR
// ==========================================
long long g_active_allocations = 0;

void* tracked_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr) g_active_allocations++;
    return ptr;
}

void* tracked_calloc(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    if (ptr) g_active_allocations++;
    return ptr;
}

void tracked_free(void* ptr) {
    if (ptr) {
        g_active_allocations--;
        free(ptr);
    }
}

#define malloc tracked_malloc
#define calloc tracked_calloc
#define free tracked_free

// ==========================================
//  USER SOLUTION
// ==========================================

/*
 * Twist 1: Implement the Encoder
 * Input: "aaabbccca" -> Output: "a3b2c3a1"
 * Note: Handle counts > 9 (e.g., "aaaaaaaaaa" -> "a10")
 * Memory: Return a new allocated string.
 */
char* runLengthEncode(char* s) {
    if (!s) return NULL;
    int len= strlen(s);
    if(len==0) return calloc(1,sizeof(char));
    char* res=(char*)malloc(2*len+1);//what if a1a1a1a1\0
    int i=0;
    int write_idx=0;
    while(i<len){
        int count=1;
        //same char
        while(i+1<len && s[i]==s[i+1]){
            ++count;
            ++i;
        }
        //if next is not the same of this
        write_idx+= sprintf(res+write_idx,"%c%d",s[i],count);//return寫入的字元數
        ++i;
    }
    res[write_idx]='\0';//in the end need to \0
    return res;
}

/*
 * Twist 2: Implement the Decoder
 * Input: "a3b2c3a1" -> Output: "aaabbccca"
 * Memory: Return a new allocated string.
 */
char* runLengthDecode(char* s) {
    if (!s) return NULL;
    int len= strlen(s);
    if(len==0) return calloc(1,1);
    //1st pass: count the total len for the count
    int i=0;
    int totalCount=0;
    while(i<len){
        ++i;//skip the charc
        int count=0;
        while(i<len && isdigit(s[i])){
            count=count*10 + s[i]-'0';
            ++i;
        }
        totalCount+=count;
    }

    //2nd pass: memset the chars
    char* res=(char*)malloc(totalCount+1);//+1 for the \0
    i=0;
    int write_idx=0;
    while(i<len){
        char charToRepeat=s[i];
        ++i;
        int count=0;
        while(i<len && isdigit(s[i])){
            count=count*10+s[i]-'0';
            i++;
        }
        if(count>0){
            memset(res+write_idx,charToRepeat,count);
            write_idx+=count;
        }
    }
    res[write_idx]='\0';
    return res;
}

// ==========================================
//  TEST HELPERS
// ==========================================

// Generates random string with runs of characters
// e.g., "aaabbbbcc"
char* generateRunLengthString(int len) {
    if (len <= 0) return calloc(1,1); // Empty string

    // Allocate generous buffer
    char* s = (char*)malloc(len + 1);
    int idx = 0;

    while (idx < len) {
        char c = 'a' + (rand() % 5); // Use small alphabet to ensure repeats
        int run = 1 + (rand() % 5);  // Run length 1-5

        for (int k = 0; k < run && idx < len; k++) {
            s[idx++] = c;
        }
    }
    s[len] = '\0';
    return s;
}

// ==========================================
//  TEST RUNNER
// ==========================================
void runTest(int testNum, char* testName, char* input, char* expectedEnc, int checkDecode, int* failedTests) {
    long long memBefore = g_active_allocations;

    printf("Test #%d (%-20s): ", testNum, testName);

    // --- Step 1: Encode ---
    char* encoded = runLengthEncode(input);

    int passed = 1;
    char failReason[256] = "None";

    // Basic Null Checks
    if (input != NULL && encoded == NULL) {
        passed = 0;
        sprintf(failReason, "Encoder returned NULL for valid input");
    } else if (input == NULL && encoded != NULL) {
        passed = 0;
        sprintf(failReason, "Should return NULL for NULL input");
    } else if (input != NULL) {
        // Compare with expected (if provided)
        if (expectedEnc && strcmp(encoded, expectedEnc) != 0) {
            passed = 0;
            sprintf(failReason, "Encoding mismatch.\n    Exp: %s\n    Got: %s", expectedEnc, encoded);
        }
    }

    // --- Step 2: Decode (Round Trip) ---
    char* decoded = NULL;
    if (passed && checkDecode && encoded) {
        decoded = runLengthDecode(encoded);
        if (decoded == NULL) {
            passed = 0;
            sprintf(failReason, "Decoder returned NULL");
        } else if (strcmp(input, decoded) != 0) {
            passed = 0;
            // Truncate long strings for display
            char showIn[20], showOut[20];
            strncpy(showIn, input, 15); showIn[15]='\0';
            strncpy(showOut, decoded, 15); showOut[15]='\0';
            if (strlen(input) > 15) strcat(showIn, "...");
            if (strlen(decoded) > 15) strcat(showOut, "...");

            sprintf(failReason, "Round Trip Failed (Decode(Encode(s)) != s).\n    Orig: %s\n    Decod: %s", showIn, showOut);
        }
    }

    // --- Step 3: Cleanup & Memory Check ---
    if (encoded) free(encoded);
    if (decoded) free(decoded);

    long long memAfter = g_active_allocations;

    if (passed && memAfter == memBefore) {
        printf("\033[32mPassed\033[0m\n");
    } else {
        printf("\033[31mFailed\033[0m\n");
        if (!passed) printf("  Reason: %s\n", failReason);
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

    // 1. Basic Sample
    runTest(++totalTests, "Sample 'aaabbccca'", "aaabbccca", "a3b2c3a1", 1, &failedTests);

    // 2. Single Character
    runTest(++totalTests, "Single 'a'", "a", "a1", 1, &failedTests);

    // 3. No Repeats
    runTest(++totalTests, "No Repeats 'abc'", "abc", "a1b1c1", 1, &failedTests);

    // 4. Empty String
    runTest(++totalTests, "Empty String", "", "", 1, &failedTests);

    // 5. Long Run (Testing multi-digit numbers)
    // "aaaaaaaaaa" (10 chars) -> "a10"
    runTest(++totalTests, "Run Length 10", "aaaaaaaaaa", "a10", 1, &failedTests);

    // 6. Twist: Digits in input?
    // The prompt asks "How would you solve encoding digits?". 
    // Standard RLE breaks if input is "a1b". Encodes to "a111b1"? Decoder sees "a" repeated 111 times?
    // For this basic test harness, we assume input is alphabetic only, 
    // OR that the user implementation has a specific strategy (escaping).
    // We will skip this specific edge case for the "Simple" encoder unless you implement a protocol.

    printf("\n==========================================\n");
    printf("         STRESS TESTS (Round Trip)\n");
    printf("==========================================\n");

    int stressCount = 1000;
    for (int i = 0; i < stressCount; i++) {
        int len = rand() % 50;
        char* input = generateRunLengthString(len);

        // We pass NULL for expectedEnc because we don't know it, 
        // we rely on Round Trip (Decode(Encode) == Input) to verify correctness.
        runTest(++totalTests, "Random Stress", input, NULL, 1, &failedTests);

        free(input);

        // Stop spamming console on success
        if (failedTests > 0) break;
        if (i % 200 == 0) {
            printf("\rRunning Stress Tests... %d/%d", i, stressCount);
            fflush(stdout);
        }
    }
    printf("\rStress Tests Completed.              \n");

    printf("\n==========================================\n");
    if (failedTests == 0) {
        printf("\033[32mAll Tests Passed (Logic + Memory)\033[0m\n");
    } else {
        printf("\033[31mFailed %d Tests\033[0m\n", failedTests);
    }
    printf("==========================================\n");

    return 0;
}