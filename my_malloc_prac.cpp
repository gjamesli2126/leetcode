#include <unistd.h>    // sbrk()
#include <cstddef>     // size_t
#include <cstdio>      // printf
#include <cassert>
#define testMain main

// Declarations of our custom allocator functions:
extern "C" {
    void* my_malloc(size_t n);
    void  my_free(void* ptr);
}
struct BlockHeader{
    size_t size:63;
    size_t free:1;
    BlockHeader* next;
};
BlockHeader* freeList= nullptr;
constexpr size_t HEADERSIZE= sizeof(BlockHeader);
void* findNextFreeBlock(size_t n){
    BlockHeader* cur=freeList,*prev;
    while(cur){
        //if have
        if(cur->free && cur->size>=n){
            cur->free= false;
            //rm this part from the linkedList
            if(prev) prev->next=cur->next;
            else freeList=cur->next;
            return cur;
        }
        prev=cur;
        cur=cur->next;
    }
    return nullptr;
}
struct BlockHeader* allocMem(size_t n){
    void* old_ptr=sbrk(0);
    if(old_ptr==(void*)-1) return nullptr;
    size_t total=HEADERSIZE+n;
    void* still_old_ptr= sbrk(total);
    if(still_old_ptr==(void*)-1) return nullptr;
    struct BlockHeader* h=(BlockHeader*) still_old_ptr;
    h->size=n;
    h->free= false;
    h->next= nullptr;
    return h;
}
void* my_malloc(size_t n){
    if(!n) return nullptr;
    //first find if it exists in the freelist
    void* p= findNextFreeBlock(n);
    //if not then create one
    if(p) printf("Found a free mem block with size:%u!\n",((BlockHeader*)p)->size);
    if(!p){
        p= allocMem(n);
        printf("Alloc new mem\n");
    }
    return (void*)((char*)p+HEADERSIZE);
}
void my_free(void* ptr){
    if(!ptr) return;
    //calc out the addr of the block
    BlockHeader* blk=(BlockHeader*)((char*)ptr-HEADERSIZE);
    blk->free=true;
    blk->next=freeList;
    freeList=blk;
}

int testMain() {
    // 1) Allocate 100 bytes
    char* p1 = (char*) my_malloc(100);
    assert(p1 != nullptr);
    printf("Test1: malloc(100) succeeded, p1 = %p\n", (void*)p1);

    // 2) Allocate 200 bytes
    char* p2 = (char*) my_malloc(200);
    assert(p2 != nullptr);
    printf("Test2: malloc(200) succeeded, p2 = %p\n", (void*)p2);
    // 3) Free p1
    my_free(p1);
    printf("Test3: free(p1) done\n");

    // 4) Allocate 50 bytes
    char* p3 = (char*) my_malloc(50);
    assert(p3 != nullptr);
    printf("Test4: malloc(50) succeeded, p3 = %p\n", (void*)p3);

    // 5) Free p2 and p3
    my_free(p2);
    my_free(p3);
    printf("Test5: free(p2) and free(p3) done\n");

    // 6) Allocate 150 bytes
    char* p4 = (char*) my_malloc(150);
    assert(p4 != nullptr);
    printf("Test6: malloc(150) succeeded, p4 = %p\n", (void*)p4);

    // 7) Clean up
    my_free(p4);
    printf("Test7: free(p4) done\n");

    printf("All malloc/free tests passed (only success checked).\n");
    return 0;
}