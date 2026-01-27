#ifndef JKRSOLIDHEAP_H
#define JKRSOLIDHEAP_H

#include "JSystem/JKernel/JKRHeap.h"

class JKRSolidHeap : public JKRHeap {
public:
    struct Unknown {
        u32 field_0x0;
        u32 field_0x4;
        u32 field_0x8;
        void* field_0xc;
        Unknown* mNext;
    };

protected:
    JKRSolidHeap(void*, u32, JKRHeap*, bool);
    virtual ~JKRSolidHeap();

    void* allocFromHead(u32, int);
    void* allocFromTail(u32, int);

    static s32 getUsedSize(JKRSolidHeap* heap) { return heap->mSize - heap->getTotalFreeSize(); }

public:
    virtual u32 getHeapType(void);
    virtual bool check(void);

    virtual bool dump(void);
    virtual void do_destroy(void);
    virtual void* do_alloc(u32, int);
    virtual void do_free(void*);
    virtual void do_freeAll(void);
    virtual void do_freeTail(void);
    virtual s32 do_resize(void*, u32);
    virtual s32 do_getSize(void*);
    virtual s32 do_getFreeSize(void);
    virtual void* do_getMaxFreeBlock(void);
    virtual s32 do_getTotalFreeSize(void);

private:
    u32 mFreeSize;
    u8* mSolidHead;
    u8* mSolidTail;
    Unknown* field_0x78;

public:
    s32 adjustSize(void);

    static JKRSolidHeap* create(u32, JKRHeap*, bool);

    static void* getState_(TState* state) { return getState_buf_(state); }
};

inline JKRSolidHeap* JKRCreateSolidHeap(u32 param_0, JKRHeap* heap, bool param_2) {
    return JKRSolidHeap::create(param_0, heap, param_2);
}

inline void JKRDestroySolidHeap(JKRSolidHeap* heap) {
    heap->destroy();
}

#endif
