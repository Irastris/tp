#ifndef J3DMATERIALFACTORY_V21_H
#define J3DMATERIALFACTORY_V21_H

#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include <dolphin/gx.h>

class J3DMaterial;
struct J3DTexCoord2Info;
struct J3DCurrentMtxInfo;

struct J3DMaterialInitData_v21 {
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

class J3DMaterialFactory_v21 {
public:
    J3DMaterialFactory_v21(J3DMaterialBlock_v21 const&);
    u16 countUniqueMaterials();
    u32 countTexGens(int) const;
    u32 countStages(int) const;
    J3DMaterial* create(J3DMaterial*, int, u32) const;
    J3DGXColor newMatColor(int, int) const;
    const u8 newColorChanNum(int) const;
    J3DColorChan newColorChan(int, int) const;
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
    J3DFog newFog(int) const;
    J3DAlphaComp newAlphaComp(int) const;
    J3DBlend newBlend(int) const;
    const J3DZMode newZMode(int) const;
    const u8 newZCompLoc(int) const;
    const u8 newDither(int) const;
    J3DNBTScale newNBTScale(int) const;

    u16 getMaterialID(int idx) const { return mpMaterialID[idx]; }
    u8 getMaterialMode(int idx) const { return mpMaterialInitData[mpMaterialID[idx]].mMaterialMode; }

    u16 mMaterialNum;
    J3DMaterialInitData_v21* mpMaterialInitData;
    u16* mpMaterialID;
    GXColor* mpMatColor;
    u8* mpColorChanNum;
    J3DColorChanInfo* mpColorChanInfo;
    u8* mpTexGenNum;
    J3DTexCoordInfo* mpTexCoordInfo;
    J3DTexCoord2Info* mpTexCoord2Info;
    J3DTexMtxInfo* mpTexMtxInfo;
    J3DTexMtxInfo* field_0x28;
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
    u16 field_0x6c;
    u8 field_0x6e;
    u8 field_0x6f;
};

#endif
