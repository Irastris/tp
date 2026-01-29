#ifndef DYNAMICLINK_H
#define DYNAMICLINK_H

#include <dolphin/os.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "global.h"

class JKRArchive;
class JKRFileCache;
class mDoDvdThd_callback_c;

struct DynamicModuleControlBase {
    u16 mLinkCount;
    u16 mDoLinkCount;
    DynamicModuleControlBase* mPrev;
    DynamicModuleControlBase* mNext;

    virtual ~DynamicModuleControlBase();
    virtual const char* getModuleName() const { return NULL; };
    virtual int getModuleSize() const { return 0; };
    virtual const char* getModuleTypeString() const {return "Base";};
    static void dump();
    static void dump(char*);

    virtual void dump2() {};
    virtual bool do_load() {return true;};
    virtual BOOL do_load_async() {return true;};
    virtual bool do_unload() {return true;};
    virtual BOOL do_link() {return TRUE;};
    virtual bool do_unlink() {return true; };
    DynamicModuleControlBase();
    BOOL link();
    BOOL unlink();
    BOOL load_async();
    bool force_unlink();
    static JKRHeap* createHeap(u32, JKRHeap*);

    static inline DynamicModuleControlBase* getFirstClass() { return mFirst; }
    inline DynamicModuleControlBase* getNextClass() { return mNext; }
    bool isLinked() const { return mLinkCount != 0; }

    static void resetDoLinkCount() {}
    static void dumpTag() {}

    static DynamicModuleControlBase* mFirst;
    static DynamicModuleControlBase* mLast;

    #if DEBUG
    static u8 verbose;
    #endif

    #if PLATFORM_WII || PLATFORM_SHIELD
    static JKRHeap* getHeap() { return m_heap; }

    static JKRHeap* m_heap;
    #endif
};

struct DynamicModuleControl : DynamicModuleControlBase {
    virtual const char* getModuleName() const { return mName; };
    virtual ~DynamicModuleControl() {}
    virtual int getModuleSize() const;
    virtual const char* getModuleTypeString() const;
    virtual void dump2();
    virtual bool do_load();
    virtual BOOL do_load_async();
    virtual bool do_unload();
    virtual BOOL do_link();
    virtual bool do_unlink();
    DynamicModuleControl(char const*);
    static JKRArchive* mountCallback(void*);
    static bool initialize();
    static bool callback(void*);

    /* OSModuleHeader */ void* mModule;
    void* mBss;
    u32 unk_24;
    const char* mName;
    u8 mResourceType;
    u8 unk_33;
    u16 mChecksum;
    s32 mSize;
    mDoDvdThd_callback_c* mAsyncLoadCallback;

    static u32 sAllocBytes;
    static JKRArchive* sArchive;
    static JKRFileCache* sFileCache;
};

#endif
