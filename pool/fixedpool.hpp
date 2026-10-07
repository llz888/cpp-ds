#pragma once
#include <cstddef>

struct FreeNode {
    FreeNode* next;
};

class FixedPool {
private:
    char*     memory_;      
    size_t    blockSize_;   
    size_t    count_;       
    FreeNode* freeHead_;   

public:
    FixedPool(size_t blockSize, size_t count) : blockSize_(blockSize),count_(count){
        freeHead_ = nullptr;
        memory_ = new char[blockSize*count];
        char* p = memory_;
        for(size_t i=0;i<count_;++i){
            FreeNode* node = (FreeNode*) p;
            node->next = freeHead_;
            freeHead_ = node;
            p+=blockSize_;
            
        }

    }

    ~FixedPool() {
        delete[] memory_;
    }

    void* allocate() {
        // 你写：摘链表头。链表空了返回 nullptr
        if(!freeHead_) return freeHead_;
        FreeNode* node = freeHead_;
        freeHead_ = node->next;
        return node;
    }

    void deallocate(void* p) {
        ((FreeNode*)p)-> next = freeHead_;
        freeHead_ = (FreeNode*)p;

    }
};