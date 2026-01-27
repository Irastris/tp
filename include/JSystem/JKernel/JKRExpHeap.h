#ifndef JKREXPHEAP_H
#define JKREXPHEAP_H

#include <stdint.h>

#include <dolphin/types.h>

#include "global.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRPlatform.h"

class JKRExpHeap : public JKRHeap {
public:
    enum EAllocMode {
        ALLOC_MODE_1 = 1,
    };

    class CMemBlock {
        friend class JKRExpHeap;

    public:
        void initiate(CMemBlock* prev, CMemBlock* next, u32 size, u8 groupId, u8 alignment);
        JKRExpHeap::CMemBlock* allocFore(u32 size, u8 groupId1, u8 alignment1, u8 groupId2,
                                         u8 alignment2);
        JKRExpHeap::CMemBlock* allocBack(u32 size, u8 groupId1, u8 alignment1, u8 groupId2,
                                         u8 alignment2);
        int free(JKRExpHeap* heap);
        static CMemBlock* getHeapBlock(void* ptr);

        void newGroupId(u8 groupId) { mGroupId = groupId; }
        bool isValid() const { return mMagic == 'HM'; }
        bool isTempMemBlock() const { return mFlags & 0x80; }
        int getAlignment() const { return mFlags & 0x7f; }
        void* getContent() const { return (void*)(this + 1); }
        CMemBlock* getPrevBlock() const { return mPrev; }
        CMemBlock* getNextBlock() const { return mNext; }
        u32 getSize() const { return size; }
        u8 getGroupId() const { return mGroupId; }
        static CMemBlock* getBlock(void* data) { return (CMemBlock*)((uintptr_t)data + -0x10); }

    private:
        u16 mMagic;
        u8 mFlags;  // a|bbbbbbb a=temporary b=alignment
        u8 mGroupId;
        u32 size;
        CMemBlock* mPrev;
        CMemBlock* mNext;
    };  // Size: 0x10
    friend class CMemBlock;

protected:
    JKRExpHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag);
    virtual ~JKRExpHeap();

    void* allocFromHead(u32 size, int align);
    void* allocFromHead(u32 size);
    void* allocFromTail(u32 size, int align);
    void* allocFromTail(u32 size);
    void appendUsedList(CMemBlock* newblock);
    void setFreeBlock(CMemBlock* block, CMemBlock* prev, CMemBlock* next);
    void removeFreeBlock(CMemBlock* block);
    void removeUsedBlock(CMemBlock* block);
    void recycleFreeBlock(CMemBlock* block);
    void joinTwoBlocks(CMemBlock* block);

public:
    BOOL isEmpty();
    s32 getUsedSize(u8 groupId) const;
    s32 getTotalUsedSize(void) const;
    
    CMemBlock* getUsedFirst() { return mHeadUsedList; }
    void setAllocationMode(EAllocMode mode) {
        mAllocMode = mode;
    }

public:
    virtual u32 getHeapType();
    virtual bool check();
    virtual void do_destroy();
    virtual void* do_alloc(u32 size, int alignment);
    virtual void do_free(void* ptr);
    virtual void do_freeAll();
    virtual void do_freeTail();
    virtual s32 do_resize(void* ptr, u32 size);
    virtual s32 do_getSize(void* ptr);
    virtual s32 do_getFreeSize();
    virtual void* do_getMaxFreeBlock();
    virtual s32 do_getTotalFreeSize();
    virtual s32 do_changeGroupID(u8 newGroupID);
    virtual u8 do_getCurrentGroupId();

    u8 mAllocMode;
    u8 mCurrentGroupId;
    bool field_0x6e;

private:
    void* field_0x70;
    u32 field_0x74;
    CMemBlock* mHeadFreeList;
    CMemBlock* mTailFreeList;
    CMemBlock* mHeadUsedList;
    CMemBlock* mTailUsedList;

public:
    static JKRExpHeap* createRoot(int maxHeaps, bool errorFlag);
    static JKRExpHeap* create(u32 size, JKRHeap* parent, bool errorFlag);
    static JKRExpHeap* create(void* ptr, u32 size, JKRHeap* parent, bool errorFlag);

    static s32 getUsedSize_(JKRExpHeap* heap) { return heap->mSize - heap->getTotalFreeSize(); }
    static void* getState_(TState* state) { return getState_buf_(state); }
};

inline JKRExpHeap* JKRCreateExpHeap(u32 size, JKRHeap* parent, bool errorFlag) {
    return JKRExpHeap::create(size, parent, errorFlag);
}

inline void JKRDestroyExpHeap(JKRExpHeap* heap) {
    heap->destroy();
}

#endif
