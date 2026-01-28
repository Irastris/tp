#ifndef J3DMATERIAL_H
#define J3DMATERIAL_H

#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include <stdint.h>

class J3DJoint;
class J3DMaterialAnm;

class J3DMaterial {
public:
    static J3DColorBlock* createColorBlock(u32);
    static J3DTexGenBlock* createTexGenBlock(u32);
    static J3DTevBlock* createTevBlock(int);
    static J3DIndBlock* createIndBlock(int);
    static J3DPEBlock* createPEBlock(u32, u32);
    static u32 calcSizeColorBlock(u32);
    static u32 calcSizeTexGenBlock(u32);
    static u32 calcSizeTevBlock(int);
    static u32 calcSizeIndBlock(int);
    static u32 calcSizePEBlock(u32, u32);
    void initialize();
    u32 countDLSize();
    void makeDisplayList_private(J3DDisplayListObj*);
    void setCurrentMtx();
    void calcCurrentMtx();
    void copy(J3DMaterial*);
    s32 newSharedDisplayList(u32);
    s32 newSingleSharedDisplayList(u32);

    virtual void calc(f32 const (*)[4]);
    virtual void calcDiffTexMtx(f32 const (*)[4]);
    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void patch();
    virtual void diff(u32);
    virtual void reset();
    virtual void change();

    J3DMaterial() { initialize(); }
    ~J3DMaterial() {}
    J3DMaterial* getNext() { return mNext; }
    J3DShape* getShape() { return mShape; }
    J3DTevBlock* getTevBlock() { return mTevBlock; }
    J3DColorBlock* getColorBlock() { return mColorBlock; }
    J3DTexGenBlock* getTexGenBlock() { return mTexGenBlock; }
    J3DDisplayListObj* getSharedDisplayListObj() { return mSharedDLObj; }
    J3DIndBlock* getIndBlock() { return mIndBlock; }
    J3DJoint* getJoint() { return mJoint; }
    J3DMaterialAnm* getMaterialAnm() {
        return (uintptr_t)mMaterialAnm < 0xC0000000 ? mMaterialAnm : NULL;
    }
    u32 getMaterialMode() { return mMaterialMode; }
    J3DNBTScale* getNBTScale() { return mTexGenBlock->getNBTScale(); }
    u16 getTexNo(u32 idx) { return mTevBlock->getTexNo(idx); }
    J3DGXColor* getTevKColor(u32 param_0) { return mTevBlock->getTevKColor(param_0); }
    J3DGXColorS10* getTevColor(u32 param_0) { return mTevBlock->getTevColor(param_0); }
    J3DFog* getFog() { return mPEBlock->getFog(); }
    J3DTexMtx* getTexMtx(u32 idx) { return mTexGenBlock->getTexMtx(idx); }
    u16 getIndex() { return mIndex; }
    BOOL isDrawModeOpaTexEdge() { return (mMaterialMode & 3) ? 1 : 0; }
    J3DPEBlock* getPEBlock() { return mPEBlock; }
    void onInvalid() { mInvalid = 1; }
    u32 getTexGenNum() const { return mTexGenBlock->getTexGenNum(); }
    u8 getTevStageNum() const { return mTevBlock->getTevStageNum(); }
    J3DTexCoord* getTexCoord(u32 idx) { return mTexGenBlock->getTexCoord(idx); }
    J3DZMode* getZMode() { return mPEBlock->getZMode(); }
    J3DBlend* getBlend() { return mPEBlock->getBlend(); }
    J3DColorChan* getColorChan(u32 idx) { return getColorBlock()->getColorChan(idx); }
    J3DGXColor* getMatColor(u32 i) { return mColorBlock->getMatColor(i); }

    void setTevColor(u32 i, const J3DGXColorS10* i_color) { mTevBlock->setTevColor(i, i_color); }
    void setTevKColor(u32 i, const J3DGXColor* i_color) { mTevBlock->setTevKColor(i, i_color); }
    void setAmbColor(u32 i, const J3DGXColor* i_color) { mColorBlock->setAmbColor(i, i_color); }
    void setLight(u32 i, J3DLightObj* i_lightobj) { mColorBlock->setLight(i, i_lightobj); }
    void setMaterialAnm(J3DMaterialAnm* i_anm) { mMaterialAnm = i_anm; }
    void setCullMode(u8 i_mode) { mColorBlock->setCullMode(i_mode); }
    void setTexMtx(u32 idx, J3DTexMtx* mtx) { mTexGenBlock->setTexMtx(idx, mtx); }
    void setZCompLoc(u8 i_comploc) { mPEBlock->setZCompLoc(i_comploc); }
    void setMaterialMode(u32 i_mode) { mMaterialMode = i_mode; }

    void addShape(J3DShape* pShape) {
        mShape = pShape;
    }

    void setNext(J3DMaterial* pMaterial) {
        mNext = pMaterial;
    }

    void setJoint(J3DJoint* pJoint) {
        mJoint = pJoint;
    }

public:
    J3DMaterial* mNext;
    J3DShape* mShape;
    J3DJoint* mJoint;
    u32 mMaterialMode;
    u16 mIndex;
    u32 mInvalid;
    u32 field_0x1c;
    u32 mDiffFlag;
    J3DColorBlock* mColorBlock;
    J3DTexGenBlock* mTexGenBlock;
    J3DTevBlock* mTevBlock;
    J3DIndBlock* mIndBlock;
    J3DPEBlock* mPEBlock;
    J3DMaterial* mpOrigMaterial;
    J3DMaterialAnm* mMaterialAnm;
    J3DCurrentMtx mCurrentMtx;
    J3DDisplayListObj* mSharedDLObj;
};

class J3DPatchedMaterial : public J3DMaterial {
public:
    J3DPatchedMaterial() { initialize(); }
    void initialize();

    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void reset();
    virtual void change();
};

class J3DLockedMaterial : public J3DMaterial {
public:
    J3DLockedMaterial() { initialize(); }
    void initialize();

    virtual void calc(f32 const (*)[4]);
    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void patch();
    virtual void diff(u32);
    virtual void reset();
    virtual void change();
};

#endif
