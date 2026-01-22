#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

// ==========================================
//  CONFIGURATION
// ==========================================
// Set to 1: Struct has 'manager' pointer (Easier, O(Depth))
// Set to 0: 'manager' pointer is hidden (Harder, requires Recursion/DFS from root)
#define ENABLE_PARENT_POINTER 0

// ==========================================
//  MEMORY TRACKING
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
//  DATA STRUCTURES
// ==========================================
typedef struct Employee {
    int id;
    char name[32];

    // Children (Reports)
    struct Employee** reports;
    int reportCount;
    int reportCapacity;

#if ENABLE_PARENT_POINTER
    struct Employee* manager; // Parent pointer
#else
    void* _hidden_manager;    // Hidden from user for Oracle verification
#endif

} Employee;

// ==========================================
//  USER SOLUTION
// ==========================================

/*
 * Find the closest common manager (LCA) for two employees.
 * * @param root: The CEO (Useful if ENABLE_PARENT_POINTER is 0)
 * @param e1: First employee
 * @param e2: Second employee
 * @return: The manager/employee who is the LCA.
 */
Employee* whoIsOurBoss(Employee* root, Employee* e1, Employee* e2) {
    if (!e1 || !e2) return NULL;
    // ---------------------------------------------------------
    // STRATEGY 1: Bottom-Up (Using Manager Pointers)
    // Complexity: O(Depth)
    // ---------------------------------------------------------
#if ENABLE_PARENT_POINTER

    // TODO: Implement Intersection of two Linked Lists logic here
    // 1. Find depth of e1 and e2
    // 2. Move deeper node up until levels match
    // 3. Move both up until they collide
    Employee* e1_cur=e1;
    Employee* e2_cur=e2;

    while(e1_cur!=e2_cur){
        if(e1_cur->manager) e1_cur=e1_cur->manager;
        else e1_cur=e2;
        if(e2_cur->manager) e2_cur=e2_cur->manager;
        else e2_cur=e1;
    }
    return e1_cur; // Placeholder

#else
    // ---------------------------------------------------------
    // STRATEGY 2: Top-Down (Recursive / No Parent Pointers)
    // Complexity: O(N)
    // Twist: "Remove the manager pointer"
    // ---------------------------------------------------------
        //base case
        if (!root) return NULL;
        if (root == e1 || root == e2) return root;//真正找到的 base case
        //sh for team members
        int count=0;
        Employee* likely_boss=NULL;
        for(int i=0;i<root->reportCount;i++){
            Employee* res= whoIsOurBoss(root->reports[i],e1,e2);//往下找 target 不變
            if(res){//if 下面有找到
                ++count;//把結果往上傳！
                likely_boss=res;
            }
        }
    if(count==2) return root;
    return likely_boss;

#endif
}

// ==========================================
//  TEST INFRASTRUCTURE
// ==========================================

// Helper: Create a Node
Employee* createEmployee(int id, const char* name) {
    Employee* e = (Employee*)calloc(1, sizeof(Employee));
    e->id = id;
    snprintf(e->name, 32, "%s", name);
    e->reportCapacity = 2;
    e->reports = (Employee**)calloc(e->reportCapacity, sizeof(Employee*));
    return e;
}

// Helper: Link Manager -> Report
void addReport(Employee* manager, Employee* report) {
    if (manager->reportCount == manager->reportCapacity) {
        manager->reportCapacity *= 2;
        manager->reports = (Employee**)realloc(manager->reports, manager->reportCapacity * sizeof(Employee*));
    }
    manager->reports[manager->reportCount++] = report;

#if ENABLE_PARENT_POINTER
    report->manager = manager;
#else
    report->_hidden_manager = manager; // Keep a secret copy for the Oracle
#endif
}

// Helper: Recursive Cleanup
void freeHierarchy(Employee* root) {
    if (!root) return;
    for (int i = 0; i < root->reportCount; i++) {
        freeHierarchy(root->reports[i]);
    }
    free(root->reports);
    free(root);
}

// ==========================================
//  ORACLE (TRUSTED REFERENCE SOLVER)
// ==========================================
// We use the hidden parent pointers to verify the user's answer
// regardless of which method they implemented.
Employee* getInternalManager(Employee* e) {
#if ENABLE_PARENT_POINTER
    return e->manager;
#else
    return (Employee*)e->_hidden_manager;
#endif
}

int getDepth(Employee* e) {
    int d = 0;
    while (e) {
        e = getInternalManager(e);
        d++;
    }
    return d;
}

Employee* referenceLCA(Employee* e1, Employee* e2) {
    if (!e1 || !e2) return NULL;
    int d1 = getDepth(e1);
    int d2 = getDepth(e2);

    // Equalize levels
    while (d1 > d2) { e1 = getInternalManager(e1); d1--; }
    while (d2 > d1) { e2 = getInternalManager(e2); d2--; }

    // March up
    while (e1 != e2) {
        e1 = getInternalManager(e1);
        e2 = getInternalManager(e2);
    }
    return e1;
}

// ==========================================
//  TEST RUNNER
// ==========================================
void runTest(int testNum, char* testName, Employee* root, Employee* e1, Employee* e2, int* failedTests) {
    printf("Test #%d (%-20s): ", testNum, testName);

    Employee* expected = referenceLCA(e1, e2);
    Employee* actual = whoIsOurBoss(root, e1, e2);

    if (actual == expected) {
        printf("\033[32mPassed\033[0m\n");
    } else {
        printf("\033[31mFailed\033[0m\n");
        printf("  E1 ID: %d, E2 ID: %d\n", e1->id, e2->id);
        printf("  Exp ID: %d (%s)\n", expected ? expected->id : -1, expected ? expected->name : "NULL");
        printf("  Got ID: %d (%s)\n", actual ? actual->id : -1, actual ? actual->name : "NULL");
        (*failedTests)++;
    }
}

// Helper: Generate a random tree with N nodes
// Returns array of pointers to all nodes for easy selection
Employee** generateRandomHierarchy(int n, Employee** outRoot) {
    Employee** nodes = (Employee**)malloc(n * sizeof(Employee*));

    // Node 0 is CEO
    nodes[0] = createEmployee(0, "CEO");

    for (int i = 1; i < n; i++) {
        char buf[32];
        sprintf(buf, "Emp%d", i);
        nodes[i] = createEmployee(i, buf);

        // Pick a random manager from existing nodes (0 to i-1)
        // This ensures no cycles and full connectivity
        int mgrIdx = rand() % i;
        addReport(nodes[mgrIdx], nodes[i]);
    }

    *outRoot = nodes[0];
    return nodes;
}

int main() {
    srand(time(0));
    int failedTests = 0, totalTests = 0;

    printf("==========================================\n");
    printf("         STANDARD TESTS\n");
    printf("==========================================\n");

    /*
          CEO (0)
          /    \
       VP1(1)   VP2(2)
       /  \       |
     M1(3) M2(4)  M3(5)
      |
     E1(6)
    */

    Employee* ceo = createEmployee(0, "CEO");
    Employee* vp1 = createEmployee(1, "VP1");
    Employee* vp2 = createEmployee(2, "VP2");
    addReport(ceo, vp1);
    addReport(ceo, vp2);

    Employee* m1 = createEmployee(3, "M1");
    Employee* m2 = createEmployee(4, "M2");
    addReport(vp1, m1);
    addReport(vp1, m2);

    Employee* m3 = createEmployee(5, "M3");
    addReport(vp2, m3);

    Employee* e1 = createEmployee(6, "E1");
    addReport(m1, e1);

    // Test 1: Common Manager is direct parent (Siblings)
    runTest(++totalTests, "Siblings (M1, M2)", ceo, m1, m2, &failedTests);

    // Test 2: Common Manager is Grandparent (Cousins)
    runTest(++totalTests, "Cousins (M1, M3)", ceo, m1, m3, &failedTests);

    // Test 3: Ancestry (E1 reports to M1, LCA is M1)
    // Edge case: "One employee manages the other"
    runTest(++totalTests, "Manager & Report", ceo, m1, e1, &failedTests);

    // Test 4: Deep path
    runTest(++totalTests, "Deep (E1, VP2)", ceo, e1, vp2, &failedTests);

    // Test 5: Same node
    runTest(++totalTests, "Same Node", ceo, e1, e1, &failedTests);

    // Clean up Standard
    freeHierarchy(ceo);

    printf("\n==========================================\n");
    printf("         STRESS TESTS\n");
    printf("==========================================\n");

    int stressCount = 500;
    for (int i = 0; i < stressCount; i++) {
        int n = 10 + rand() % 90; // Tree size 10-100
        Employee* root = NULL;
        Employee** nodes = generateRandomHierarchy(n, &root);

        // Pick two random employees
        Employee* a = nodes[rand() % n];
        Employee* b = nodes[rand() % n];

        runTest(++totalTests, "Random Tree", root, a, b, &failedTests);

        // Cleanup
        freeHierarchy(root);
        free(nodes); // Free the array of pointers, not the nodes (freeHierarchy does that)

        if (failedTests > 0) break;
        if (i % 50 == 0) {
            printf("\rRunning Stress Tests... %d/%d", i, stressCount);
            fflush(stdout);
        }
    }
    printf("\rStress Tests Completed.              \n");

    printf("\n==========================================\n");
    if (failedTests == 0) {
        printf("\033[32mAll Tests Passed\033[0m\n");
    } else {
        printf("\033[31mFailed %d Tests\033[0m\n", failedTests);
    }

    // Check for internal leaks in Harness
    if (g_active_allocations != 0) {
        printf("\033[31m[WARNING] Memory Leak Detected: %lld allocs remaining\033[0m\n", g_active_allocations);
    } else {
        printf("Memory Clean: OK\n");
    }
    printf("==========================================\n");

    return 0;
}