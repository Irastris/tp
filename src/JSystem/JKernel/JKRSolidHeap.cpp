#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "global.h"
#include "JSystem/JKernel/JKRPlatform.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

JKRSolidHeap* JKRSolidHeap::create(u32 size, JKRHeap* heap, bool useErrorHandler) {
    if (!heap) {
        heap = sRootHeap;
    }
    u32 solidHeapSize = ALIGN_NEXT(sizeof(JKRSolidHeap), 0x10);

    if (size == -1) {
        size = heap->getMaxAllocatableSize(0x10);
    }

    u32 alignedSize = ALIGN_PREV(size, 0x10);
    if (alignedSize < solidHeapSize)
        return NULL;

    u8* mem = (u8*)JKRAllocFromHeap(heap, alignedSize, 0x10);
    void* dataPtr = mem + solidHeapSize;
    if (!mem)
        return NULL;

    return new (mem) JKRSolidHeap(dataPtr, alignedSize - solidHeapSize, heap, useErrorHandler);
}

void JKRSolidHeap::do_destroy(void) {
    JKRHeap* parent = getParent();
    if (parent) {
        this->~JKRSolidHeap();
        JKRFreeToHeap(parent, this);
    }
}

JKRSolidHeap::JKRSolidHeap(void* start, u32 size, JKRHeap* parent, bool useErrorHandler)
    : JKRHeap(start, size, parent, useErrorHandler) {
    mFreeSize = mSize;
    mSolidHead = (u8*)mStart;
    mSolidTail = (u8*)mEnd;
    field_0x78 = NULL;
}

JKRSolidHeap::~JKRSolidHeap(void) {
    dispose();
}

s32 JKRSolidHeap::adjustSize(void) {
    int r25 = 0;
    JKRHeap* parent = getParent();
    if (parent) {
        lock();
        u32 thisSize = (uintptr_t)mStart - (uintptr_t)this;
        u32 newSize = ALIGN_NEXT(mSolidHead - mStart, 0x20);
        s32 r26 = parent->resize(this, thisSize + newSize);
        if (r26 != -1) {
            mFreeSize = 0;
            mSize = newSize;
            mEnd = mStart + mSize;
            mSolidHead = mEnd;
            mSolidTail = mEnd;
        }

        unlock();

        return thisSize + newSize;
    }

    return -1;
}

void* JKRSolidHeap::do_alloc(u32 size, int alignment) {
    lock();

    if (size < 4) {
        size = 4;
    }

    void* ptr;
    if (alignment >= 0) {
        ptr = allocFromHead(size, alignment < 4 ? 4 : alignment);
    } else {
        ptr = allocFromTail(size, -alignment < 4 ? 4 : -alignment);
    }

    unlock();
    return ptr;
}

void* JKRSolidHeap::allocFromHead(u32 size, int alignment) {
    size = ALIGN_NEXT(size, 0x4);
    void* ptr = NULL;
    u32 alignedStart = (alignment - 1 + (uintptr_t)mSolidHead) & ~(alignment - 1);
    u32 totalSize = size + (alignedStart - (uintptr_t)mSolidHead);
    if (totalSize <= mFreeSize) {
        ptr = (void*)alignedStart;
        mSolidHead += totalSize;
        mFreeSize -= totalSize;
    } else {
        if (getErrorFlag() == true) {
            callErrorHandler(this, size, alignment);
        }
    }

    return ptr;
}

void* JKRSolidHeap::allocFromTail(u32 size, int alignment) {
    size = ALIGN_NEXT(size, 4);
    void* ptr = NULL;
    u32 alignedStart = ALIGN_PREV((uintptr_t)mSolidTail - size, alignment);
    u32 totalSize = (uintptr_t)mSolidTail - (uintptr_t)alignedStart;
    if (totalSize <= mFreeSize) {
        ptr = (void*)alignedStart;
        mSolidTail -= totalSize;
        mFreeSize -= totalSize;
    } else {
        if (getErrorFlag() == true) {
            callErrorHandler(this, size, alignment);
        }
    }
    return ptr;
}

void JKRSolidHeap::do_free(void* ptr) {
    // No-op
}

void JKRSolidHeap::do_freeAll(void) {
    lock();
    this->JKRHeap::callAllDisposer();
    mFreeSize = mSize;
    mSolidHead = (u8*)mStart;
    mSolidTail = (u8*)mEnd;
    field_0x78 = NULL;
    unlock();
}

void JKRSolidHeap::do_freeTail(void) {
    lock();

    if (mSolidTail != mEnd) {
        dispose(mSolidTail, mEnd);
    }

    this->mFreeSize = ((uintptr_t)mEnd - (uintptr_t)mSolidTail + mFreeSize);
    this->mSolidTail = mEnd;

    for (JKRSolidHeap::Unknown* unknown = field_0x78; unknown; unknown = unknown->mNext) {
        unknown->field_0xc = mEnd;
    }

    unlock();
}

s32 JKRSolidHeap::do_resize(void* ptr, u32 newSize) {
    return -1;
}

s32 JKRSolidHeap::do_getSize(void* ptr) {
    return -1;
}

bool JKRSolidHeap::check(void) {
    lock();

    bool result = true;
    u32 calculatedSize = (mSolidHead - mStart) + mFreeSize + (mEnd - mSolidTail);
    if (calculatedSize != mSize) {
        result = false;
    }

    unlock();
    return result;
}

bool JKRSolidHeap::dump(void) {
    bool result = check();

    lock();
    s32 htSize = (mSolidHead - mStart) + (mEnd - mSolidTail);
    unlock();

    return result;
}

u32 JKRSolidHeap::getHeapType(void) {
    return 'SLID';
}

s32 JKRSolidHeap::do_getFreeSize(void) {
    return mFreeSize;
}

void* JKRSolidHeap::do_getMaxFreeBlock(void) {
    return mSolidHead;
}

s32 JKRSolidHeap::do_getTotalFreeSize(void) {
    return getFreeSize();
}
