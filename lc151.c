#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義 mainTest
#define mainTest main

// 顏色定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// --- 輔助函式 ---
// 提示：這是一個標準的 helper，用來翻轉字串 s 在 [left, right] 區間的字元
// 例如 reverse(s, 0, 2) 把 "abc" 變成 "cba"
void pure_inplace_reverse(char* str,int st,int ed){
    while(st<ed){
        char stc=str[st];
        str[st]=str[ed];
        str[ed]=stc;
        st++;
        ed--;
    }
}
void del_extra_sace(char* str){
    int len=strlen(str);
    int slow=0;
    //重新鍛造 string
    for(int fast=0;fast<len;fast++){
        if(str[fast]==' ') continue;
        if(slow!=0) str[slow++]=' ';
        //move the words
        while(fast<len && str[fast]!=' ') str[slow++]=str[fast++];
    }
    str[slow]='\0';
}
// --- 主要解題函式 ---
char* reverseWords(char* str){
    //remove extra whiet space
    del_extra_sace(str);
    int len= strlen(str);
    int loc_st=0,loc_ed=0;
    pure_inplace_reverse(str,0,len-1);
    //reverse each word
    for(;loc_ed<=len;loc_ed++){
        if(str[loc_ed]!=' ' && str[loc_ed]!='\0') continue;
        pure_inplace_reverse(str,loc_st,loc_ed-1);
        loc_st=loc_ed+1;
    }
    return str;
}

// --- 測試框架 ---
void runTest(const char* input, const char* expected) {
    // [重要] 因為我們要原地修改 (In-place)，不能直接傳入字串常數
    // 使用 strdup 複製一份到 Heap 記憶體
    char* mutableString = strdup(input);

    printf("Input: [\"%s\"] -> ", input);

    char* result = reverseWords(mutableString);

    if (result != NULL && strcmp(result, expected) == 0) {
        printf("Got: [\"%s\"] %sPASS%s\n", result, COLOR_GREEN, COLOR_RESET);
    } else {
        printf("Got: [\"%s\"] Expected: [\"%s\"] %sFAIL%s\n", result == NULL ? "NULL" : result, expected, COLOR_RED, COLOR_RESET);
    }

    free(mutableString); // 釋放記憶體
}

int mainTest() {
    printf("=== LeetCode 151 Skeleton Test ===\n");

    // Test Case 1: 標準
    runTest("the sky is blue", "blue is sky the");

    // Test Case 2: 前後有空白
    runTest("  hello world  ", "world hello");

    // Test Case 3: 中間有多個空白
    runTest("a good   example", "example good a");

    return 0;
}