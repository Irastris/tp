#ifndef J2DMATERIAL_H
#define J2DMATERIAL_H

#include "JSystem/J2DGraph/J2DAnimation.h"
#include "JSystem/J2DGraph/J2DMatBlock.h"

class J2DMaterial {
public:
    struct J2DMaterialAnmPointer {
        J2DMaterialAnmPointer();

        J2DAnmColor* mColorAnm;
        J2DAnmTextureSRTKey* mSRTAnm;
        J2DAnmTexPattern* mPatternAnm;
        J2DAnmTevRegKey* mTevAnm;
        u16 mColorIds;
        u16 mSRTIds[8];
        u16 mPatternIds[8];
        u16 mTevCRegIds[4];
        u16 mTevKRegIds[4];
    };

    J2DMaterial();
    void setGX();
    static J2DTevBlock* createTevBlock(int, bool);
    static J2DIndBlock* createIndBlock(int, bool);
    void makeAnmPointer();
    void setAnimation(J2DAnmTextureSRTKey*);
    void setAnimation(J2DAnmTexPattern*);
    void setAnimation(J2DAnmTevRegKey*);
    void setAnimation(J2DAnmColor*);
    void animation();

    virtual ~J2DMaterial();

    u16 getIndex() const { return mIndex; }
    J2DColorBlock* getColorBlock() { return &mColorBlock; }
    J2DTexGenBlock* getTexGenBlock() { return &mTexGenBlock; }
    J2DPEBlock* getPEBlock() { return &mPEBlock; }
    J2DTevBlock* getTevBlock() { return mTevBlock; }
    J2DIndBlock* getIndBlock() { return mIndBlock; }
    bool isVisible() const { return mVisible; }
    int getMaterialAlphaCalc() const { return mMaterialAlphaCalc; }

// private:
    void* field_0x4;
    int field_0x8;
    u16 mIndex;
    bool mVisible;
    u8 mMaterialAlphaCalc;
    J2DColorBlock mColorBlock;
    J2DTexGenBlock mTexGenBlock;
    J2DTevBlock* mTevBlock;
    J2DIndBlock* mIndBlock;
    J2DPEBlock mPEBlock;
    J2DMaterialAnmPointer* mAnmPointer;
};

#endif
