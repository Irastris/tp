#include "DynamicLink.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRFileCache.h"
#include <cstdio>
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_ext.h"

DynamicModuleControlBase* DynamicModuleControlBase::mFirst;

DynamicModuleControlBase* DynamicModuleControlBase::mLast;

DynamicModuleControlBase::~DynamicModuleControlBase() {
    force_unlink();
    if (mPrev != NULL) {
        mPrev->mNext = mNext;
    }
    if (mNext != NULL) {
        mNext->mPrev = mPrev;
    }
    if (mFirst == this) {
        mFirst = mNext;
    }
    if (mLast == this) {
        mLast = mPrev;
    }
    mNext = NULL;
    mPrev = NULL;
}

DynamicModuleControlBase::DynamicModuleControlBase() {
    mLinkCount = 0;
    mDoLinkCount = 0;
    mNext = NULL;
    if (mFirst == NULL) {
        mFirst = this;
    }
    mPrev = mLast;
    if (mPrev != NULL) {
        mPrev->mNext = this;
    }
    mLast = this;
}

BOOL DynamicModuleControlBase::link() {
    if (mLinkCount == 0) {
        do_load();
        if (do_link() == false) {
            return false;
        }
        if (mDoLinkCount < 0xFFFF) {
            mDoLinkCount++;
        }
    }
    if (mLinkCount < 0xFFFF) {
        mLinkCount++;
    }
    return true;
}

BOOL DynamicModuleControlBase::unlink() {
    if (mLinkCount != 0) {
        mLinkCount--;
        if (mLinkCount == 0) {
            do_unlink();
            do_unload();
        }
    }
    return true;
}

BOOL DynamicModuleControlBase::load_async() {
    if (mLinkCount == 0) {
        return do_load_async();
    }
    return true;
}

bool DynamicModuleControlBase::force_unlink() {
    if (mLinkCount != 0) {
        mLinkCount = 0;
        do_unlink();
    }
    return true;
}

void DynamicModuleControlBase::dump() {
    u16 doLinkCount;
    u16 linkCount;
    DynamicModuleControlBase* current = getFirstClass();
    size_t totalSize = 0;
    JUTReportConsole_f("\nDynamicModuleControlBase::dump()\n");
    JUTReportConsole_f("Do  Lnk Size      Name\n");
    while (current != NULL) {
        doLinkCount = current->mDoLinkCount;
        linkCount = current->mLinkCount;
        if (doLinkCount != 0 || linkCount != 0) {
            u32 size = current->getModuleSize();
            const char* name = current->getModuleName();
            if (size < 0xFFFFFFFF) {
                name = (name != NULL) ? name : "(Null)";
                const char* type = current->getModuleTypeString();
                JUTReportConsole_f("%3d%3d%5.1f %05x %-4s %-24s ", doLinkCount, linkCount,
                                   size / 1024.0f, size, type, name);
                totalSize = totalSize + size;
            } else {
                name = (name != NULL) ? name : "(Null)";
                const char* type = current->getModuleTypeString();
                JUTReportConsole_f("%3d%3d ???? ????? %-4s %-24s ", doLinkCount, linkCount, type,
                                   name);
            }
            current->dump2();
            JUTReportConsole_f("\n");
        }
        current = current->getNextClass();
    }
    JUTReportConsole_f("TotalSize %6.2f %06x\n\n", totalSize / 1024.0f, totalSize);
}

DynamicModuleControl::DynamicModuleControl(char const* name) {
    mModule = NULL;
    mBss = NULL;
    unk_24 = 0;
    mName = name;
    mResourceType = 0;
    unk_33 = 0;
    mChecksum = 0;
    mSize = 0;
    mAsyncLoadCallback = NULL;
}

u32 DynamicModuleControl::sAllocBytes;

JKRArchive* DynamicModuleControl::sArchive;

JKRFileCache* DynamicModuleControl::sFileCache;

static const char* baseString = "Base";

JKRArchive* DynamicModuleControl::mountCallback(void* param_0) {
    JKRExpHeap* heap = mDoExt_getArchiveHeap();
    sFileCache = JKRFileCache::mount("/rel/Final/Release", heap, NULL);
    sArchive = JKRArchive::mount("RELS.arc", JKRArchive::MOUNT_COMP, heap, JKRArchive::MOUNT_DIRECTION_HEAD);
    return sArchive;
}

bool DynamicModuleControl::initialize() {
    sFileCache = NULL;
    sAllocBytes = 0;
    sArchive = NULL;
    mountCallback(NULL);
    return true;
}

bool DynamicModuleControl::callback(void* moduleControlPtr) {
    DynamicModuleControl* moduleControl = (DynamicModuleControl*)moduleControlPtr;
    return moduleControl->do_load();
}

static u32 calcSum2(u16 const* data, u32 size) {
    u32 sum = 0;
    while (size > 0) {
        sum = sum + *data;
        size = size - 2;
        data++;
    }
    return sum;
}

bool DynamicModuleControl::do_load() {
    if (mModule != NULL) {
        return true;
    }
    JKRExpHeap* heap = mDoExt_getArchiveHeap();
    s32 i = 0;
    while (true) {
        if (mModule != NULL) {
            JKRFree(mModule);
            mModule = NULL;
        }
        char buffer[64];
        snprintf(buffer, 64, "%s.rel", mName);
        if (mModule == NULL && sArchive != NULL) {
            if (mModule == NULL) {
                mModule = NULL; // (OSModuleHeader*)JKRGetResource('MMEM', buffer, sArchive);
                if (mModule != NULL) {
                    mResourceType = 1;
                }
            }
            if (mModule == NULL) {
                mModule = NULL; // (OSModuleHeader*)JKRGetResource('AMEM', buffer, sArchive);
                if (mModule != NULL) {
                    mResourceType = 2;
                }
            }
            if (mModule == NULL) {
                mModule = NULL; // (OSModuleHeader*)JKRGetResource('DMEM', buffer, sArchive);
                if (mModule != NULL) {
                    mResourceType = 3;
                }
            }
        }
        if (mModule != NULL) {
            mSize = sArchive->getExpandedResSize(mModule);
            JKRDetachResource(mModule, NULL);
        } else {
            if (mModule == NULL) {
                snprintf(buffer, 64, "/rel/Final/Release/%s.rel", mName);
                mModule = NULL; // (OSModuleHeader*)JKRDvdToMainRam(buffer, NULL, EXPAND_SWITCH_UNKNOWN1, NULL, heap, JKRDvdRipper::ALLOC_DIRECTION_FORWARD, 0, NULL, NULL);
                if (mModule != NULL) {
                    mSize = 0;
                    mResourceType = 7;
                }
            }
            if (mModule == NULL && sFileCache != NULL) {
                mModule = NULL; // (OSModuleHeader*)sFileCache->getResource('rels', buffer);
                if (mModule != NULL) {
                    mSize = 0;
                    mResourceType = 11;
                    JKRDetachResource(mModule, NULL);
                }
            }
        }
        if (mModule == NULL) {
            return false;
        }
        if (mSize > 0) {
            u32 sum = calcSum2((u16*)mModule, mSize);
            if (unk_33 == 0) {
                mChecksum = sum;
                unk_33++;
            } else {
                u32 newsum = sum & 0xFFFF;
                if (newsum != mChecksum) {
                    unk_33 = 0;
                    i++;
                    if (i >= 3) {
                        return false;
                    }
                } else {
                    if (unk_33 < 0xFF) {
                        unk_33++;
                    }
                    break;
                }
            }
        } else {
            if (unk_33 < 0xFF) {
                unk_33++;
            }
            break;
        }
    }
    return true;
}

BOOL DynamicModuleControl::do_load_async() {
    if (mAsyncLoadCallback == NULL) {
        if (mModule != NULL) {
            return true;
        }
        mAsyncLoadCallback = mDoDvdThd_callback_c::create((mDoDvdThd_callback_func)DynamicModuleControl::callback, this);
    }
    if (mAsyncLoadCallback != NULL && mAsyncLoadCallback->sync()) {
        mAsyncLoadCallback->destroy();
        mAsyncLoadCallback = NULL;
        return true;
    } else {
        return false;
    }
}

bool DynamicModuleControl::do_unload() {
    if (mModule != NULL) {
        JKRFree(mModule);
        mModule = NULL;
    }
    return true;
}

void DynamicModuleControl::dump2() {
    if (mModule != NULL) {
        OSSectionInfo* section = (OSSectionInfo*)mModule->info.sectionInfoOffset;
        OSSectionInfo* section2 = section + 1;
        u32 offset = section2->offset & ~(1);
    }
}

BOOL DynamicModuleControl::do_link() {
    if (mModule == NULL) {
        do_load();
    }
    if (mModule != NULL) {
        if (mModule->info.version >= 3) {
            u32 fixSizePtr;
            u32 fixSize = mModule->fixSize;
            u32 fixSize2 = (fixSize + 0x1f) & ~0x1f;
            fixSizePtr = (u32)mModule + fixSize2;
            s32 size = JKRGetMemBlockSize(NULL, mModule);
            if (size < 0) {
                void* bss = JKRAlloc(mModule->bssSize, 0x20);
                if (bss == NULL) {
                    goto error;
                }
                mBss = bss;
                BOOL linkResult = OSLink(&mModule->info, bss);
                if (linkResult == FALSE) {
                    goto error;
                }
            } else {
                if (fixSize2 + mModule->bssSize < size) {
                    BOOL linkResult = OSLinkFixed(&mModule->info, (void*)fixSizePtr);
                    if (linkResult == FALSE) {
                        goto error;
                    }
                    s32 result = JKRResizeMemBlock(NULL, mModule, fixSize2 + mModule->bssSize);
                    if (result < 0) {
                    }
                } else {
                    s32 result = JKRResizeMemBlock(NULL, mModule, fixSize2 + mModule->bssSize);
                    if (result > 0) {
                        BOOL linkResult = OSLinkFixed(&mModule->info, (void*)fixSizePtr);
                        if (linkResult == FALSE) {
                            goto error;
                        }
                    } else {
                        void* bss = JKRAlloc(mModule->bssSize, 0x20);
                        if (bss == NULL) {
                            goto error;
                        }
                        mBss = bss;
                        BOOL linkResult = OSLinkFixed(&mModule->info, bss);
                        if (linkResult == FALSE) {
                            goto error;
                        }
                        s32 result = JKRResizeMemBlock(NULL, mModule, fixSize);
                        if (result < 0) {
                        }
                    }
                }
            }
        }
        sAllocBytes = sAllocBytes + getModuleSize();
        unk_24 = ((u32(*)())mModule->prolog)();
        return TRUE;
    }

error:
    unk_33 = 0;
    if (mBss != NULL) {
        JKRHeap::free(mBss, NULL);
        mBss = NULL;
    }
    if (mModule != NULL) {
        JKRHeap::free(mModule, NULL);
        mModule = NULL;
    }
    return FALSE;
}

bool DynamicModuleControl::do_unlink() {
    // ((void (*)())mModule->epilog)();
    BOOL unklink = OSUnlink(&mModule->info);
    if (unklink == FALSE) {
        return false;
    }
    sAllocBytes = sAllocBytes - getModuleSize();
    if (mBss != NULL) {
        JKRFree(mBss);
        mBss = NULL;
    }
    do_unload();
    return true;
}

int DynamicModuleControl::getModuleSize() const {
    if (mModule != NULL) {
        u32 size = JKRGetMemBlockSize(NULL, mModule);
        if (mBss != NULL) {
            JKRGetMemBlockSize(NULL, mBss);
        }
        return size + mModule->bssSize;
    } else {
        return 0;
    }
}

const char* DynamicModuleControl::getModuleTypeString() const {
    static const char* strings[4] = {"????", "MEM", "ARAM", "DVD"};
    return strings[mResourceType & 3];
}

extern "C" void ModuleConstructorsX(void (*const *ctors)()) {
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
}

extern "C" void ModuleDestructorsX(void (*const *dtors)()) {
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
