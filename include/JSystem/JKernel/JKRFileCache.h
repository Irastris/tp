#ifndef JKRFILECACHE_H
#define JKRFILECACHE_H

#include <iostream>

#include "JSystem/JKernel/JKRFileLoader.h"

class JKRHeap;

class JKRFileCache : public JKRFileLoader {
public:
    class CCacheBlock {
    public:
        CCacheBlock(u32, u32, const void*);
        ~CCacheBlock() {}

    public:
        JSULink<CCacheBlock> mCacheBlockLink;
        u32 mReferenceCount;
        u32 mFileId;
        u32 mFileSize;
        void* mMemoryPtr;
    };

protected:
    JKRFileCache(const char*, const char*);
    virtual ~JKRFileCache();

    CCacheBlock* findCacheBlock(const void*) const;
    CCacheBlock* findCacheBlock(u32) const;
    bool findFile(char*, const char*) const;
    char* getDvdPathName(const char*) const;
    void convStrLower(char*) const;

public:
    virtual bool becomeCurrent(const char*);
    virtual void* getResource(const char*);
    virtual void* getResource(u32, const char*);
    virtual u32 readResource(void*, u32, const char*);
    virtual u32 readResource(void*, u32, u32, const char*);
    virtual void removeResourceAll(void);
    virtual bool removeResource(void*);
    virtual bool detachResource(void*);
    virtual u32 getResSize(const void*) const;
    virtual u32 countFile(const char*) const;
    virtual JKRFileFinder* getFirstFile(const char*) const;
    virtual void* getFsResource(const char*);
    virtual void* getNameResource(u32, const char*);
    virtual u32 readFsResource(void*, u32, const char*);
    virtual u32 readNameResource(void*, u32, u32, const char*);

private:
    JKRHeap* mParentHeap;
    JSUList<CCacheBlock> mCacheBlockList;
    char* mRootPath;
    char* mCurrentPath;
    char* mVolumePath;

public:
    static JKRFileCache* mount(const char*, JKRHeap*, const char*);
};

inline JKRFileCache* JKRMountDvdDrive(const char* path, JKRHeap* heap, const char* param_2) {
    return JKRFileCache::mount(path, heap, param_2);
}

inline void JKRUnmountDvdDrive(JKRFileCache* filecache) {
    filecache->unmount();
}

#endif
