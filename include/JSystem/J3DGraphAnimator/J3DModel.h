#ifndef J3DMODEL_H
#define J3DMODEL_H

#include "JSystem/J3DGraphAnimator/J3DSkinDeform.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include <dolphin/types.h>

// TODO: Deduplicate instances of these
typedef f32 Mtx33[3][3];
typedef f32 (*MtxP)[4];

enum J3DMdlFlag {
    J3DMdlFlag_None             = 0x0,
    J3DMdlFlag_Unk1             = 0x1,
    J3DMdlFlag_UseDefaultJ3D    = 0x2,
    J3DMdlFlag_SkinPosCpu       = 0x4,
    J3DMdlFlag_SkinNrmCpu       = 0x8,
    J3DMdlFlag_EnableLOD        = 0x10,
    J3DMdlFlag_UseSharedDL      = 0x20000,
    J3DMdlFlag_UseSingleDL      = 0x40000,
    J3DMdlFlag_DifferedDLBuffer = 0x80000,
};

struct J3DUnkCalc1 {
    virtual void calc(J3DModel* model);
};

struct J3DUnkCalc2 {
    virtual void unk();
    virtual void calc(J3DModelData* mpModelData);
};

typedef void (*J3DCalcCallBack)(J3DModel*, u32 timing);

class J3DModel {
public:
    J3DModel() {
        initialize();
    }

    J3DModel(J3DModelData* pModelData, u32 mdlFlags, u32 mtxBufferFlag) {
        initialize();
        entryModelData(pModelData, mdlFlags, mtxBufferFlag);
    }

    void initialize();
    s32 entryModelData(J3DModelData*, u32, u32);
    s32 createShapePacket(J3DModelData*);
    s32 createMatPacket(J3DModelData*, u32);
    s32 newDifferedDisplayList(u32);
    void lock();
    void unlock();
    void diff();
    s32 setDeformData(J3DDeformData*, u32);
    s32 setSkinDeform(J3DSkinDeform*, u32);
    void calcAnmMtx();
    void calcWeightEnvelopeMtx();
    void calcNrmMtx();
    void calcBumpMtx();
    void calcBBoardMtx();
    void prepareShapePackets();
    void ptrToIndex();
    void makeDL();

    virtual void update();
    virtual void entry();
    virtual void calc();
    virtual void calcMaterial();
    virtual void calcDiffTexMtx();
    virtual void viewCalc();
    virtual ~J3DModel() {}

    J3DModelData* getModelData() { return mModelData; }

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }

    bool isCpuSkinningOn() const { return (mFlags & J3DMdlFlag_SkinPosCpu) && (mFlags & J3DMdlFlag_SkinNrmCpu); }

    Mtx& getBaseTRMtx() { return mBaseTransformMtx; }
    void setBaseTRMtx(Mtx m) { MTXCopy(m, mBaseTransformMtx); }
    u32 getMtxCalcMode() { return mFlags & (J3DMdlFlag_Unk1 | J3DMdlFlag_UseDefaultJ3D); }
    J3DVertexBuffer* getVertexBuffer() { return (J3DVertexBuffer*)&mVertexBuffer; }
    J3DMatPacket* getMatPacket(u16 idx) const { return &mMatPacket[idx]; }
    J3DShapePacket* getShapePacket(u16 idx) const { return &mShapePacket[idx]; }
    J3DMtxBuffer* getMtxBuffer() { return mMtxBuffer; }
    void setScaleFlag(int idx, u8 flag) { mMtxBuffer->setScaleFlag(idx, flag); }
    Mtx33* getBumpMtxPtr(int idx) { return mMtxBuffer->getBumpMtxPtr(idx); }
    Mtx33* getNrmMtxPtr() { return mMtxBuffer->getNrmMtxPtr(); }
    Mtx* getDrawMtxPtr() { return mMtxBuffer->getDrawMtxPtr(); }
    void setBaseScale(const Vec& scale) { mBaseScale = scale; }
    void setUserArea(uintptr_t area) { mUserArea = area; }
    uintptr_t getUserArea() const { return mUserArea; }
    Vec* getBaseScale() { return &mBaseScale; }
    void setAnmMtx(int jointNo, Mtx m) { mMtxBuffer->setAnmMtx(jointNo, m); }
    MtxP getAnmMtx(int jointNo) { return mMtxBuffer->getAnmMtx(jointNo); }
    MtxP getWeightAnmMtx(int i) { return mMtxBuffer->getWeightAnmMtx(i); }
    J3DSkinDeform* getSkinDeform() { return mSkinDeform; }

    J3DModelData* mModelData;
    u32 mFlags;
    u32 mDiffFlag;
    J3DCalcCallBack mCalcCallBack;
    uintptr_t mUserArea;
    Vec mBaseScale;
    Mtx mBaseTransformMtx;
    Mtx mInternalView;
    J3DMtxBuffer* mMtxBuffer;
    J3DVertexBuffer mVertexBuffer;
    J3DMatPacket* mMatPacket;
    J3DShapePacket* mShapePacket;
    J3DDeformData* mDeformData;
    J3DSkinDeform* mSkinDeform;
    J3DVtxColorCalc* mVtxColorCalc;
    J3DUnkCalc1* mUnkCalc1;
    J3DUnkCalc2* mUnkCalc2;
};

#endif
