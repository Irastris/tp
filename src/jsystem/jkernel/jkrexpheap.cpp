#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#include "jsystem/jkernel/jkrexpheap.h"
#include "jsystem/jkernel/jkrplatform.h"

JKRExpHeap* JKRExpHeap::createRoot(int maxHeaps, bool errorFlag) {
    JKRExpHeap* heap = NULL;
    if (!sRootHeap) {
        void* mem1;
        u32 mem1Size;
        initArena((char**)&mem1, &mem1Size, maxHeaps);
        u32 local_3c = ALIGN_NEXT(sizeof(JKRExpHeap), 0x10);
        u8* start1 = (u8*)mem1 + local_3c;
        u32 alignedSize = mem1Size - local_3c;
        heap = new (mem1) JKRExpHeap(start1, alignedSize, NULL, errorFlag);
        sRootHeap = heap;
    }
    heap->field_0x6e = true;
    return heap;
}

JKRExpHeap* JKRExpHeap::create(u32 size, JKRHeap* parent, bool errorFlag) {
    JKRExpHeap* newHeap = NULL;
    if (!parent) {
        parent = sRootHeap;
    }
    u32 expHeapSize = ALIGN_NEXT(sizeof(JKRExpHeap), 0x10);
    u32 blockSize = sizeof(CMemBlock);

    if (size == 0xffffffff) {
        size = parent->getMaxAllocatableSize(0x10);
    }

    u32 alignedSize = ALIGN_PREV(size, 0x10);

    if (alignedSize < expHeapSize + blockSize)
        return NULL;

    u8* memory = (u8*)JKRAllocFromHeap(parent, alignedSize, 0x10);
    u8* dataPtr = (memory + expHeapSize);
    if (!memory) {
        return NULL;
    }

    newHeap = new (memory) JKRExpHeap(dataPtr, alignedSize - expHeapSize, parent, errorFlag);

    if (newHeap == NULL) {
        JKRFree(memory);
        return NULL;
    }

    newHeap->field_0x6e = false;
    return newHeap;
}

JKRExpHeap* JKRExpHeap::create(void* ptr, u32 size, JKRHeap* parent, bool errorFlag) {
    JKRHeap* parent2;
    if (parent == NULL) {
        parent2 = getRootHeap()->find(ptr);
        if (!parent2)
            return NULL;
    } else {
        parent2 = parent;
    }

    JKRExpHeap* newHeap = NULL;
    u32 expHeapSize = ALIGN_NEXT(sizeof(JKRExpHeap), 0x10);
    if (size < expHeapSize)
        return NULL;

    u8* r28 = (u8*)ptr;
    u8* dataPtr = r28 + expHeapSize;
    u32 alignedSize = ALIGN_PREV((uintptr_t)ptr + size - (uintptr_t)dataPtr, 0x10);
    if (r28) {
        newHeap = new (r28) JKRExpHeap(dataPtr, alignedSize, parent2, errorFlag);
    }

    newHeap->field_0x6e = true;
    newHeap->field_0x70 = ptr;
    newHeap->field_0x74 = size;
    return newHeap;
}

void JKRExpHeap::do_destroy() {
    if (!field_0x6e) {
        JKRHeap* heap = getParent();
        if (heap) {
            this->~JKRExpHeap();
            JKRFreeToHeap(heap, this);
        }
    } else {
        u8* r28 = (u8*)field_0x70;
        u32 r27 = field_0x74;
        this->~JKRExpHeap();
    }
}

JKRExpHeap::JKRExpHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag)
    : JKRHeap(data, size, parent, errorFlag) {
    mAllocMode = 0;
    mCurrentGroupId = 0xff;
    mHeadFreeList = (CMemBlock*)data;
    mTailFreeList = mHeadFreeList;
    mHeadFreeList->initiate(NULL, NULL, size - sizeof(CMemBlock), 0, 0);
    mHeadUsedList = NULL;
    mTailUsedList = NULL;
}

JKRExpHeap::~JKRExpHeap() {
    dispose();
}

void* JKRExpHeap::do_alloc(u32 size, int alignment) {
    lock();

    if (size < 4) {
        size = 4;
    }

    void* ptr = NULL;

    if (alignment >= 0) {
        if (alignment <= 4) {
            ptr = allocFromHead(size);
        } else {
            ptr = allocFromHead(size, alignment);
        }
    } else {
        if (-alignment <= 4) {
            ptr = allocFromTail(size);
        } else {
            ptr = allocFromTail(size, -alignment);
        }
    }

    if (ptr == NULL) {
        if (getErrorFlag() == true) {
            callErrorHandler(this, size, alignment);
        }
    }

    unlock();

    return ptr;
}

static u32 DBfoundSize;

static u32 DBfoundOffset;

static JKRExpHeap::CMemBlock* DBfoundBlock;

static JKRExpHeap::CMemBlock* DBnewFreeBlock;

static JKRExpHeap::CMemBlock* DBnewUsedBlock;

void* JKRExpHeap::allocFromHead(u32 size, int align) {
    u32 foundOffset;
    int foundSize;

    size = ALIGN_NEXT(size, 4);
    foundSize = -1;
    foundOffset = 0;
    CMemBlock* foundBlock = NULL;
    CMemBlock* newFreeBlock = NULL;
    CMemBlock* newUsedBlock = NULL;

    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        u32 offset =
            ALIGN_PREV(align - 1 + (uintptr_t)block->getContent(), align) - (uintptr_t)block->getContent();
        if (block->size < size + offset) {
            continue;
        }

        if (foundSize <= (u32)block->size) {
            continue;
        }

        foundSize = block->size;
        foundBlock = block;
        foundOffset = offset;
        if (mAllocMode != 0) {
            break;
        }

        if (foundSize == size) {
            break;
        }
    }

    DBfoundSize = foundSize;
    DBfoundOffset = foundOffset;
    DBfoundBlock = foundBlock;

    if (foundBlock) {
        if (foundOffset >= sizeof(CMemBlock)) {
            CMemBlock* prev = foundBlock->mPrev;
            CMemBlock* next = foundBlock->mNext;
            newUsedBlock = foundBlock->allocFore(foundOffset - sizeof(CMemBlock), 0, 0, 0, 0);

            if (newUsedBlock) {
                newFreeBlock = newUsedBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
            } else {
                newFreeBlock = NULL;
            }

            if (newFreeBlock) {
                setFreeBlock(foundBlock, prev, newFreeBlock);
            } else {
                setFreeBlock(foundBlock, prev, next);
            }

            if (newFreeBlock) {
                setFreeBlock(newFreeBlock, foundBlock, next);
            }

            appendUsedList(newUsedBlock);
            DBnewFreeBlock = newFreeBlock;
            DBnewUsedBlock = newUsedBlock;
            return newUsedBlock->getContent();
        } else {
            if (foundOffset != 0) {
                CMemBlock* prev = foundBlock->mPrev;
                CMemBlock* next = foundBlock->mNext;
                removeFreeBlock(foundBlock);
                newUsedBlock = (CMemBlock*)((uintptr_t)foundBlock + foundOffset);
                newUsedBlock->size = foundBlock->size - foundOffset;
                newFreeBlock =
                    newUsedBlock->allocFore(size, mCurrentGroupId, (u8)foundOffset, 0, 0);
                if (newFreeBlock) {
                    setFreeBlock(newFreeBlock, prev, next);
                }
                appendUsedList(newUsedBlock);
                return newUsedBlock->getContent();
            } else {
                CMemBlock* prev = foundBlock->mPrev;
                CMemBlock* next = foundBlock->mNext;

                newFreeBlock = foundBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
                removeFreeBlock(foundBlock);
                if (newFreeBlock) {
                    setFreeBlock(newFreeBlock, prev, next);
                }
                appendUsedList(foundBlock);
                return foundBlock->getContent();
            }
        }
    }

    return NULL;
}

void* JKRExpHeap::allocFromHead(u32 size) {
    size = ALIGN_NEXT(size, 4);
    s32 foundSize = -1;
    CMemBlock* foundBlock = NULL;
    CMemBlock* newblock = NULL;
    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        if (block->size < size) {
            continue;
        }

        if (foundSize <= block->size) {
            continue;
        }

        foundSize = block->size;
        foundBlock = block;
        if (mAllocMode != 0) {
            break;
        }

        if (foundSize == size) {
            break;
        }
    }

    if (foundBlock) {
        newblock = foundBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
        if (newblock) {
            setFreeBlock(newblock, foundBlock->mPrev, foundBlock->mNext);
        } else {
            removeFreeBlock(foundBlock);
        }
        appendUsedList(foundBlock);
        return foundBlock->getContent();
    }
    return NULL;
}

void* JKRExpHeap::allocFromTail(u32 size, int align) {
    u32 local_2c = 0;
    u32 offset = 0;
    CMemBlock* foundBlock = NULL;
    CMemBlock* newBlock = NULL;
    u32 usedSize;
    u32 start;

    for (CMemBlock* block = mTailFreeList; block; block = block->mPrev) {
        start = ALIGN_PREV((uintptr_t)block->getContent() + block->size - size, align);
        usedSize = (uintptr_t)block->getContent() + block->size - start;
        if (block->size >= usedSize) {
            local_2c = usedSize;
            foundBlock = block;
            offset = block->size - usedSize;
            newBlock = (CMemBlock*)start - 1;
            break;
        }
    }

    if (foundBlock != NULL) {
        if (offset >= sizeof(CMemBlock)) {
            newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, -0x80);
            foundBlock->size = foundBlock->size - usedSize - sizeof(CMemBlock);
            appendUsedList(newBlock);
            return newBlock->getContent();
        } else {
            if (offset != 0) {
                removeFreeBlock(foundBlock);
                newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, offset | 0x80);
                appendUsedList(newBlock);
                return newBlock->getContent();
            } else {
                removeFreeBlock(foundBlock);
                newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, -0x80);
                appendUsedList(newBlock);
                return newBlock->getContent();
            }
        }
    }

    return NULL;
}

void* JKRExpHeap::allocFromTail(u32 size) {
    size = ALIGN_NEXT(size, 4);
    CMemBlock* foundBlock = NULL;
    CMemBlock* freeBlock = NULL;
    CMemBlock* usedBlock = NULL;
    for (CMemBlock* block = mTailFreeList; block; block = block->mPrev) {
        if (block->size >= size) {
            foundBlock = block;
            break;
        }
    }

    if (foundBlock != NULL) {
        usedBlock = foundBlock->allocBack(size, 0, 0, mCurrentGroupId, 0);
        if (usedBlock) {
            freeBlock = foundBlock;
        } else {
            removeFreeBlock(foundBlock);
            usedBlock = foundBlock;
            freeBlock = NULL;
        }

        if (freeBlock) {
            setFreeBlock(freeBlock, foundBlock->mPrev, foundBlock->mNext);
        }
        appendUsedList(usedBlock);
        return usedBlock->getContent();
    }
    return NULL;
}

void JKRExpHeap::do_free(void* ptr) {
    lock();
    if (mStart <= ptr && ptr <= mEnd) {
        CMemBlock* block = CMemBlock::getHeapBlock(ptr);
        if (block) {
            block->free(this);
        }
    }
    unlock();
}

void JKRExpHeap::do_freeAll() {
    lock();

    JKRHeap::callAllDisposer();
    mHeadFreeList = (CMemBlock*)mStart;
    mTailFreeList = mHeadFreeList;
    mHeadFreeList->initiate(NULL, NULL, mSize - 0x10, 0, 0);
    mHeadUsedList = NULL;
    mTailUsedList = NULL;

    unlock();
}

void JKRExpHeap::do_freeTail() {
    lock();

    for (CMemBlock* block = mHeadUsedList; block != NULL;) {
        if (block->isTempMemBlock()) {
            dispose(block->getContent(), block->size);
            CMemBlock* temp = block->mNext;
            block->free(this);
            block = temp;
        } else {
            block = block->mNext;
        }
    }

    unlock();
}

s32 JKRExpHeap::do_changeGroupID(u8 param_0) {
    lock();
    u8 prev = mCurrentGroupId;
    mCurrentGroupId = param_0;
    unlock();
    return prev;
}

s32 JKRExpHeap::do_resize(void* ptr, u32 size) {
    lock();

    CMemBlock* block = CMemBlock::getHeapBlock(ptr);
    if (block == NULL || ptr < mStart || mEnd < ptr) {
        unlock();
        return -1;
    }

    size = ALIGN_NEXT(size, 4);
    if (size == block->size) {
        unlock();
        return size;
    }

    if (size > block->size) {
        CMemBlock* foundBlock = NULL;
        for (CMemBlock* freeBlock = mHeadFreeList; freeBlock; freeBlock = freeBlock->mNext) {
            if (freeBlock == (CMemBlock*)((uintptr_t)(block + 1) + block->size)) {
                foundBlock = freeBlock;
                break;
            }
        }

        if (foundBlock == NULL) {
            unlock();
            return -1;
        }

        if (size > block->size + sizeof(CMemBlock) + foundBlock->size) {
            unlock();
            return -1;
        }

        u32 local_24 = block->size;
        removeFreeBlock(foundBlock);
        block->size += foundBlock->size + sizeof(CMemBlock);
        if (block->size - size > sizeof(CMemBlock)) {
            CMemBlock* newBlock = block->allocFore(size, block->mGroupId, block->mFlags, 0, 0);
            if (newBlock) {
                recycleFreeBlock(newBlock);
            }
        }
    } else {
        if (block->size - size > sizeof(CMemBlock)) {
            CMemBlock* freeBlock = block->allocFore(size, block->mGroupId, block->mFlags, 0, 0);
            if (freeBlock) {
                recycleFreeBlock(freeBlock);
            }
        }
    }

    unlock();
    return block->size;
}

s32 JKRExpHeap::do_getSize(void* ptr) {
    lock();
    CMemBlock* block = CMemBlock::getHeapBlock(ptr);
    if (!block || ptr < mStart || mEnd < ptr) {
        unlock();
        return -1;
    }
    unlock();
    return block->size;
}

s32 JKRExpHeap::do_getFreeSize() {
    lock();
    s32 size = 0;
    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        if (size < (s32)block->size) {
            size = block->size;
        }
    }
    unlock();
    return size;
}

void* JKRExpHeap::do_getMaxFreeBlock() {
    lock();
    s32 size = 0;
    CMemBlock* res = NULL;
    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        if (size < (s32)block->size) {
            size = block->size;
            res = block;
        }
    }
    unlock();
    return res;
}

s32 JKRExpHeap::do_getTotalFreeSize() {
    u32 size = 0;
    lock();
    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        size += block->size;
    }
    unlock();
    return size;
}

s32 JKRExpHeap::getUsedSize(u8 groupId) const {
    lock();
    u32 size = 0;

    for (CMemBlock* block = mHeadUsedList; block; block = block->mNext) {
        if (block->mGroupId == groupId) {
            size += block->size + sizeof(CMemBlock);
        }
    }

    unlock();
    return size;
}

s32 JKRExpHeap::getTotalUsedSize() const {
    lock();
    u32 size = 0;

    for (CMemBlock* block = mHeadUsedList; block; block = block->mNext) {
        size += block->size + sizeof(CMemBlock);
    }

    unlock();
    return size;
}

BOOL JKRExpHeap::isEmpty() {
    lock();
    BOOL result = !mHeadUsedList ? TRUE : FALSE;
    unlock();
    return result;
}

void JKRExpHeap::appendUsedList(JKRExpHeap::CMemBlock* newblock) {
    CMemBlock* block = mTailUsedList;
    newblock->mMagic = 'HM';

    if (block) {
        block->mNext = newblock;
        newblock->mPrev = block;
    } else {
        newblock->mPrev = NULL;
    }

    mTailUsedList = newblock;
    if (!mHeadUsedList) {
        mHeadUsedList = newblock;
    }
    newblock->mNext = NULL;
}

void JKRExpHeap::setFreeBlock(CMemBlock* block, CMemBlock* prev, CMemBlock* next) {
    if (prev == NULL) {
        mHeadFreeList = block;
        block->mPrev = NULL;
    } else {
        prev->mNext = block;
        block->mPrev = prev;
    }

    if (next == NULL) {
        mTailFreeList = block;
        block->mNext = NULL;
    } else {
        next->mPrev = block;
        block->mNext = next;
    }

    block->mMagic = 0;
}

void JKRExpHeap::removeFreeBlock(CMemBlock* block) {
    CMemBlock* prev = block->mPrev;
    CMemBlock* next = block->mNext;

    if (prev == NULL) {
        mHeadFreeList = next;
    } else {
        prev->mNext = next;
    }

    if (next == NULL) {
        mTailFreeList = prev;
    } else {
        next->mPrev = prev;
    }
}

void JKRExpHeap::removeUsedBlock(JKRExpHeap::CMemBlock* block) {
    CMemBlock* prev = block->mPrev;
    CMemBlock* next = block->mNext;

    if (prev == NULL) {
        mHeadUsedList = next;
    } else {
        prev->mNext = next;
    }

    if (next == NULL) {
        mTailUsedList = prev;
    } else {
        next->mPrev = prev;
    }
}

void JKRExpHeap::recycleFreeBlock(JKRExpHeap::CMemBlock* block) {
    JKRExpHeap::CMemBlock* newBlock = block;
    int size = block->size;
    void* blockEnd = (u8*)newBlock + size;
    block->mMagic = 0;

    if ((block->mFlags & 0x7f) != 0) {
        newBlock = (CMemBlock*)((u8*)newBlock - (block->mFlags & 0x7f));
        size += (block->mFlags & 0x7f);
        blockEnd = (u8*)newBlock + size;
        newBlock->mGroupId = 0;
        newBlock->mFlags = 0;
        newBlock->size = size;
    }

    if (!mHeadFreeList) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        mHeadFreeList = newBlock;
        mTailFreeList = newBlock;
        setFreeBlock(newBlock, NULL, NULL);
        return;
    }

    if (mHeadFreeList >= blockEnd) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        setFreeBlock(newBlock, NULL, mHeadFreeList);
        joinTwoBlocks(newBlock);
        return;
    }

    if (mTailFreeList <= newBlock) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        setFreeBlock(newBlock, mTailFreeList, NULL);
        joinTwoBlocks(newBlock->mPrev);
        return;
    }

    for (CMemBlock* freeBlock = mHeadFreeList; freeBlock; freeBlock = freeBlock->mNext) {
        if (freeBlock >= newBlock || newBlock >= freeBlock->mNext) {
            continue;
        }
        newBlock->mNext = freeBlock->mNext;
        newBlock->mPrev = freeBlock;
        freeBlock->mNext = newBlock;
        newBlock->mNext->mPrev = newBlock;
        newBlock->mGroupId = 0;
        joinTwoBlocks(newBlock);
        joinTwoBlocks(freeBlock);
        return;
    }
}

void JKRExpHeap::joinTwoBlocks(CMemBlock* block) {
    u32 endAddr = (uintptr_t)(block + 1) + block->size;
    CMemBlock* next = block->mNext;
    u32 nextAddr = (uintptr_t)next - (next->mFlags & 0x7f);
    if (endAddr == nextAddr) {
        block->size = next->size + sizeof(CMemBlock) + (next->mFlags & 0x7f) + block->size;
        CMemBlock* local_30 = next->mNext;
        setFreeBlock(block, block->mPrev, local_30);
    }
}

bool JKRExpHeap::check() {
    lock();
    int totalBytes = 0;
    bool ok = true;
    for (CMemBlock* block = mHeadUsedList; block; block = block->mNext) {
        if (block->mMagic != 'HM') {
            ok = false;
        }

        if (block->mNext) {
            if (block->mNext->mMagic != 'HM') {
                ok = false;
                break;
            }
            if (block->mNext->mPrev != block) {
                ok = false;
            }
        } else {
            if (mTailUsedList != block) {
                ok = false;
            }
        }
        totalBytes += sizeof(CMemBlock) + block->size + block->getAlignment();
    }

    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        totalBytes += block->size + sizeof(CMemBlock);
        if (block->mNext) {
            if (block->mNext->mPrev != block) {
                ok = false;
            }

            if ((uintptr_t)block + block->size + sizeof(CMemBlock) > (uintptr_t)block->mNext) {
                ok = false;
            }
        } else {
            if (mTailFreeList != block) {
                ok = false;
            }
        }
    }

    if (totalBytes != mSize) {
        ok = false;
    }

    unlock();
    return ok;
}

void JKRExpHeap::CMemBlock::initiate(JKRExpHeap::CMemBlock* prev, JKRExpHeap::CMemBlock* next,
                                     u32 size, u8 groupId, u8 alignment) {
    mMagic = 'HM';
    mFlags = alignment;
    mGroupId = groupId;
    this->size = size;
    mPrev = prev;
    mNext = next;
}

JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::allocFore(u32 size1, u8 groupId1, u8 alignment1,
                                                        u8 groupId2, u8 alignment2) {
    CMemBlock* block = NULL;
    mGroupId = groupId1;
    mFlags = alignment1;
    if (size >= size1 + sizeof(CMemBlock)) {
        block = (CMemBlock*)(size1 + (uintptr_t)this);
        block[1].mGroupId = groupId2;
        block[1].mFlags = alignment2;
        block[1].size = size - (size1 + sizeof(CMemBlock));
        size = size1;
        block = block + 1;
    }
    return block;
}

JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::allocBack(u32 size1, u8 groupId1, u8 alignment1,
                                                        u8 groupId2, u8 alignment2) {
    CMemBlock* newblock = NULL;
    if (size >= size1 + sizeof(CMemBlock)) {
        newblock = (CMemBlock*)((uintptr_t)this + size - size1);
        newblock->mGroupId = groupId2;
        newblock->mFlags = alignment2 | 0x80;
        newblock->size = size1;
        mGroupId = groupId1;
        mFlags = alignment1;
        this->size -= size1 + sizeof(CMemBlock);
    } else {
        mGroupId = groupId2;
        mFlags = 0x80;
    }
    return newblock;
}

int JKRExpHeap::CMemBlock::free(JKRExpHeap* heap) {
    heap->removeUsedBlock(this);
    heap->recycleFreeBlock(this);
    return 0;
}

JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::getHeapBlock(void* ptr) {
    if (ptr) {
        CMemBlock* block = (CMemBlock*)ptr - 1;
        if (block->isValid()) {
            return block;
        }
    }
    return NULL;
}

u32 JKRExpHeap::getHeapType() {
    return 'EXPH';
}

u8 JKRExpHeap::do_getCurrentGroupId() {
    return mCurrentGroupId;
}
