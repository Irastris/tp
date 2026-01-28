#ifndef JUTVIDEO_H
#define JUTVIDEO_H

#include <dolphin/gx.h>
// #include <dolphin/os.h>

typedef u8 (*Pattern)[2];

class JUTVideo {
public:
    typedef void (*Callback)(u32);

    JUTVideo(GXRenderModeObj const*);
    virtual ~JUTVideo();

    static JUTVideo* createManager(GXRenderModeObj const*);
    static void destroyManager();
    static void drawDoneStart();
    static void dummyNoDrawWait();
    void setRenderMode(GXRenderModeObj const*);
    void waitRetraceIfNeed();

    static void preRetraceProc(u32);
    static void postRetraceProc(u32);
    static void drawDoneCallback();

    u16 getFbWidth() const { return mRenderObj->fbWidth; }
    u16 getEfbHeight() const { return mRenderObj->efbHeight; }
    void getBounds(u16& width, u16& height) const {
        width = (u16)getFbWidth();
        height = (u16)getEfbHeight();
    }
    u16 getXfbHeight() const { return u16(mRenderObj->xfbHeight); }
    u8 isAntiAliasing() const { return u8(mRenderObj->aa); }
    Pattern getSamplePattern() const { return mRenderObj->sample_pattern; }
    u8* getVFilter() const { return mRenderObj->vfilter; }
    OSMessageQueue* getMessageQueue() { return &mMessageQueue; }

    static JUTVideo* getManager() { return sManager; }
    static OSTick getVideoInterval() { return sVideoInterval; }
    static OSTick getVideoLastTick() { return sVideoLastTick; }

    GXRenderModeObj* getRenderMode() const { return mRenderObj; }

private:
    static JUTVideo* sManager;
    static OSTick sVideoLastTick;
    static OSTick sVideoInterval;

private:
    _GXRenderModeObj* mRenderObj;
    u32 field_0x8;
    u32 mRetraceCount;
    u32 field_0x10;
    u32 field_0x14;
    u32 field_0x18;
    VIRetraceCallback mPreRetraceCallback;
    VIRetraceCallback mPostRetraceCallback;
    Callback mPreCallback;
    Callback mPostCallback;
    bool mSetBlack;
    s32 mSetBlackFrameCount;
    OSMessage mMessage;
    OSMessageQueue mMessageQueue;
};

inline JUTVideo* JUTGetVideoManager() {
    return JUTVideo::getManager();
}

inline void JUTDestroyVideoManager() {
    JUTVideo::destroyManager();
}

#endif
