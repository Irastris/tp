#ifndef J2DMATERIALFACTORY_H
#define J2DMATERIALFACTORY_H

#include "JSystem/J2DGraph/J2DManage.h"
#include "JSystem/J2DGraph/J2DMatBlock.h"

struct J2DMaterialBlock {
    u32 field_0x0;
    u32 field_0x4;
    u16 field_0x8;
    u16 field_0xa;
    u32 field_0xc;
    u32 field_0x10;
    u32 field_0x14;
    u32 field_0x18;
    u32 field_0x1c;
    u32 field_0x20;
    u32 field_0x24;
    u32 field_0x28;
    u32 field_0x2c;
    u32 field_0x30;
    u32 field_0x34;
    u32 field_0x38;
    u32 field_0x3c;
    u32 field_0x40;
    u32 field_0x44;
    u32 field_0x48;
    u32 field_0x4c;
    u32 field_0x50;
    u32 field_0x54;
    u32 field_0x58;
    u32 field_0x5c;
    u32 field_0x60;
    u32 field_0x64;
};

typedef struct _GXColor GXColor;
typedef struct _GXColorS10 GXColorS10;
struct J2DAlphaCompInfo;
struct J2DBlendInfo;
struct J2DColorChanInfo;
class J2DMaterial;

struct J2DIndInitData {
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2[2];
    J2DIndTexOrderInfo field_0x4[4];
    J2DIndTexMtxInfo field_0xc[3];
    J2DIndTexCoordScaleInfo field_0x60[4];
    J2DIndTevStageInfo field_0x68[4];
    u8 field_0xac[0x90];
};

struct J2DMaterialInitData {
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2;
    u8 field_0x3;
    u8 field_0x4;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;
    u16 field_0x8[2];
    u16 field_0xc[4];
    u16 field_0x14[8];
    u16 field_0x24[0xa];
    u16 field_0x38[8];
    u16 field_0x48;
    u16 field_0x4a[4];
    u8 field_0x52[0x10];
    u8 field_0x62[0x10];
    u16 field_0x72[0x10];
    u16 field_0x92[0x4];
    u16 field_0x9a[0x10];
    u16 field_0xba[0x10];
    u16 field_0xda[0x4];
    u16 field_0xe2;
    u16 field_0xe4;
    u16 field_0xe6;
};
struct J2DTevStageInfo;
struct J2DTevSwapModeTableInfo;
struct J2DTevSwapModeInfo;
struct J2DTevOrderInfo;
struct J2DTexCoordInfo;
struct J2DTexMtxInfo;
class JKRArchive;

class J2DMaterialFactory {
public:
    J2DMaterialFactory(J2DMaterialBlock const&);
    u32 countStages(int) const;
    J2DMaterial* create(J2DMaterial*, int, u32, J2DResReference*, J2DResReference*, JKRArchive*) const;
    JUtility::TColor newMatColor(int, int) const;
    u8 newColorChanNum(int) const;
    J2DColorChan newColorChan(int, int) const;
    u32 newTexGenNum(int) const;
    J2DTexCoord newTexCoord(int, int) const;
    J2DTexMtx* newTexMtx(int, int) const;
    u8 newCullMode(int) const;
    u16 newTexNo(int, int) const;
    u16 newFontNo(int) const;
    J2DTevOrder newTevOrder(int, int) const;
    J2DGXColorS10 newTevColor(int, int) const;
    JUtility::TColor newTevKColor(int, int) const;
    u8 newTevStageNum(int) const;
    J2DTevStage newTevStage(int, int) const;
    J2DTevSwapModeTable newTevSwapModeTable(int, int) const;
    u8 newIndTexStageNum(int) const;
    J2DIndTexOrder newIndTexOrder(int, int) const;
    J2DIndTexMtx newIndTexMtx(int, int) const;
    J2DIndTevStage newIndTevStage(int, int) const;
    J2DIndTexCoordScale newIndTexCoordScale(int, int) const;
    J2DAlphaComp newAlphaComp(int) const;
    J2DBlend newBlend(int) const;
    u8 newDither(int) const;

    u8 getMaterialMode(int idx) const { return field_0x4[field_0x8[idx]].field_0x0; }

    u8 getMaterialAlphaCalc(int idx) const { return field_0x4[field_0x8[idx]].field_0x6; }

private:
    u16 field_0x0;
    u16 field_0x2;
    J2DMaterialInitData* field_0x4;
    u16* field_0x8;
    J2DIndInitData* field_0xc;
    GXColor* field_0x10;
    u8* field_0x14;
    J2DColorChanInfo* field_0x18;
    u8* field_0x1c;
    J2DTexCoordInfo* field_0x20;
    J2DTexMtxInfo* field_0x24;
    u16* field_0x28;
    u16* field_0x2c;
    _GXCullMode* field_0x30;
    J2DTevOrderInfo* field_0x34;
    _GXColorS10* field_0x38;
    GXColor* field_0x3c;
    u8* field_0x40;
    J2DTevStageInfo* field_0x44;
    J2DTevSwapModeInfo* field_0x48;
    J2DTevSwapModeTableInfo* field_0x4c;
    J2DAlphaCompInfo* field_0x50;
    J2DBlendInfo* field_0x54;
    u8* field_0x58;
};

#endif
