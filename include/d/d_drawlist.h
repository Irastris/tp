#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include <iostream>

#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "SSystem/SComponent/c_m3d_g_pla.h"
#include "f_op/f_op_view.h"
#include "m_Do/m_Do_ext.h"
#include "global.h"

class J3DDrawBuffer;
class J3DModel;
class J3DPacket;
class JUTFont;
class dKy_tevstr_c;

class cM_rnd_c {
public:
    cM_rnd_c() { init(100, 100, 100); }

    void init(int, int, int);
    f32 get();
    f32 getF(f32);
    f32 getFX(f32);
    f32 getValue(f32, f32);

    int seed0;
    int seed1;
    int seed2;
};

class dDlst_base_c {
public:
    dDlst_base_c() {}

    virtual void draw() {}
};

class dDlst_blo_c : public dDlst_base_c {
public:
    virtual void draw();
    bool create(JKRArchive* param_1, const char* param_2) {
        return mScreen.setPriority(param_2, 0x20000, param_1) != 0;
    }

    J2DPane* getPane(u64 i_tag) {
        return mScreen.search(i_tag);
    }

    J2DPicture* getPicture(u64 i_tag) {
        J2DPane* pane = getPane(i_tag);
        if (pane->getTypeID() != 0x12) {
            return NULL;
        }
        return (J2DPicture*)pane;
    }

    J2DScreen* getScreen() { return &mScreen; }

    void setPos(u64 param_1, f32 param_2, f32 param_3) {

    }

    class anm_c {
    public:
        inline anm_c() {
            field_0x4 = 0;
            field_0x8 = 1.0f;
        }
        ~anm_c() { remove(); }

        void remove() {
            if (field_0x4 != 0.0f) {

            }

            field_0x4 = 0.0f;
        }

        f32 field_0x4;
        f32 field_0x8;
    };

    int field_0x4;
    J2DScreen mScreen;
    anm_c anm;
};

class dDlst_snapShot_c : public dDlst_base_c {
public:
    virtual void draw();
};

class dDlst_effectLine_c : public dDlst_base_c {
public:
    virtual void draw();
    void update(cXyz&, GXColor&, u16, u16, u16, u16, f32, f32, f32, f32);

    f32 getRndValue(f32 param_0, f32 param_1) { return mRnd.getValue(param_0, param_1); }
    f32 getRndFX(f32 param_0) { return mRnd.getFX(param_0); }

    void initRnd(int r0, int r1, int r2) {
        mRnd.init(r0, r1, r2);
    }

private:
    cM_rnd_c mRnd;
    cXyz field_0x10;
    GXColor mLineColor;
    u16 field_0x20;
    u16 field_0x22;
    u16 field_0x24;
    u16 field_0x26;
    f32 field_0x28;
    f32 field_0x2c;
    f32 field_0x30;
    f32 field_0x34;
};

class dDlst_2D_c : public dDlst_base_c {
public:
    dDlst_2D_c(ResTIMG* image, s16 posX, s16 posY, s16 width, s16 height, u8 alpha);
    virtual void draw();

    void setAlpha(u8 alpha) { mAlpha = alpha; }
    J2DPicture* getPicture() { return &mpPicture; }

private:
    u8 field_0x4;
    J2DPicture mpPicture;
    s16 mPosX;
    s16 mPosY;
    s16 mSizeX;
    s16 mSizeY;
    u8 mAlpha;
};

class dDlst_2DQuad_c : public dDlst_base_c {
public:
    dDlst_2DQuad_c() {}
    virtual void draw();

    void init(s16 posX, s16 posY, s16 width, s16 height, GXColor& color) {
        mPosX = posX;
        mPosY = posY;
        mSizeX = width;
        mSizeY = height;
        mColor = color;
    }

    s16 mPosX;
    s16 mPosY;
    s16 mSizeX;
    s16 mSizeY;
    GXColor mColor;
};

class dDlst_2DT2_c : public dDlst_base_c {
public:
    virtual void draw();
    dDlst_2DT2_c();
    void init(ResTIMG*, f32, f32, f32, f32, u8, u8, u8, f32, f32);

    f32 getScaleX() { return mScaleX; }
    void setScaleX(f32 scale) { mScaleX = scale; }
    void setScaleY(f32 scale) { mScaleY = scale; }

    GXTexObj mTexObj;
    f32 field_0x24;
    f32 field_0x28;
    f32 field_0x2c;
    f32 field_0x30;
    f32 mScaleX;
    f32 mScaleY;
    GXColor field_0x3c;
    GXColor field_0x40;
    u8 field_0x44;
    u8 field_0x45;
    u8 field_0x46;
};

class dDlst_peekZ_c {
public:
    struct dDlst_peekZ_entry {
        s16 x;
        s16 y;
        u32* dst;
    };

    dDlst_peekZ_c() { mCount = 0; }
    int newData(s16, s16, u32*);
    void peekData();

    u8 mCount;
    dDlst_peekZ_entry mEntries[0x40];
};

class dDlst_shadowSimple_c {
public:
    void draw();
    void set(cXyz*, f32, f32, cXyz*, s16, f32, GXTexObj*);
    dDlst_shadowSimple_c();

    u8 mAlpha;
    GXTexObj* mpTexObj;
    Mtx mVolumeMtx;
    Mtx mMtx;
};

struct cBgD_Vtx_t;

class dDlst_shadowTri_c {
public:
    ~dDlst_shadowTri_c() {}
    dDlst_shadowTri_c() {}

    cXyz mPos[3];
};

class dDlst_shadowPoly_c {
public:
    dDlst_shadowPoly_c() {
        reset();
    }

    void reset() { mCount = 0; }

    int set(cBgD_Vtx_t*, u16, u16, u16, cM3dGPla*);
    void draw();

    virtual dDlst_shadowTri_c* getTri() = 0;
    virtual s32 getTriMax() = 0;

    u16 mCount;
    u8 field_0x6[2];
};

class dDlst_shadowRealPoly_c : public dDlst_shadowPoly_c {
public:
    virtual dDlst_shadowTri_c* getTri() { return mShadowTri; }
    virtual s32 getTriMax() { return ARRAY_SIZEU(mShadowTri); }

    dDlst_shadowTri_c mShadowTri[256];
};

class dDlst_shadowReal_c {
public:
    void reset();
    void imageDraw(f32 (*)[4]);
    void draw();
    u8 setShadowRealMtx(cXyz*, cXyz*, f32, f32, f32, dKy_tevstr_c*);
    u32 set(u32, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*, f32, f32);
    bool add(J3DModel*);
    ~dDlst_shadowReal_c() {}
    dDlst_shadowReal_c() { mState = 0; }

    dDlst_shadowReal_c* getZsortNext() { return mZsortNext; }
    dDlst_shadowReal_c* getZsortPre() { return mZsortPre; }
    bool isNoUse() { return mState == 0; }
    bool isUse() { return mState == 1; }
    bool checkKey(u32 i_key) { return mKey == i_key; }
    f32 getCameraZ() { return mCameraZ; }
    void setZsortNext(dDlst_shadowReal_c* next) { mZsortNext = next; }
    void setZsortPre(dDlst_shadowReal_c* pre) { mZsortPre = pre; }

private:
    u8 mState;
    u8 field_0x1;
    u8 mModelNum;
    u8 field_0x3;
    u32 mKey;
    Mtx mViewMtx;
    Mtx44 mRenderProjMtx;
    Mtx mReceiverProjMtx;
    dDlst_shadowRealPoly_c mShadowRealPoly;
    J3DModel* mpModels[38];
    f32 mCameraZ;
    dDlst_shadowReal_c* mZsortPre;
    dDlst_shadowReal_c* mZsortNext;
};

class dDlst_shadowControl_c {
public:
    dDlst_shadowControl_c() { field_0x0 = 0; }
    void init();
    void reset();
    void imageDraw(f32 (*)[4]);
    void draw(f32 (*)[4]);
    int setReal(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    bool addReal(u32, J3DModel*);
    int setSimple(cXyz*, f32, f32, cXyz*, s16, f32, GXTexObj*);
    static void setSimpleTex(ResTIMG const*);

    static GXTexObj* getSimpleTex() { return &mSimpleTexObj; }

    static GXTexObj mSimpleTexObj;

private:
    u8 field_0x0;
    u8 mRealNum;
    u8 mSimpleNum;
    dDlst_shadowReal_c* field_0x4;
    dDlst_shadowReal_c* field_0x8;
    dDlst_shadowSimple_c mSimple[128];
    int mNextID;
    dDlst_shadowReal_c mReal[8];
    GXTexObj field_0x15eb0[2];
    void* field_0x15ef0[2];
};

class dDlst_window_c {
public:
    dDlst_window_c() {}
    ~dDlst_window_c() {}
    void setViewPort(f32, f32, f32, f32, f32, f32);
    void setScissor(f32, f32, f32, f32);

    void setCameraID(int id) { mCameraID = id; }
    int getCameraID() { return mCameraID; }
    void setMode(int mode) { mMode = mode; }
    view_port_class* getViewPort() { return &mViewport; }
    scissor_class* getScissor() { return &mViewport.scissor; }

private:
    view_port_class mViewport;
    s8 mCameraID;
    s8 mMode;
};

struct view_port_class;
struct view_class;

class dDlst_list_c {
public:
    dDlst_list_c();
    void init();
    ~dDlst_list_c();
    void reset();
    void entryZSortXluDrawList(J3DDrawBuffer*, J3DPacket*, cXyz&);
    void drawOpaDrawList(J3DDrawBuffer*);
    void drawXluDrawList(J3DDrawBuffer*);
    void drawOpaListItem3d();
    void drawXluListItem3d();
    int set(dDlst_base_c**&, dDlst_base_c**&, dDlst_base_c*);
    void draw(dDlst_base_c**, dDlst_base_c**);
    static void wipeIn(f32 i_wipeSpeed, GXColor& i_wipeColor);
    static void wipeIn(f32 i_wipeSpeed);
    static void calcWipe();

    enum DrawBuffer {
        DB_OPA_LIST_SKY,
        DB_XLU_LIST_SKY,
        DB_LIST_P0,
        DB_OPA_LIST_BG,
        DB_XLU_LIST_BG,
        DB_OPA_LIST_DARK_BG,
        DB_XLU_LIST_DARK_BG,
        DB_OPA_LIST,
        DB_XLU_LIST,
        DB_OPA_LIST_DARK,
        DB_XLU_LIST_DARK,
        DB_OPA_LIST_PACKET,
        DB_LIST_FILTER,
        DB_OPA_LIST_ITEM3D,
        DB_XLU_LIST_ITEM3D,
        DB_OPA_LIST_INVISIBLE,
        DB_XLU_LIST_INVISIBLE,
        DB_LIST_Z_XLU,
        DB_LIST_2D_SCREEN,
        DB_LIST_MIDDLE,
        DB_LIST_3D_LAST,

        DB_LIST_MAX
    };

    void set2DOpa(dDlst_base_c* dlst) { set(mp2DOpaStart, mp2DOpaEnd, dlst); }
    void set2DOpaTop(dDlst_base_c* dlst) { set(mp2DOpaTopStart, mp2DOpaTopEnd, dlst); }
    void set2DXlu(dDlst_base_c* dlst) { set(mp2DXluStart, mp2DXluEnd, dlst); }
    void setCopy2D(dDlst_base_c* dlst) { set(mpCopy2DStart, mpCopy2DEnd, dlst); }
    view_class* getView() { return mView; }
    void setView(view_class* view) { mView = view; }
    void setWindow(dDlst_window_c* window) { mWindow = window; }
    void setViewport(view_port_class* port) { mViewport = port; }
    J3DDrawBuffer* getOpaList() { return mDrawBuffers[DB_OPA_LIST]; }
    J3DDrawBuffer* getOpaListFilter() { return mDrawBuffers[DB_LIST_FILTER]; }
    J3DDrawBuffer* getOpaListP0() { return mDrawBuffers[DB_LIST_P0]; }
    J3DDrawBuffer* getOpaListPacket() { return mDrawBuffers[DB_OPA_LIST_PACKET]; }
    J3DDrawBuffer* getOpaListBG() { return mDrawBuffers[DB_OPA_LIST_BG]; }
    J3DDrawBuffer* getOpaListDark() { return mDrawBuffers[DB_OPA_LIST_DARK]; }
    J3DDrawBuffer* getXluListBG() { return mDrawBuffers[DB_XLU_LIST_BG]; }
    void setXluDrawList(J3DDrawBuffer* buffer) { j3dSys.setDrawBuffer(buffer, J3DSysDrawBuf_Xlu); }
    void setOpaDrawList(J3DDrawBuffer* buffer) { j3dSys.setDrawBuffer(buffer, J3DSysDrawBuf_Opa); }
    void setXluListSky() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_SKY]); }
    void setOpaListSky() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_SKY]); }
    void setXluListDark() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_DARK]); }
    void setOpaListDark() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_DARK]); }
    void setOpaListInvisible() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_INVISIBLE]); }
    void setXluListInvisible() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_INVISIBLE]); }
    void setXluListDarkBG() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_DARK_BG]); }
    void setOpaListDarkBG() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_DARK_BG]); }
    void setOpaList() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST]); }
    void setXluList() { setXluDrawList(mDrawBuffers[DB_XLU_LIST]); }
    void setOpaListItem3D() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_ITEM3D]); }
    void setXluListItem3D() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_ITEM3D]); }
    void setXluListBG() { setXluDrawList(mDrawBuffers[DB_XLU_LIST_BG]); }
    void setOpaListBG() { setOpaDrawList(mDrawBuffers[DB_OPA_LIST_BG]); }
    void setOpaList3Dlast() { setOpaDrawList(mDrawBuffers[DB_LIST_3D_LAST]); }
    void setXluList3Dlast() { setXluDrawList(mDrawBuffers[DB_LIST_3D_LAST]); }
    void setXluList2DScreen() { setXluDrawList(mDrawBuffers[DB_LIST_2D_SCREEN]); }
    void setXluListP0() { setXluDrawList(mDrawBuffers[DB_LIST_P0]); }
    void setOpaListP0() { setOpaDrawList(mDrawBuffers[DB_LIST_P0]); }
    void setXluListMiddle() { setXluDrawList(mDrawBuffers[DB_LIST_MIDDLE]); }
    void setOpaListMiddle() { setOpaDrawList(mDrawBuffers[DB_LIST_MIDDLE]); }
    void setOpaListZxlu() { setOpaDrawList(mDrawBuffers[DB_LIST_Z_XLU]); }
    void setXluListZxlu() { setXluDrawList(mDrawBuffers[DB_LIST_Z_XLU]); }
    void setOpaListFilter() { setOpaDrawList(mDrawBuffers[DB_LIST_FILTER]); }
    void setXluListFilter() { setXluDrawList(mDrawBuffers[DB_LIST_FILTER]); }
    void set3DlineMat(mDoExt_3DlineMat_c *param_1) {
        m3DLineMatSortPacket[param_1->getMaterialID()].setMat(param_1);
    }

    void set3DlineMatDark(mDoExt_3DlineMat_c *param_1) {
        m3DLineMatSortPacket[param_1->getMaterialID()].setMatDark(param_1);
    }

    void peekZdata() { mPeekZ.peekData(); }
    void entryZSortListZxlu(J3DPacket* i_packet, cXyz& param_1) {
        entryZSortXluDrawList(mDrawBuffers[DB_LIST_Z_XLU], i_packet, param_1);
    }

    void entryZSortXluList(J3DPacket* i_packet, cXyz& param_1) {
        entryZSortXluDrawList(mDrawBuffers[DB_XLU_LIST], i_packet, param_1);
    }

    int setSimpleShadow(cXyz* param_0, f32 param_1, f32 param_2, cXyz* param_3, s16 param_4, f32 param_5, GXTexObj* param_6) {
        return mShadowControl.setSimple(param_0, param_1, param_2, param_3, param_4, param_5, param_6);
    }

    int setRealShadow(u32 param_0, s8 param_1, J3DModel* param_2, cXyz* param_3, f32 param_4,
                      f32 param_5, dKy_tevstr_c* param_6) {
        return mShadowControl.setReal(param_0, param_1, param_2, param_3, param_4, param_5,
                                      param_6);
    }

    bool addRealShadow(u32 key, J3DModel* model) {
        return mShadowControl.addReal(key, model);
    }

    void newPeekZdata(s16 param_0, s16 param_1, u32* param_2) {
        mPeekZ.newData(param_0, param_1, param_2);
    }

    view_port_class* getViewport() { return mViewport; }

    void drawCopy2D() { draw(mpCopy2DDrawLists, mpCopy2DStart); }
    void drawOpaListSky() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_SKY]); }
    void drawXluListSky() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST_SKY]); }
    void drawOpaListBG() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_BG]); }
    void drawOpaListDarkBG() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_DARK_BG]); }
    void drawOpaListMiddle() { drawOpaDrawList(mDrawBuffers[DB_LIST_MIDDLE]); }
    void drawOpaList() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST]); }
    void drawOpaListDark() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_DARK]); }
    void drawOpaListPacket() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_PACKET]); }
    void drawXluListBG() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST_BG]); }
    void drawXluListDarkBG() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST_DARK_BG]); }
    void drawXluList() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST]); }
    void drawXluListDark() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST_DARK]); }
    void drawXluListInvisible() { drawXluDrawList(mDrawBuffers[DB_XLU_LIST_INVISIBLE]); }
    void drawOpaListInvisible() { drawOpaDrawList(mDrawBuffers[DB_OPA_LIST_INVISIBLE]); }
    void drawXluListZxlu() { drawXluDrawList(mDrawBuffers[DB_LIST_Z_XLU]); }
    void drawXluList2DScreen() { drawXluDrawList(mDrawBuffers[DB_LIST_2D_SCREEN]); }
    void drawOpaList3Dlast() { drawOpaDrawList(mDrawBuffers[DB_LIST_3D_LAST]); }
    void drawOpaListFilter() { drawOpaDrawList(mDrawBuffers[DB_LIST_FILTER]); }
    void drawOpaListP0() { drawOpaDrawList(mDrawBuffers[DB_LIST_P0]); }
    void draw2DOpa() { draw(mp2DOpaDrawLists, mp2DOpaStart); }
    void draw2DOpaTop() { draw(mp2DOpaTopDrawLists, mp2DOpaTopStart); }
    void draw2DXlu() { draw(mp2DXluDrawLists, mp2DXluStart); }

    void imageDrawShadow(Mtx param_0) { mShadowControl.imageDraw(param_0); }
    void drawShadow(Mtx param_0) { mShadowControl.draw(param_0); }

    static void wipeOut(f32 i_rate) { wipeIn(-i_rate); }
    static void offWipe() { mWipe = 0; }
    static f32 getWipeRate() { return mWipeRate; }

    static dDlst_2DT2_c mWipeDlst;
    static GXColor mWipeColor;
    static f32 mWipeRate;
    static f32 mWipeSpeed;
    static u8 mWipe;

private:
    J3DDrawBuffer* mDrawBuffers[DB_LIST_MAX];
    dDlst_base_c* mpCopy2DDrawLists[4];
    dDlst_base_c** mpCopy2DStart;
    dDlst_base_c** mpCopy2DEnd;
    dDlst_base_c* mp2DOpaTopDrawLists[16];
    dDlst_base_c** mp2DOpaTopStart;
    dDlst_base_c** mp2DOpaTopEnd;
    dDlst_base_c* mp2DOpaDrawLists[64];
    dDlst_base_c** mp2DOpaStart;
    dDlst_base_c** mp2DOpaEnd;
    dDlst_base_c* mp2DXluDrawLists[32];
    dDlst_base_c** mp2DXluStart;
    dDlst_base_c** mp2DXluEnd;
    dDlst_window_c* mWindow;
    view_port_class* mViewport;
    view_class* mView;
    u8 field_0x250[0xC];
    dDlst_shadowControl_c mShadowControl;
    mDoExt_3DlineMatSortPacket m3DLineMatSortPacket[3];
    dDlst_peekZ_c mPeekZ;
};

#endif
