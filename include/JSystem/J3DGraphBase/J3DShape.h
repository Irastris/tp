#ifndef J3DSHAPE_H
#define J3DSHAPE_H

#include "JSystem/J3DGraphBase/J3DShapeDraw.h"
#include "JSystem/J3DGraphBase/J3DFifo.h"
#include <dolphin/mtx.h>

class J3DShapeMtx;

class J3DCurrentMtxInfo {
public:
    u32 mMtxIdxRegA;
    u32 mMtxIdxRegB;
};

class J3DCurrentMtx : public J3DCurrentMtxInfo {
public:
    J3DCurrentMtx() {
        mMtxIdxRegA = 0x3cf3cf00;
        mMtxIdxRegB = 0x00f3cf3c;
    }

    J3DCurrentMtx& operator=(J3DCurrentMtxInfo const& info) {
        mMtxIdxRegA = info.mMtxIdxRegA;
        mMtxIdxRegB = info.mMtxIdxRegB;
        return *this;
    }

    u32 getMtxIdxRegA() const { return mMtxIdxRegA; }
    u32 getMtxIdxRegB() const { return mMtxIdxRegB; }

    void load() const {
        std::cout << "J3DCurrentMtx::load() is stubbed" << std::endl;

        /* J3DFifoLoadCPCmd(CP_REG_MTXIDXA_ID, mMtxIdxRegA);
        J3DFifoLoadCPCmd(CP_REG_MTXIDXB_ID, mMtxIdxRegB);
        J3DFifoLoadXFCmdHdr(GX_XF_REG_MATRIXINDEX0, 2);
        GXCmd1u32(mMtxIdxRegA);
        GXCmd1u32(mMtxIdxRegB); */
    }

    void setCurrentTexMtx(u8 param_1, u8 param_2, u8 param_3, u8 param_4,
                          u8 param_5, u8 param_6, u8 param_7, u8 param_8) {
        mMtxIdxRegA = (param_1 << 6) | (param_2 << 0xc) | (param_3 << 0x12) | (param_4 << 0x18);
        mMtxIdxRegB = (param_5) | param_6 << 6 | param_7 << 0xc | param_8 << 0x12;
    }
};

typedef void (J3DShapeMtx::*J3DShapeMtx_LoadFunc)(int, u16) const;

class J3DShapeMtx {
public:
    J3DShapeMtx(u16 useMtxIndex)
        : mUseMtxIndex(useMtxIndex)
    {}

    void loadMtxIndx_PNGP(int, u16) const;
    void loadMtxIndx_PCPU(int, u16) const;
    void loadMtxIndx_NCPU(int, u16) const;
    void loadMtxIndx_PNCPU(int, u16) const;

    virtual ~J3DShapeMtx() {}
    virtual u32 getType() const { return 'SMTX'; }
    virtual u16 getUseMtxNum() const { return 1; }
    virtual u16 getUseMtxIndex(u16) const { return mUseMtxIndex; }
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, f32 (*)[3][3], f32 (*)[3][3]);

    static J3DShapeMtx_LoadFunc sMtxLoadPipeline[4];
    static u16 sMtxLoadCache[10];
    static u32 sCurrentPipeline;
    static u8* sCurrentScaleFlag;
    static bool sNBTFlag;
    static bool sLODFlag;
    static u32 sTexMtxLoadType;

    static void setCurrentPipeline(u32 pipeline) {
        sCurrentPipeline = pipeline;
    }

    static void setLODFlag(bool flag) { sLODFlag = flag; }
    static u32 getLODFlag() { return sLODFlag; }
    static void resetMtxLoadCache();

protected:
    u16 mUseMtxIndex;
};

class J3DMaterial;
class J3DVertexData;
class J3DDrawMtxData;

enum J3DShpFlag {
    J3DShpFlag_Visible    = 0x0001,
    J3DShpFlag_SkinPosCpu = 0x0004,
    J3DShpFlag_SkinNrmCpu = 0x0008,
    J3DShpFlag_Hidden     = 0x0010,
    J3DShpFlag_EnableLod  = 0x0100,
    J3DShpFlag_NoMtx      = 0x0200,
};

class J3DShape {
public:
    J3DShape() {
        initialize();
    }

    static const int kVcdVatDLSize = 0xC0;

    void initialize();
    void addTexMtxIndexInDL(GXAttr, u32);
    void addTexMtxIndexInVcd(GXAttr);
    void calcNBTScale(Vec const&, f32 (*)[3][3], f32 (*)[3][3]);
    u16 countBumpMtxNum() const;
    void loadVtxArray() const;
    bool isSameVcdVatCmd(J3DShape*);
    void makeVtxArrayCmd();
    void makeVcdVatCmd();
    void loadPreDrawSetting() const;
    void setArrayAndBindPipeline() const;

    virtual void draw() const;
    virtual void drawFast() const;
    virtual void simpleDraw() const;
    virtual void simpleDrawCache() const;

    void loadCurrentMtx() const;

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }

    void setMaterial(J3DMaterial* pMaterial) {
        mMaterial = pMaterial;
    }

    void setDrawMtxDataPointer(J3DDrawMtxData* pMtxData) {
        mDrawMtxData = pMtxData;
    }

    void setVertexDataPointer(J3DVertexData* pVtxData) {
        mVertexData = pVtxData;
    }

    void* getVcdVatCmd() { return mVcdVatCmd; }
    void setVcdVatCmd(void* pVatCmd) { mVcdVatCmd = (u8*)pVatCmd; }
    void show() { offFlag(J3DShpFlag_Visible); }
    void hide() { onFlag(J3DShpFlag_Visible); }

    void setCurrentViewNoPtr(u32* pViewNoPtr) {
        mCurrentViewNo = pViewNoPtr;
    }

    void setCurrentMtx(J3DCurrentMtx& mtx) { mCurrentMtx = mtx; }

    void setScaleFlagArray(u8* pScaleFlagArray) {
        mScaleFlagArray = pScaleFlagArray;
    }

    void setDrawMtx(Mtx** pDrawMtx) { mDrawMtx = pDrawMtx; }
    void setNrmMtx(Mtx33** pNrmMtx) { mNrmMtx = pNrmMtx; }
    void setTexMtxLoadType(u32 type) { mFlags = (mFlags & 0xFFFF0FFF) | type; }
    bool getNBTFlag() const { return mHasNBT; }
    u32 getBumpMtxOffset() const { return mBumpMtxOffset; }
    void setBumpMtxOffset(u32 offset) { mBumpMtxOffset = offset; }
    GXVtxDescList* getVtxDesc() { return mVtxDesc; }

    J3DMaterial* getMaterial() const { return mMaterial; }
    u16 getIndex() const { return mIndex; }
    u32 getTexMtxLoadType() const { return mFlags & 0xF000; }
    u32 getMtxGroupNum() const { return mMtxGroupNum; }
    J3DShapeDraw* getShapeDraw(u16 idx) { return mShapeDraw[idx]; }
    J3DShapeMtx* getShapeMtx(u16 idx) { return mShapeMtx[idx]; }
    Vec* getMin() { return &mMin; }
    Vec* getMax() { return &mMax; }

    static void resetVcdVatCache() { sOldVcdVatCmd = NULL; }

    static void* sOldVcdVatCmd;
    static bool sEnvelopeFlag;

private:
    friend struct J3DShapeFactory;
    friend class J3DJointTree;

    J3DMaterial* mMaterial;
    u16 mIndex;
    u16 mMtxGroupNum;
    u32 mFlags;
    f32 mRadius;
    Vec mMin;
    Vec mMax;
    u8* mVcdVatCmd;
    GXVtxDescList* mVtxDesc;
    bool mHasNBT;
    J3DShapeMtx** mShapeMtx;
    J3DShapeDraw** mShapeDraw;
    J3DCurrentMtx mCurrentMtx;
    bool mHasPNMTXIdx;
    J3DVertexData* mVertexData;
    J3DDrawMtxData* mDrawMtxData;
    u8* mScaleFlagArray;
    Mtx** mDrawMtx;
    Mtx33** mNrmMtx;
    u32* mCurrentViewNo;
    u32 mBumpMtxOffset;
};

#endif
