#ifndef M_DO_M_DO_GRAPHIC_H
#define M_DO_M_DO_GRAPHIC_H

#include <iostream>

#include "JSystem/JFramework/JFWDisplay.h"
#include "m_Do/m_Do_mtx.h"
#include "global.h"

#define FB_WIDTH  (608)
#define FB_HEIGHT (448)

int mDoGph_Create();
void mDoGph_drawFilterQuad(s8 param_0, s8 param_1);

struct ResTIMG;
class JKRSolidHeap;

class mDoGph_gInf_c {
public:
    class bloom_c {
    public:
        bloom_c() { m_buffer = NULL; }
        void create();
        void remove();
        void draw();

        u8 getEnable() { return mEnable; }
        void setEnable(u8 i_enable) { mEnable = i_enable; }
        GXColor* getMonoColor() { return &mMonoColor; }
        GXColor* getBlendColor() { return &mBlendColor; }
        void setPoint(u8 i_point) { mPoint = i_point; }
        void setBlureSize(u8 i_size) { mBlureSize = i_size; }
        void setBlureRatio(u8 i_ratio) { mBlureRatio = i_ratio; }
        void setBlendColor(GXColor i_color) { mBlendColor = i_color; }
        void setMonoColor(GXColor i_color) { mMonoColor = i_color; }
        void setMode(u8 i_mode) { mMode = i_mode; }
        void* getBuffer() { return m_buffer; }
        u8 getPoint() { return mPoint; }
        u8 getBlureSize() { return mBlureSize; }
        u8 getBlureRatio() { return mBlureRatio; }

        GXColor mBlendColor;
        GXColor mMonoColor;
        u8 mEnable;
        u8 mMode;
        u8 mPoint;
        u8 mBlureSize;
        u8 mBlureRatio;
        void* m_buffer;
    };

    static void create();
    static void beginRender();
    static void fadeOut(f32);
    static void fadeOut(f32, GXColor&);
    static void fadeIn(f32 fadeSpeed, GXColor& fadeColor) {
        fadeOut(-fadeSpeed, fadeColor);
    }
    static void fadeOut_f(f32, GXColor&);
    static void onBlure(const Mtx);
    static void onBlure();
    static void calcFade();

    static void fadeIn(f32 fadeSpeed) {
        fadeOut(-fadeSpeed);
    }

    static JUTFader* getFader() { return mFader; }
    static void setFader(JUTFader* fader) {
        JFWDisplay::getManager()->setFader(fader);
        mFader = fader;
    }

    static int startFadeOut(int param_0) { return JFWDisplay::getManager()->startFadeOut(param_0); }
    static int startFadeIn(int param_0) { return JFWDisplay::getManager()->startFadeIn(param_0); }
    static void setFadeColor(JUtility::TColor& color) { mFader->setColor(color); }
    static void setClearColor(JUtility::TColor color) { JFWDisplay::getManager()->setClearColor(color); }
    static void setBackColor(GXColor& color) { mBackColor = color; }
    static void endFrame() { JFWDisplay::getManager()->endFrame(); }
    static void offFade() { mFade = 0; }
    static u8 isFade() { return mFade; }
    static void fadeIn_f(f32 i_fadeSpeed, GXColor& i_fadeColor) { fadeOut_f(-i_fadeSpeed, i_fadeColor); }
    static void offBlure() { mBlureFlag = false; }
    static u8 isBlure() { return mBlureFlag; }
    static void setBlureRate(u8 i_rate) { mBlureRate = i_rate; }
    static u8 getBlureRate() { return mBlureRate; }
    static MtxP getBlureMtx() { return mBlureMtx; }
    static void offAutoForcus() { mAutoForcus = 0; }
    static BOOL isAutoForcus() { return mAutoForcus; }
    static void setTickRate(u32 rate) { JFWDisplay::getManager()->setTickRate(rate); }
    static void waitBlanking(int wait) { JFWDisplay::getManager()->waitBlanking(wait); }
    static void setBlureMtx(const Mtx m) { cMtx_copy(m, mBlureMtx); }
    static f32 getWidthF() { return FB_WIDTH; }
    static f32 getHeightF() { return FB_HEIGHT; }
    static f32 getWidth() { return FB_WIDTH; 
    static f32 getHeight() { return FB_HEIGHT; }
    static f32 getMinYF() { return 0.0f; }
    static f32 getMinXF() { return 0.0f; }
    static f32 getMaxYF() { return FB_HEIGHT; }
    static f32 getMaxXF() { return FB_WIDTH; }
    static f32 getAspect() { return 1.3571428f; }
    static int getMinY() { return 0; }
    static int getMinX() { return 0; }
    static int getMaxY() { return FB_HEIGHT; }
    static int getMaxX() { return FB_WIDTH; }
    static ResTIMG* getFrameBufferTimg() { return mFrameBufferTimg; }
    static ResTIMG* getZbufferTimg() { return mZbufferTimg; }
    static void* getFrameBufferTex() { return mFrameBufferTex; }
    static void* getZbufferTex() { return mZbufferTex; }
    static void setFadeRate(f32 rate) { mFadeRate = rate; }
    static f32 getFadeRate() { return mFadeRate; }
    static bloom_c* getBloom() { return &m_bloom; }
    static GXColor& getFadeColor() { return mFadeColor; }
    static GXColor& getBackColor() { return mBackColor; }
    static void endRender() { JFWDisplay::getManager()->endRender(); }
    static GXTexObj* getZbufferTexObj() { return &mZbufferTexObj; }
    static GXTexObj* getFrameBufferTexObj() { return &mFrameBufferTexObj; }
    static void setFrameRate(u16 i_rate) { JFWDisplay::getManager()->setFrameRate(i_rate); }

    static int getFrameBufferSize() {
        #define RoundUp16b(x)   (u16)(((u16)(x) + 16 - 1) & ~(16 - 1))
        return RoundUp16b(JFWDisplay::getManager()->getEfbWidth()) * JFWDisplay::getManager()->getEfbHeight() * 2;
    }

    static void* getFrameBufferMemory() { return JFWDisplay::getManager()->getXfbManager()->getDisplayingXfb(); }
    static f32 getInvScale() { return 1.0f; }
    static f32 getScale() { return 1.0f; }
    static GXTexObj mFrameBufferTexObj;
    static GXTexObj mZbufferTexObj;
    static bloom_c m_bloom;
    static Mtx mBlureMtx;
    static GXColor mBackColor;
    static GXColor mFadeColor;
    static JUTFader* mFader;
    static ResTIMG* mFrameBufferTimg;
    static void* mFrameBufferTex;
    static ResTIMG* mZbufferTimg;
    static void* mZbufferTex;
    static f32 mFadeRate;
    static f32 mFadeSpeed;
    static u8 mBlureFlag;
    static u8 mBlureRate;
    static u8 mFade;
    static bool mAutoForcus;
};

#endif
