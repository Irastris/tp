#ifndef JPAEXTEXSHAPE_H
#define JPAEXTEXSHAPE_H

#include "dolphin/types.h"

class JPAEmitterWorkData;

struct JPAExTexShapeData {
    u8 mMagic[4];
    u32 mSize;

    u32 mFlags;
    f32 mIndTexMtx[2][3];
    s8 mExpScale;
    s8 mIndTexIdx;
    s8 mSecTexIdx;
};

class JPAExTexShape {
public:
    JPAExTexShape(u8 const*);

    const f32* getIndTexMtx() const { return &mpData->mIndTexMtx[0][0]; }
    s8 getExpScale() const { return mpData->mExpScale; }
    u8 getIndTexIdx() const { return mpData->mIndTexIdx; }
    u8 getSecTexIdx() const { return mpData->mSecTexIdx; }
    bool isUseIndirect() const { return !!(mpData->mFlags & 0x01); }
    bool isUseSecTex() const { return !!(mpData->mFlags & 0x0100); }

public:
    const JPAExTexShapeData* mpData;
};

void JPALoadExTex(JPAEmitterWorkData*);

#endif
