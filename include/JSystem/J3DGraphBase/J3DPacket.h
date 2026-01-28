#ifndef J3DPACKET_H
#define J3DPACKET_H

#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphBase/J3DEnum.h"
// #include "dolphin/gd/GDBase.h"
#include <dolphin/mtx.h>
#include <cstdint>

class J3DMatPacket;

class J3DDrawBuffer;
class J3DMaterial;
class J3DMaterialAnm;
class J3DModel;
class J3DMtxBuffer;
class J3DShape;
class J3DTexMtx;
class J3DTexMtxObj;
class J3DTexture;

enum J3DDiffFlag {
    J3DDiffFlag_MatColor         = 0x1,
    J3DDiffFlag_ColorChan        = 0x2,
    J3DDiffFlag_AmbColor         = 0x4,
    J3DDiffFlag_TexGen           = 0x1000,
    J3DDiffFlag_TevReg           = 0x1000000,
    J3DDiffFlag_KonstColor       = 0x2000000,  // is this right?
    J3DDiffFlag_TexCoordScale    = 0x4000000,
    J3DDiffFlag_TevStageIndirect = 0x8000000,
    J3DDiffFlag_Fog              = 0x10000000,
    J3DDiffFlag_Blend            = 0x20000000,
    J3DDiffFlag_Unk40000000      = 0x40000000,
    J3DDiffFlag_Changed          = 0x80000000,
};

#define J3D_DIFF_LIGHTOBJNUM(n) ((n & 0xF) << 4)
#define J3D_DIFF_TEXGENNUM(n)   ((n & 0xF) << 8)
#define J3D_DIFF_TEXNONUM(n)    ((n & 0xF) << 16)
#define J3D_DIFF_TEVSTAGENUM(n) ((n & 0xF) << 20)

#define J3D_DIFF_FLAG(MatColor, ColorChan, AmbColor, LightNum, TexGenNum, TexGen, TexCoordNum, TevStageNum, TevReg, KColor, TexCoordScale, TevStageInd, Fog, Blend) \
    ( \
        (MatColor << 0) | \
        (ColorChan << 1) | \
        (AmbColor << 2) | \
        ((LightNum & 0xF) << 4) | \
        ((TexGenNum & 0xF) << 8) | \
        (TexGen << 12) | \
        ((TexCoordNum & 0xF) << 16) | \
        ((TevStageNum & 0xF) << 20) | \
        (TevReg << 24) | \
        (KColor << 25) | \
        (TexCoordScale << 26) | \
        (TevStageInd << 27) | \
        (Fog << 28) | \
        (Blend << 29) \
    )

inline u32 getDiffFlag_LightObjNum(u32 diffFlags) {
    return (diffFlags & 0xf0) >> 4;
}

inline u32 getDiffFlag_TexGenNum(u32 diffFlags) {
    return (diffFlags & 0xf00) >> 8;
}

inline int calcDifferedBufferSize_TexMtxSize(u32 param_1) {
  return param_1 * 0x35;
}

inline int calcDifferedBufferSize_TexGenSize(u32 param_1) {
    return param_1 * 0x3d + 10;
}

inline u32 getDiffFlag_TexNoNum(u32 diffFlags) {
    return (diffFlags & 0xf0000) >> 0x10;
}

inline int calcDifferedBufferSize_TexNoSize(u32 param_1) {
    return param_1 * 0x37;
}

inline u32 calcDifferedBufferSize_TexNoAndTexCoordScaleSize(u32 param_1) {
    u32 res = param_1 * 0x37;
    res += ((param_1 + 1) >> 1) * 0x37;
    return res;
}

inline u32 getDiffFlag_TevStageNum(u32 diffFlags) {
    return (diffFlags & 0xf00000) >> 0x14;
}

inline int calcDifferedBufferSize_TevStageSize(u32 param_1) {
    return param_1 * 10;
}

inline int calcDifferedBufferSize_TevStageDirectSize(u32 param_1) {
    return param_1 * 5;
}

class J3DDisplayListObj {
public:
    J3DDisplayListObj() {
        mpDisplayList[0] = NULL;
        mpDisplayList[1] = NULL;
        mSize = 0;
        mMaxSize = 0;
    }

    J3DError newDisplayList(u32);
    J3DError newSingleDisplayList(u32);
    int single_To_Double();
    void setSingleDisplayList(void*, u32);
    void swapBuffer();
    void callDL() const;
    void beginDL();
    u32 endDL();
    void beginPatch();
    u32 endPatch();

    u8* getDisplayList(int idx) { return (u8*)mpDisplayList[idx]; }
    u32 getDisplayListSize() { return mSize; }

    static GDLObj sGDLObj;
    static s32 sInterruptFlag;

    void* mpDisplayList[2];
    u32 mSize;
    u32 mMaxSize;
};

class J3DTexMtxObj {
public:
    Mtx& getMtx(u16 idx) {
        return mpTexMtx[idx];
    }

    void setMtx(u16 idx, const Mtx mtx) {
        MTXCopy(mtx, mpTexMtx[idx]);
    }

    Mtx44& getEffectMtx(u16 idx) {
        return mpEffectMtx[idx];
    }

    u16 getNumTexMtx() const { return mTexMtxNum; }

    Mtx* mpTexMtx;
    Mtx44* mpEffectMtx;
    u16 mTexMtxNum;
};

class J3DPacket {
public:
    J3DPacket() {
        mpNextPacket = NULL;
        mpFirstChild = NULL;
        mpUserArea = NULL;
    }

    void addChildPacket(J3DPacket*);

    J3DPacket* getNextPacket() const { return mpNextPacket; }
    void setNextPacket(J3DPacket* i_packet) { mpNextPacket = i_packet; }

    void drawClear() {
        mpNextPacket = NULL;
        mpFirstChild = NULL;
    }

    void* getUserArea() const { return mpUserArea; }
    void setUserArea(uintptr_t area) { mpUserArea = (void*)area; }

    virtual int entry(J3DDrawBuffer*);
    virtual void draw();
    virtual ~J3DPacket() {}

public:
    J3DPacket* mpNextPacket;
    J3DPacket* mpFirstChild;
    void* mpUserArea;
};

class J3DDrawPacket : public J3DPacket {
public:
    J3DDrawPacket();
    ~J3DDrawPacket();
    J3DError newDisplayList(u32);
    J3DError newSingleDisplayList(u32);
    virtual void draw();

    J3DDisplayListObj* getDisplayListObj() { return mpDisplayListObj; }
    void setDisplayListObj(J3DDisplayListObj* pObj) { mpDisplayListObj = pObj; }

    void beginPatch() { mpDisplayListObj->beginPatch(); }
    void endPatch() { mpDisplayListObj->endPatch(); }

    void callDL() const { mpDisplayListObj->callDL(); }
    void beginDL() { mpDisplayListObj->beginDL(); }
    void endDL() { mpDisplayListObj->endDL(); }

    void* getDisplayList(int i) { return mpDisplayListObj->mpDisplayList[i]; }
    u32 getDisplayListSize() const { return mpDisplayListObj->mSize; }

    enum {
        LOCKED = 0x01,
    };

    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }
    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    void lock() { onFlag(LOCKED); }
    void unlock() { offFlag(LOCKED); }
    J3DTexMtxObj* getTexMtxObj() { return mpTexMtxObj; }
    bool isLocked() const { return checkFlag(1); }

public:
    u32 mFlags;
    char unk_0x14[0x20 - 0x14];
    J3DDisplayListObj* mpDisplayListObj;
    J3DTexMtxObj* mpTexMtxObj;
};

class J3DShapePacket : public J3DDrawPacket {
public:
    J3DShapePacket();
    u32 calcDifferedBufferSize(u32);
    int newDifferedDisplayList(u32);
    void prepareDraw() const;
    void drawFast();

    virtual ~J3DShapePacket();
    virtual void draw();

    void setShape(J3DShape* pShape) {
        mpShape = pShape;
    }

    void setModel(J3DModel* pModel) {
        mpModel = pModel;
    }

    void setMtxBuffer(J3DMtxBuffer* pMtxBuffer) { mpMtxBuffer = pMtxBuffer; }
    void setBaseMtxPtr(Mtx* pMtx) { mpBaseMtxPtr = pMtx; }

    J3DShape* getShape() const { return mpShape; }
    J3DModel* getModel() const { return mpModel; }
    Mtx* getBaseMtxPtr() const { return mpBaseMtxPtr; }

public:
    J3DShape* mpShape;
    J3DMtxBuffer* mpMtxBuffer;
    Mtx* mpBaseMtxPtr;
    u32 mDiffFlag;
    J3DModel* mpModel;
};

class J3DMatPacket : public J3DDrawPacket {
public:
    J3DMatPacket();
    void addShapePacket(J3DShapePacket*);
    void beginDiff();
    void endDiff();
    bool isSame(J3DMatPacket*) const;

    J3DMaterial* getMaterial() const { return mpMaterial; }
    J3DShapePacket* getShapePacket() const { return mpShapePacket; }
    void setShapePacket(J3DShapePacket* packet) { mpShapePacket = packet; }

    void setMaterial(J3DMaterial* pMaterial) {
        mpMaterial = pMaterial;
    }

    void setTexture(J3DTexture* pTexture) {
        mpTexture = pTexture;
    }

    void setInitShapePacket(J3DShapePacket* packet) { mpInitShapePacket = packet; }
    void setMaterialID(u32 id) { mDiffFlag = id; }
    void setMaterialAnmID(J3DMaterialAnm* materialAnm) { mpMaterialAnm = materialAnm; }
    BOOL isChanged() { return mDiffFlag & J3DDiffFlag_Changed; }
    bool isEnabled_Diff() { return mpInitShapePacket->getDisplayListObj() != NULL; }

    virtual ~J3DMatPacket();
    virtual int entry(J3DDrawBuffer*);
    virtual void draw();

public:
    J3DShapePacket* mpInitShapePacket;
    J3DShapePacket* mpShapePacket;
    J3DMaterial* mpMaterial;
    u32 mDiffFlag;
    J3DTexture* mpTexture;
    J3DMaterialAnm* mpMaterialAnm;
};

#endif
