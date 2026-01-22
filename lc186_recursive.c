#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義 mainTest
#define mainTest main

// 顏色定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

//recursivly
//直接rotate 一個word 然後專 rnext word-->NO, rotate 會導致 N^2
//還是用我原本 iter的方法 只是把 for each 反轉word變成 recursive
//這題不用考慮字串尾 \0
void reverse(char* s,int st,int end){
    while(st<end) {
        char stc = s[st];
        s[st] = s[end];
        s[end] = stc;
        st++;
        end--;
    }
}
void reverseEachWord(char* s,int st,int sSize){
    if(st>=sSize) return;
    //到 space時開始處理
    int end=st;
    while(end<sSize && s[end]!=' ') end++;
    reverse(s,st,end-1);
    reverseEachWord(s,end+1,sSize);
}
void reverseWords(char* s, int sSize) {
    //reverse the whole shit
    reverse(s,0,sSize-1);
    //recusively reverse each word
    reverseEachWord(s,0,sSize);
}

// --- 測試框架 ---
void runTest(const char* inputStr, const char* expectedStr) {
    // 準備測試資料
    int len = strlen(inputStr);

    // 因為是 In-place 修改，必須複製一份可寫入的記憶體
    char* mutableS = (char*)malloc((len + 1) * sizeof(char));
    strcpy(mutableS, inputStr);

    printf("Input: [\"%s\"] -> ", inputStr);

    // 呼叫解題函式
    reverseWords(mutableS, len);

    // 驗證結果
    if (strncmp(mutableS, expectedStr, len) == 0) {
        printf("Got: [\"%s\"] %sPASS%s\n", mutableS, COLOR_GREEN, COLOR_RESET);
    } else {
        printf("Got: [\"%s\"] Expected: [\"%s\"] %sFAIL%s\n", mutableS, expectedStr, COLOR_RED, COLOR_RESET);
    }

    free(mutableS);
}

int mainTest() {
    printf("=== LeetCode 186 Skeleton Test ===\n");

    // Test Case 1
    runTest("the sky is blue", "blue is sky the");

    // Test Case 2: 單一字母
    runTest("a", "a");

    // Test Case 3: 較長的句子
    runTest("hello world from C", "C from world hello");

    return 0;
}