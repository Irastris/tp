#ifndef J3DMATERIALFACTORY_H
#define J3DMATERIALFACTORY_H

#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include <dolphin/gx.h>

class J3DMaterial;

struct J3DMaterialInitData {
    u8 mMaterialMode;
    u8 mCullModeIdx;
    u8 mColorChanNumIdx;
    u8 mTexGenNumIdx;
    u8 mTevStageNumIdx;
    u8 mZCompLocIdx;
    u8 mZModeIdx;
    u8 mDitherIdx;
    u16 mMatColorIdx[2];
    u16 mColorChanIdx[4];
    u16 mAmbColorIdx[2];
    u8 field_0x018[0x10];
    u16 mTexCoordIdx[8];
    u8 field_0x038[0x10];
    u16 mTexMtxIdx[8];
    u8 field_0x058[0x2c];
    u16 mTexNoIdx[8];
    u16 mTevKColorIdx[4];
    u8 mTevKColorSel[0x10];
    u8 mTevKAlphaSel[0x10];
    u16 mTevOrderIdx[0x10];
    u16 mTevColorIdx[4];
    u16 mTevStageIdx[0x10];
    u16 mTevSwapModeIdx[0x10];
    u16 mTevSwapModeTableIdx[4];
    u8 field_0x12c[0x18];
    u16 mFogIdx;
    u16 mAlphaCompIdx;
    u16 mBlendIdx;
    u16 mNBTScaleIdx;
};

struct J3DIndInitData {
    bool mEnabled;
    u8 mIndTexStageNum;
    u8 field_0x002[2];
    J3DIndTexOrderInfo mIndTexOrderInfo[3];
    u8 field_0x010[4];
    J3DIndTexMtxInfo mIndTexMtxInfo[3];
    J3DIndTexCoordScaleInfo mIndTexCoordScaleInfo[3];
    u8 field_0x074[4];
    J3DIndTevStageInfo mIndTevStageInfo[0x10];
};

struct J3DPatchingInfo {
    u16 mMatColorOffset;
    u16 mColorChanOffset;
    u16 mTexMtxOffset;
    u16 mTexNoOffset;
    u16 mTevRegOffset;
    u16 mFogOffset;
    u8 field_0xc[4];
};

struct J3DDisplayListInit {
    u32 mOffset;
    u32 field_0x4;
}; // size 8

struct J3DTexCoord2Info;
struct J3DCurrentMtxInfo;

class J3DMaterialFactory {
public:
    enum MaterialType {
        MATERIAL_TYPE_NORMAL = 0,
        MATERIAL_TYPE_LOCKED = 1,
        MATERIAL_TYPE_PATCHED = 2,
    };

    J3DMaterialFactory(J3DMaterialDLBlock const&);
    J3DMaterialFactory(J3DMaterialBlock const&);
    u16 countUniqueMaterials();
    u32 countTexGens(int) const;
    u32 countStages(int) const;
    J3DMaterial* create(J3DMaterial*, MaterialType, int, u32) const;
    J3DMaterial* createNormalMaterial(J3DMaterial*, int, u32) const;
    J3DMaterial* createPatchedMaterial(J3DMaterial*, int, u32) const;
    void modifyPatchedCurrentMtx(J3DMaterial*, int) const;
    J3DMaterial* createLockedMaterial(J3DMaterial*, int, u32) const;
    u32 calcSize(J3DMaterial*, MaterialType, int, u32) const;
    u32 calcSizeNormalMaterial(J3DMaterial*, int, u32) const;
    u32 calcSizePatchedMaterial(J3DMaterial*, int, u32) const;
    u32 calcSizeLockedMaterial(J3DMaterial*, int, u32) const;
    J3DGXColor newMatColor(int, int) const;
    const u8 newColorChanNum(int) const;
    J3DColorChan newColorChan(int, int) const;
    J3DGXColor newAmbColor(int, int) const;
    u32 newTexGenNum(int) const;
    J3DTexCoord newTexCoord(int, int) const;
    J3DTexMtx* newTexMtx(int, int) const;
    u8 newCullMode(int) const;
    u16 newTexNo(int, int) const;
    J3DTevOrder newTevOrder(int, int) const;
    J3DGXColorS10 newTevColor(int, int) const;
    J3DGXColor newTevKColor(int, int) const;
    const u8 newTevStageNum(int) const;
    J3DTevStage newTevStage(int, int) const;
    J3DTevSwapModeTable newTevSwapModeTable(int, int) const;
    u8 newIndTexStageNum(int) const;
    J3DIndTexOrder newIndTexOrder(int, int) const;
    J3DIndTexMtx newIndTexMtx(int, int) const;
    J3DIndTevStage newIndTevStage(int, int) const;
    J3DIndTexCoordScale newIndTexCoordScale(int, int) const;
    J3DFog newFog(int) const;
    J3DAlphaComp newAlphaComp(int) const;
    J3DBlend newBlend(int) const;
    J3DZMode newZMode(int) const;
    const u8 newZCompLoc(int) const;
    const u8 newDither(int) const;
    J3DNBTScale newNBTScale(int) const;

    u16 getMaterialID(int idx) const { return mpMaterialID[idx]; }
    u8 getMaterialMode(int idx) const { return mpMaterialInitData[mpMaterialID[idx]].mMaterialMode; }

    u16 mMaterialNum;
    J3DMaterialInitData* mpMaterialInitData;
    u16* mpMaterialID;
    J3DIndInitData* mpIndInitData;
    GXColor* mpMatColor;
    u8* mpColorChanNum;
    J3DColorChanInfo* mpColorChanInfo;
    GXColor* mpAmbColor;
    J3DLightInfo* mpLightInfo;
    u8* mpTexGenNum;
    J3DTexCoordInfo* mpTexCoordInfo;
    J3DTexCoord2Info* mpTexCoord2Info;
    J3DTexMtxInfo* mpTexMtxInfo;
    J3DTexMtxInfo* field_0x34;
    u16* mpTexNo;
    GXCullMode* mpCullMode;
    J3DTevOrderInfo* mpTevOrderInfo;
    GXColorS10* mpTevColor;
    GXColor* mpTevKColor;
    u8* mpTevStageNum;
    J3DTevStageInfo* mpTevStageInfo;
    J3DTevSwapModeInfo* mpTevSwapModeInfo;
    J3DTevSwapModeTableInfo* mpTevSwapModeTableInfo;
    J3DFogInfo* mpFogInfo;
    J3DAlphaCompInfo* mpAlphaCompInfo;
    J3DBlendInfo* mpBlendInfo;
    J3DZModeInfo* mpZModeInfo;
    u8* mpZCompLoc;
    u8* mpDither;
    J3DNBTScaleInfo* mpNBTScaleInfo;
    J3DDisplayListInit* mpDisplayListInit;
    J3DPatchingInfo* mpPatchingInfo;
    J3DCurrentMtxInfo* mpCurrentMtxInfo;
    u8* mpMaterialMode;
};

#endif
