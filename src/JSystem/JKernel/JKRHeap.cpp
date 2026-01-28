#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring> // <string>
#include <iostream>
#include <sys/mman.h>

#include "JSystem/JKernel/JKRHeap.h"

bool JKRHeap::sDefaultFillFlag = true;

JKRHeap* JKRHeap::sSystemHeap;

JKRHeap* JKRHeap::sCurrentHeap;

JKRHeap* JKRHeap::sRootHeap;

JKRErrorHandler JKRHeap::mErrorHandler;

static bool data_80451380;

JKRHeap::JKRHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag)
    : JKRDisposer(), mChildTree(this), mDisposerList() {
    mSize = size;
    mStart = (u8*)data;
    mEnd = (u8*)data + size;

    if (parent == NULL) {
        becomeSystemHeap();
        becomeCurrentHeap();
    } else {
        parent->mChildTree.appendChild(&mChildTree);

        if (sSystemHeap == sRootHeap) {
            becomeSystemHeap();
        }

        if (sCurrentHeap == sRootHeap) {
            becomeCurrentHeap();
        }
    }

    mErrorFlag = errorFlag;
    if (mErrorFlag == true && mErrorHandler == NULL) {
        mErrorHandler = JKRDefaultMemoryErrorRoutine;
    }

    mDebugFill = false;  // No debug fill on modern port
    mCheckMemoryFilled = false;
    mInitFlag = false;
}

JKRHeap::~JKRHeap() {
    mChildTree.getParent()->removeChild(&mChildTree);
    JSUTree<JKRHeap>* nextRootHeap = sRootHeap->mChildTree.getFirstChild();

    if (sCurrentHeap == this) {
        sCurrentHeap = !nextRootHeap ? sRootHeap : nextRootHeap->getObject();
    }

    if (sSystemHeap == this) {
        sSystemHeap = !nextRootHeap ? sRootHeap : nextRootHeap->getObject();
    }
}

void* JKRHeap::mCodeStart;

void* JKRHeap::mCodeEnd;

void* JKRHeap::mUserRamStart;

void* JKRHeap::mUserRamEnd;

u32 JKRHeap::mMemorySize;

JKRHeap::JKRAllocCallback JKRHeap::sAllocCallback;

JKRHeap::JKRFreeCallback JKRHeap::sFreeCallback;

bool JKRHeap::initArena(char** memory, u32* size, int maxHeaps) {
    std::cout << "Hello from JKRHeap::initArena() @ JKRHeap.cpp" << std::endl;
    // TODO: Lower this? 64MB is more than the GameCube had
    size_t arenaSize = 64 * 1024 * 1024;
    std::cout << "ALERT: Arena is currently being lazily initialized to 64MB and might require testing if this is okay" << std::endl;

    int flags = MAP_PRIVATE | MAP_ANONYMOUS;

    void* arena = mmap(nullptr, arenaSize, PROT_READ | PROT_WRITE, flags, -1, 0);

    if (arena == MAP_FAILED) {
        return false;
    }

    void* arenaLo = (void*)ALIGN_NEXT((uintptr_t)arena, 0x20);
    void* arenaHi = (void*)ALIGN_PREV((uintptr_t)arena + arenaSize, 0x20);

    mCodeStart = nullptr;
    mCodeEnd = nullptr;
    mUserRamStart = arenaLo;
    mUserRamEnd = arenaHi;
    mMemorySize = (u32)arenaSize;

    *memory = (char*)arenaLo;
    *size = (uintptr_t)arenaHi - (uintptr_t)arenaLo;

    // std::cout << "Arena initialized at " << std::hex << arena << std::dec << " with size " << std::hex << (unsigned)arenaSize << std::dec << std::endl;
    std::cout << std::format("Arena initialized at {} with size {} bytes", static_cast<void*>(arena), static_cast<unsigned>(arenaSize)) << std::endl;
    return true;
}

JKRHeap* JKRHeap::becomeSystemHeap() {
    JKRHeap* prev = sSystemHeap;
    sSystemHeap = this;
    return prev;
}

JKRHeap* JKRHeap::becomeCurrentHeap() {
    JKRHeap* prev = sCurrentHeap;
    sCurrentHeap = this;
    return prev;
}

void JKRHeap::destroy() {
    do_destroy();
}

void* JKRHeap::alloc(u32 size, int alignment, JKRHeap* heap) {
    if (heap != NULL) {
        return heap->alloc(size, alignment);
    }

    if (sCurrentHeap != NULL) {
        return sCurrentHeap->alloc(size, alignment);
    }

    return NULL;
}

void* JKRHeap::alloc(u32 size, int alignment) {
    void* mem = do_alloc(size, alignment);
    return mem;
}

void JKRHeap::free(void* ptr, JKRHeap* heap) {
    if (!heap) {
        heap = findFromRoot(ptr);
        if (!heap)
            return;
    }

    heap->free(ptr);
}

void JKRHeap::free(void* ptr) {
    do_free(ptr);
}

void JKRHeap::callAllDisposer() {
    JSUListIterator<JKRDisposer> iterator;

    while ((iterator = mDisposerList.getFirst()) != mDisposerList.getEnd()) {
        iterator->~JKRDisposer();
    }
}

void JKRHeap::freeAll() {
    do_freeAll();
}

void JKRHeap::freeTail() {
    do_freeTail();
}

s32 JKRHeap::resize(void* ptr, u32 size, JKRHeap* heap) {
    if (!heap) {
        heap = findFromRoot(ptr);
        if (!heap)
            return -1;
    }

    return heap->resize(ptr, size);
}

s32 JKRHeap::resize(void* ptr, u32 size) {
    return do_resize(ptr, size);
}

s32 JKRHeap::getSize(void* ptr, JKRHeap* heap) {
    if (!heap) {
        heap = findFromRoot(ptr);
        if (!heap)
            return -1;
    }

    return heap->getSize(ptr);
}

s32 JKRHeap::getSize(void* ptr) {
    return do_getSize(ptr);
}

s32 JKRHeap::getFreeSize() {
    return do_getFreeSize();
}

void* JKRHeap::getMaxFreeBlock() {
    return do_getMaxFreeBlock();
}

s32 JKRHeap::getTotalFreeSize() {
    return do_getTotalFreeSize();
}

s32 JKRHeap::changeGroupID(u8 groupID) {
    return do_changeGroupID(groupID);
}

u8 JKRHeap::getCurrentGroupId() {
    return do_getCurrentGroupId();
}

u32 JKRHeap::getMaxAllocatableSize(int alignment) {
    u32 maxFreeBlock = (uintptr_t)getMaxFreeBlock();
    u32 ptrOffset = (alignment - 1) & alignment - (maxFreeBlock & 0xf);
    return ~(alignment - 1) & (getFreeSize() - ptrOffset);
}

JKRHeap* JKRHeap::findFromRoot(void* ptr) {
    if (sRootHeap == NULL) {
        return NULL;
    }

    if (sRootHeap->mStart <= ptr && ptr < sRootHeap->mEnd) {
        return sRootHeap->find(ptr);
    }

    return sRootHeap->findAllHeap(ptr);
}

JKRHeap* JKRHeap::find(void* memory) const {
    if (mStart <= memory && memory < mEnd) {
        if (mChildTree.getNumChildren() != 0) {
            for (JSUTreeIterator<JKRHeap> iterator(mChildTree.getFirstChild());
                 iterator != mChildTree.getEndChild(); ++iterator)
            {
                JKRHeap* result = iterator->find(memory);
                if (result) {
                    return result;
                }
            }
        }

        return const_cast<JKRHeap*>(this);
    }

    return NULL;
}

JKRHeap* JKRHeap::findAllHeap(void* ptr) const {
    if (mChildTree.getNumChildren() != 0) {
        for (JSUTreeIterator<JKRHeap> iterator(mChildTree.getFirstChild());
             iterator != mChildTree.getEndChild(); ++iterator)
        {
            JKRHeap* result = iterator->findAllHeap(ptr);

            if (result) {
                return result;
            }
        }
    }

    if (mStart <= ptr && ptr < mEnd) {
        return const_cast<JKRHeap*>(this);
    }

    return NULL;
}

void JKRHeap::dispose_subroutine(u32 begin, u32 end) {
    JSUListIterator<JKRDisposer> next_iterator((JSULink<JKRDisposer>*)NULL);
    JSUListIterator<JKRDisposer> it = mDisposerList.getFirst();
    while (it != mDisposerList.getEnd()) {
        JKRDisposer* disposer = it.getObject();

        if ((void*)begin <= disposer && disposer < (void*)end) {
            it->~JKRDisposer();

            if (next_iterator == JSUListIterator<JKRDisposer>((JSULink<JKRDisposer>*)NULL)) {
                it = mDisposerList.getFirst();
                continue;
            }
            it = next_iterator;
            it++;
            continue;
        }
        next_iterator = it;
        it++;
    }
}

bool JKRHeap::dispose(void* ptr, u32 size) {
    dispose_subroutine((uintptr_t)ptr, (uintptr_t)ptr + size);
    return false;
}

void JKRHeap::dispose(void* begin, void* end) {
    dispose_subroutine((uintptr_t)begin, (uintptr_t)end);
}

void JKRHeap::dispose() {
    JSUListIterator<JKRDisposer> iterator;
    while ((iterator = mDisposerList.getFirst()) != mDisposerList.getEnd()) {
        iterator->~JKRDisposer();
    }
}

void JKRHeap::copyMemory(void* dst, void* src, u32 size) {
    u32 count = (size + 3) / 4;

    u32* dst_32 = (u32*)dst;
    u32* src_32 = (u32*)src;
    while (count-- > 0) {
        *dst_32++ = *src_32++;
    }
}

void JKRDefaultMemoryErrorRoutine(void* heap, u32 size, int alignment) {
    throw std::bad_alloc();
}

bool JKRHeap::setErrorFlag(bool errorFlag) {
    bool prev = mErrorFlag;
    mErrorFlag = errorFlag;
    return prev;
}

JKRErrorHandler JKRHeap::setErrorHandler(JKRErrorHandler errorHandler) {
    JKRErrorHandler prev = mErrorHandler;

    mErrorHandler = !errorHandler ? JKRDefaultMemoryErrorRoutine : errorHandler;

    return prev;
}

void JKRHeap::fillMemory(u8* dst, u32 size, u8 val) {
    memset(dst, val, size);
}

bool JKRHeap::checkMemoryFilled(u8* mem, u32 size, u8 val) {
    void* ptr = mem;
    bool result = true;
    for (int i = 0; i < size; i++) {
        if (val == mem[i]) {
            continue;
        }
        result = false;
        if (fillcheck_dispcount <= 0) {
            continue;
        }
        fillcheck_dispcount--;
        if (data_8074A8D0_debug) {
            break;
        }
    }
    return result;
}

bool JKRHeap::isSubHeap(JKRHeap* heap) const {
    if (!heap)
        return false;

    if (mChildTree.getNumChildren() != 0) {
        for (JSUTreeIterator<JKRHeap> iterator = mChildTree.getFirstChild(); iterator != mChildTree.getEndChild();
             ++iterator)
        {
            if (iterator.getObject() == heap) {
                return true;
            }

            if (iterator.getObject()->isSubHeap(heap)) {
                return true;
            }
        }
    }

    return false;
}

// Heap-specific placement new operators (always available)
void* operator new(size_t size, JKRHeap* heap, int alignment) {
    return JKRHeap::alloc(size, alignment, heap);
}

void* operator new[](size_t size, JKRHeap* heap, int alignment) {
    return JKRHeap::alloc(size, alignment, heap);
}

s32 fillcheck_dispcount = 100;
bool data_8074A8D0_debug = true;

void* ARALT_AramStartAdr = (void*)0x90000000;

void* JKRHeap::getAltAramStartAdr() { return ARALT_AramStartAdr; }

s32 JKRHeap::do_changeGroupID(u8 param_0) {
    return 0;
}

u8 JKRHeap::do_getCurrentGroupId() {
    return 0;
}
