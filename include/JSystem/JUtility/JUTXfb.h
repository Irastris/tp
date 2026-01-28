#ifndef JUTXFB_H
#define JUTXFB_H

#include "JSystem/JUtility/JUTVideo.h"

class JKRHeap;

class JUTXfb {
public:
    enum EXfbNumber {
        UNK_0 = 0,
        UNK_1 = 1,
        UNK_2 = 2,
        UNK_3 = 3,
    };

    void clearIndex();
    void common_init(int);
    JUTXfb(GXRenderModeObj const*, JKRHeap*, JUTXfb::EXfbNumber);
    ~JUTXfb();
    void delXfb(int);
    static JUTXfb* createManager(JKRHeap*, JUTXfb::EXfbNumber);
    static void destroyManager();
    void initiate(u16, u16, JKRHeap*, JUTXfb::EXfbNumber);

    s32 getBufferNum() { return mBufferNum; }
    s16 getDrawnXfbIndex() const { return mDrawnXfbIndex; }
    s16 getDrawingXfbIndex() const { return mDrawingXfbIndex; }
    s16 getDisplayingXfbIndex() const { return mDisplayingXfbIndex; }
    s32 getSDrawingFlag() const { return mSDrawingFlag; }

    void* getDrawnXfb() const {
        void* result;
        if (mDrawnXfbIndex >= 0) {
            result = mBuffer[mDrawnXfbIndex];
        } else {
            result = NULL;
        }
        return result;
    }

    void* getDrawingXfb() const {
        void* result;
        if (mDrawingXfbIndex >= 0) {
            result = mBuffer[mDrawingXfbIndex];
        } else {
            result = NULL;
        }
        return result;
    }

    void* getDisplayingXfb() const {
        void* xfb;
        if (mDisplayingXfbIndex >= 0) {
            xfb = mBuffer[mDisplayingXfbIndex];
        } else {
            xfb = NULL;
        }
        return xfb;
    }

    void setDisplayingXfbIndex(s16 index) { mDisplayingXfbIndex = index; }
    void setSDrawingFlag(s32 flag) { mSDrawingFlag = flag; }
    void setDrawnXfbIndex(s16 index) { mDrawnXfbIndex = index; }
    void setDrawingXfbIndex(s16 index) { mDrawingXfbIndex = index; }

    static JUTXfb* getManager() { return sManager; }

private:
    static JUTXfb* sManager;

private:
    void* mBuffer[3];
    bool mXfbAllocated[3];
    s32 mBufferNum;
    s16 mDrawingXfbIndex;
    s16 mDrawnXfbIndex;
    s16 mDisplayingXfbIndex;
    s32 mSDrawingFlag;
};

#endif
