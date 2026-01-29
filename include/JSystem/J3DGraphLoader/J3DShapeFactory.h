#ifndef J3DSHAPEFACTORY_H
#define J3DSHAPEFACTORY_H

#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include <dolphin/gx.h>

class J3DShape;
class J3DShapeMtx;
class J3DShapeDraw;
struct ResNTAB;

struct J3DShapeInitData {
    u8 mShapeMtxType;
    u16 mMtxGroupNum;
    u16 mVtxDescListIndex;
    u16 mMtxInitDataIndex;
    u16 mDrawInitDataIndex;
    f32 mRadius;
    Vec mMin;
    Vec mMax;
};

struct J3DShapeMtxInitData {
    u16 mUseMtxIndex;
    u16 mUseMtxCount;
    u32 mFirstUseMtxIndex;
};

struct J3DShapeDrawInitData {
    u32 mDisplayListSize;
    u32 mDisplayListIndex;
};

struct J3DShapeFactory {
    J3DShapeFactory(J3DShapeBlock const&);
    J3DShape* create(int, u32, GXVtxDescList*);
    J3DShapeMtx* newShapeMtx(u32, int, int) const;
    J3DShapeDraw* newShapeDraw(int, int) const;
    void allocVcdVatCmdBuffer(u32);
    s32 calcSize(int, u32);
    s32 calcSizeVcdVatCmdBuffer(u32);
    s32 calcSizeShapeMtx(u32, int, int) const;

    J3DShapeInitData* mShapeInitData;
    u16* mIndexTable;
    GXVtxDescList* mVtxDescList;
    u16* mMtxTable;
    u8* mDisplayListData;
    J3DShapeMtxInitData* mMtxInitData;
    J3DShapeDrawInitData* mDrawInitData;
    u8* mVcdVatCmdBuffer;

    u16 getMtxGroupNum(int no) const { return mShapeInitData[mIndexTable[no]].mMtxGroupNum; }
    GXVtxDescList* getVtxDescList(int no) const { return (GXVtxDescList*)((u8*)mVtxDescList + mShapeInitData[mIndexTable[no]].mVtxDescListIndex); }
    f32 getRadius(int no) const { return mShapeInitData[mIndexTable[no]].mRadius; }
    Vec& getMin(int no) const { return mShapeInitData[mIndexTable[no]].mMin; }
    Vec& getMax(int no) const { return mShapeInitData[mIndexTable[no]].mMax; }
};

#endif
