#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義你的 mainTest macro
#define mainTest main

// 顏色定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// 1. Find 函式 (標準配備)
int find(int* parent, int x) {
    if (parent[x] != x) parent[x] = find(parent, parent[x]);
    return parent[x];
}

// 2. Unite 函式 (標準配備 - 修正過)
// 考試重點：這裡面一定要操作 root_x, root_y，不要操作 x, y
void unite(int* parent, int* rank, int x, int y, int* count) {
    int root_x = find(parent, x); // 在這裡找老大
    int root_y = find(parent, y); // 在這裡找老大

    if (root_x != root_y) {
        (*count)--; // 幫派少一個
        // Union by Rank (或是直接 parent[root_x] = root_y 偷懶也可以)
        if (rank[root_x] < rank[root_y]) parent[root_x] = root_y;
        else if (rank[root_x] > rank[root_y]) parent[root_y] = root_x;
        else {
            parent[root_x] = root_y;//老大比較高
            rank[root_y]++;
        }
    }
}

// 3. 主函式 (乾淨版)
int minSwapsCouples(int* row, int rowSize) {
    int N = rowSize / 2;
    int tree_num = N; // 一開始有 N 個獨立幫派

    // 記憶體配置 (背誦重點：malloc int * N)
    int* parent = (int*)malloc(sizeof(int) * N);
    int* rank = (int*)calloc(N, sizeof(int));
    for(int i=0; i<N; i++) parent[i] = i;

    // 遍歷沙發 (背誦重點：i+=2)
    for (int i = 0; i < rowSize; i += 2) {
        int cpl1 = row[i] / 2;     // 左邊那個人屬於哪一對
        int cpl2 = row[i+1] / 2;   // 右邊那個人屬於哪一對

        // 直接叫 unite，不用在外面 find，好背！
        unite(parent, rank, cpl1, cpl2, &tree_num);
    }

    // 釋放記憶體 (容易忘記，但加分)
    free(parent);
    free(rank);

    return N - tree_num; // 公式：總對數 - 剩下的幫派數
//    我們的目標是要有 N 個獨立的組。因為每交換一次就會「多產生」一個組，所以需要的交換次數就是 N 減去目前的組數。
}

// 輔助測試函數
void runTest(int* inputRow, int size, int expected) {
    // 因為 minSwapsCouples 可能會修改陣列 (交換)，所以我們複製一份來跑
    int* tempRow = (int*)malloc(size * sizeof(int));
    memcpy(tempRow, inputRow, size * sizeof(int));

    printf("Test Input: [");
    for(int i=0; i<size; i++) printf("%d%s", inputRow[i], (i==size-1)? "":",");
    printf("] -> Expected: %d -> ", expected);

    int result = minSwapsCouples(tempRow, size);

    if (result == expected) {
        printf("%sPASS%s\n", COLOR_GREEN, COLOR_RESET);
    } else {
        printf("%sFAIL (Got: %d)%s\n", COLOR_RED, result, COLOR_RESET);
    }

    free(tempRow);
}

int mainTest() {
    printf("=== Running Tests for minSwapsCouples ===\n");

    // Test Case 1
    int row1[] = {0, 2, 1, 3};
    runTest(row1, 4, 1);

    // Test Case 2
    int row2[] = {3, 2, 0, 1};
    runTest(row2, 4, 0);

    // Test Case 3: Custom Case (需要交換兩次)
    // (0,1) 分開, (2,3) 分開 -> [0, 2, 1, 3] 是 1 次
    // [0, 2, 3, 4, 5, 1] -> 0的伴侶是1(在最後), 2的伴侶是3(在原位), 4的伴侶是5(在原位)
    // 這種情況交換一次 1 和 2 即可歸位? 不，我們試一個複雜點的
    // [5, 4, 2, 6, 3, 1, 0, 7]
    // 期待值取決於算法，但可以用已知答案測試

    return 0;
}