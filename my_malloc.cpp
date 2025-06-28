// my_malloc.cpp
#include <unistd.h>    // sbrk()
#include <cstddef>     // size_t
#include <cstdio>      // printf
#include <cassert>

struct __attribute__((packed)) BlockHeader {
    size_t size;               // payload 大小 (不含 header), 8byte
    bool   free;               // 空閒標記, 1byte
    BlockHeader *next;         // free list 指標, 8byte
};

static BlockHeader *free_list = nullptr;

constexpr size_t HEADER_SIZE = sizeof(BlockHeader);

// 在 free_list 上以 first‐fit 找適合大小的區塊
static BlockHeader* find_free_block(size_t n) {
    BlockHeader *prev = nullptr, *curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= n) {
            // 從鏈上摘下
            if (prev) prev->next = curr->next;
            else       free_list = curr->next;
            curr->free = false;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return nullptr;
}

// 向 OS 申請 (HEADER_SIZE + n) bytes，回傳剛分配的 header
static BlockHeader* request_space(size_t n) {
    // 先取得當前的堆尾
    void *old_brk = sbrk(0);
    if (old_brk == (void*)-1) return nullptr;
    // 要申請的總大小
    size_t total = HEADER_SIZE + n;
    void *p = sbrk(total);
    if (p == (void*)-1) return nullptr;
    printf("old:%p, new:%p\n",p, sbrk(0));
    // 在 old_brk 寫 header，payload 就從 (old_brk + HEADER_SIZE) 開始
    BlockHeader *h = (BlockHeader*)old_brk;
    h->size = n;
    h->free = false;
    h->next = nullptr;
    return h;
}

// 類似 malloc
extern "C" void* my_malloc(size_t n) {
    if (n == 0) return nullptr;
    // 1. 試著找 free list 上的空閒區塊
    BlockHeader *blk = find_free_block(n);
    if (!blk) {
        // 2. 找不到就向 OS 申請新空間
        blk = request_space(n);
        if (!blk) return nullptr;
    }
    // 3. 回傳 payload 開頭 (跳過 header)
    return (void*)((char*)blk + HEADER_SIZE);
}

// 類似 free
extern "C" void my_free(void *ptr) {
    if (!ptr) return;
    // 計算出 header 位址
    BlockHeader *h = (BlockHeader*)((char*)ptr - HEADER_SIZE);
    h->free = true;
    // 插入 free_list 鏈頭
    h->next = free_list;
    free_list = h;
}

// （選填）示範用的簡單 main

int main() {
    char *p1 = (char*)my_malloc(100);
    assert(p1);
    snprintf(p1, 100, "Hello, my_malloc!");
    printf("%s\n", p1);

    char *p2 = (char*)my_malloc(200);
    assert(p2);
    snprintf(p2, 200, "Another block.");
    printf("%s\n", p2);

    my_free(p1);
    my_free(p2);

    char *p3 = (char*)my_malloc(50);
    assert(p3);
    snprintf(p3, 50, "Reused or new block.");
    printf("%s\n", p3);

    return 0;
}
