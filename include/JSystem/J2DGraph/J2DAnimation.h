#ifndef J2DANIMATION_H
#define J2DANIMATION_H

#include "JSystem/JMath/JMath.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

class J2DScreen;
class JUTPalette;
struct ResTIMG;

enum J2DAnmKind {
    KIND_TRANSFORM = 0,
    KIND_COLOR = 1,
    KIND_TEX_PATTERN = 2,
    KIND_TEXTURE_SRT = 4,
    KIND_TEV_REG = 5,
    KIND_VISIBILITY = 6,
    KIND_VTX_COLOR = 7
};

class J2DAnmBase {
public:
    J2DAnmBase() {
        mFrame = 0.0f;
        mFrameMax = 0;
    }
    J2DAnmBase(s16 frameMax) {
        mFrame = 0.0f;
        mFrameMax = frameMax;
    }
    virtual ~J2DAnmBase() {}
    virtual void searchUpdateMaterialID(J2DScreen*) {}

    s16 getFrameMax() const { return mFrameMax; }
    void setFrame(f32 frame) { mFrame = frame; }
    f32 getFrame() const { return mFrame; }
    J2DAnmKind getKind() const { return mKind; }

    u8 field_0x4;
    u8 field_0x5;
    s16 mFrameMax;
    f32 mFrame;
    J2DAnmKind mKind;
};

class J2DAnmVtxColor : public J2DAnmBase {
public:
    J2DAnmVtxColor() {
        mKind = KIND_VTX_COLOR;
        for (int i = 0; i < ARRAY_SIZE(mAnmTableNum); i++) {
            mAnmTableNum[i] = NULL;
        }
        for (int i = 0; i < ARRAY_SIZE(mVtxColorIndexData); i++) {
            mVtxColorIndexData[i] = NULL;
        }
    }
    virtual ~J2DAnmVtxColor() {}
    virtual void getColor(u8, u16, GXColor*) const {}
    u16 getAnmTableNum(u8 param_0) const {
        return mAnmTableNum[param_0];
    }
    J3DAnmVtxColorIndexData* getAnmVtxColorIndexData(u8 param_1, u16 param_2) const {
        return &mVtxColorIndexData[param_1][param_2];
    }
    u16* getVtxColorIndexPointer(u8 param_0) const {
        return mVtxColorIndexPointer[param_0];
    }

    u16 mAnmTableNum[2];
    J3DAnmVtxColorIndexData* mVtxColorIndexData[2];
    u16* mVtxColorIndexPointer[2];
};

struct J3DTransformInfo;
struct J3DTextureSRTInfo;

class J2DAnmVtxColorKey : public J2DAnmVtxColor {
public:
    J2DAnmVtxColorKey() {
        for (int i = 0; i < ARRAY_SIZE(mInfoTable); i++) {
            mInfoTable[i] = NULL;
        }
    }
    virtual ~J2DAnmVtxColorKey() {}
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorKeyTable* mInfoTable[2];
    s16* mRValues;
    s16* mGValues;
    s16* mBValues;
    s16* mAValues;
};

class J2DAnmVtxColorFull : public J2DAnmVtxColor {
public:
    J2DAnmVtxColorFull() {
        for (int i = 0; i < ARRAY_SIZE(mInfoTable); i++) {
            mInfoTable[i] = NULL;
        }
    }
    virtual ~J2DAnmVtxColorFull() {}
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorFullTable* mInfoTable[2];
    u8* mRValues;
    u8* mGValues;
    u8* mBValues;
    u8* mAValues;
};

class J2DAnmVisibilityFull : public J2DAnmBase {
public:
    J2DAnmVisibilityFull() {
        field_0x10 = 0;
        mTable = NULL;
        field_0x12 = 0;
        mValues = NULL;
        mKind = KIND_VISIBILITY;
    }
    virtual ~J2DAnmVisibilityFull() {}
    void getVisibility(u16, u8*) const;

    u16 field_0x10;
    u16 field_0x12;
    J3DAnmVisibilityFullTable* mTable;
    u8* mValues;
};

class J2DAnmTransform : public J2DAnmBase {
public:
    J2DAnmTransform(s16 frameMax, f32* pScaleValues, s16* pRotationValues, f32* pTranslateValues) : J2DAnmBase(frameMax) {
        mScaleValues = pScaleValues;
        mRotationValues = pRotationValues;
        mTranslateValues = pTranslateValues;
        mKind = KIND_TRANSFORM;
    }
    virtual ~J2DAnmTransform() {}
    virtual void getTransform(u16, J3DTransformInfo*) const {}

    f32* mScaleValues;
    s16* mRotationValues;
    f32* mTranslateValues;
};

class J2DAnmTransformKey : public J2DAnmTransform {
public:
    J2DAnmTransformKey() : J2DAnmTransform(0, NULL, NULL, NULL) {
        field_0x24 = 0;
        mInfoTable = NULL;
    }
    virtual ~J2DAnmTransformKey() {}
    virtual void getTransform(u16 p1, J3DTransformInfo* pInfo) const {
        this->calcTransform(mFrame, p1, pInfo);
    }
    virtual void calcTransform(f32, u16, J3DTransformInfo*) const;

    u8 field_0x1c[6];
    u16 field_0x22;
    u32 field_0x24;
    J3DAnmTransformKeyTable* mInfoTable;
};

class J2DAnmTransformFull : public J2DAnmTransform {
public:
    J2DAnmTransformFull() : J2DAnmTransform(0, NULL, NULL, NULL) { mTableInfo = NULL; }
    virtual ~J2DAnmTransformFull() {}
    virtual void getTransform(u16, J3DTransformInfo*) const;

    u8 field_0x1c[6];
    u16 field_0x22;
    J3DAnmTransformFullTable* mTableInfo;
};

class J2DAnmTextureSRTKey : public J2DAnmBase {
public:
    J2DAnmTextureSRTKey() {
        field_0x10 = 0;
        mUpdateMaterialNum = field_0x1a = field_0x1c = field_0x1e = 0;
        mInfoTable = NULL;
        mScaleValues = mTranslationValues = NULL;
        mRotationValues = NULL;
        field_0x4e = field_0x48 = field_0x4a = field_0x4c = 0;
        field_0x5c = NULL;
        field_0x50 = field_0x58 = NULL;
        field_0x54 = NULL;
        field_0x7c = 0;
        mKind = KIND_TEXTURE_SRT;
    }
    void calcTransform(f32, u16, J3DTextureSRTInfo*) const;

    virtual ~J2DAnmTextureSRTKey() {}
    virtual void searchUpdateMaterialID(J2DScreen*);
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum / 3; }
    u16 getUpdateMaterialID(u16 i) const {
        return mUpdateMaterialID[i];
    }
    u8 getUpdateTexMtxID(u16 i) const {
        return mUpdateTexMtxID[i];
    }
    void getTransform(u16 param_1, J3DTextureSRTInfo* param_2) const {
        calcTransform(mFrame, param_1, param_2);
    }

    int field_0x10;
    J3DAnmTransformKeyTable* mInfoTable;
    u16 mUpdateMaterialNum;
    u16 field_0x1a;
    u16 field_0x1c;
    u16 field_0x1e;
    f32* mScaleValues;
    s16* mRotationValues;
    f32* mTranslationValues;
    u8* mUpdateTexMtxID;
    u16* mUpdateMaterialID;
    JUTNameTab field_0x34;
    Vec* field_0x44;
    u16 field_0x48;
    u16 field_0x4a;
    u16 field_0x4c;
    u16 field_0x4e;
    f32* field_0x50;
    s16* field_0x54;
    f32* field_0x58;
    J3DAnmTransformKeyTable* field_0x5c;
    u8* field_0x60;
    u16* field_0x64;
    JUTNameTab field_0x68;
    Vec* field_0x78;
    int field_0x7c;
};

class J2DAnmTexPattern : public J2DAnmBase {
public:
    struct J2DAnmTexPatternTIMGPointer {
        J2DAnmTexPatternTIMGPointer() {
            mRes = NULL;
            mPalette = NULL;
        }
        ~J2DAnmTexPatternTIMGPointer() {
            delete mPalette;
        }

        ResTIMG* mRes;
        JUTPalette* mPalette;
    };

    J2DAnmTexPattern() {
        mValues = NULL;
        mAnmTable = NULL;
        mKind = KIND_TEX_PATTERN;
        mUpdateMaterialNum = 0;
        mUpdateMaterialID = NULL;
        mTIMGPtrArray = NULL;
    }

    void getTexNo(u16, u16*) const;
    ResTIMG* getResTIMG(u16) const;
    JUTPalette* getPalette(u16) const;

    virtual ~J2DAnmTexPattern() { delete[] mTIMGPtrArray; }
    virtual void searchUpdateMaterialID(J2DScreen*);
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    u16 getUpdateMaterialID(u16 i) const {
        return mUpdateMaterialID[i];
    }
    J3DAnmTexPatternFullTable* getAnmTable() const { return mAnmTable; }

    u16* mValues;
    J3DAnmTexPatternFullTable* mAnmTable;
    u16 field_0x18;
    u16 mUpdateMaterialNum;
    u16* mUpdateMaterialID;
    JUTNameTab field_0x20;
    J2DAnmTexPatternTIMGPointer* mTIMGPtrArray;
};

class J2DAnmTevRegKey : public J2DAnmBase {
public:
    J2DAnmTevRegKey() {
        mCRegUpdateMaterialNum = mKRegUpdateMaterialNum = 0;
        field_0x14 = field_0x16 = field_0x18 = field_0x1a = 0;
        field_0x1c = field_0x1e = field_0x20 = field_0x22 = 0;
        mCRegUpdateMaterialID = mKRegUpdateMaterialID = NULL;
        mCRValues = mCGValues = mCBValues = mCAValues = NULL;
        mKRValues = mKGValues = mKBValues = mKAValues = NULL;
        mKind = KIND_TEV_REG;
    }
    void getTevColorReg(u16, GXColorS10*) const;
    void getTevKonstReg(u16, GXColor*) const;

    virtual ~J2DAnmTevRegKey() {}
    virtual void searchUpdateMaterialID(J2DScreen* pScreen);

    u16 getCRegUpdateMaterialNum() const { return mCRegUpdateMaterialNum; }
    u16 getCRegUpdateMaterialID(u16 i) const {
        return mCRegUpdateMaterialID[i];
    }

    u16 getKRegUpdateMaterialNum() const { return mKRegUpdateMaterialNum; }
    u16 getKRegUpdateMaterialID(u16 i) const {
        return mKRegUpdateMaterialID[i];
    }

    J3DAnmCRegKeyTable* getAnmCRegKeyTable() const { return mAnmCRegKeyTable; }
    J3DAnmKRegKeyTable* getAnmKRegKeyTable() const { return mAnmKRegKeyTable; }

    u16 mCRegUpdateMaterialNum;
    u16 mKRegUpdateMaterialNum;
    u16 field_0x14;
    u16 field_0x16;
    u16 field_0x18;
    u16 field_0x1a;
    u16 field_0x1c;
    u16 field_0x1e;
    u16 field_0x20;
    u16 field_0x22;
    u16* mCRegUpdateMaterialID;
    JUTNameTab mCRegNameTab;
    u16* mKRegUpdateMaterialID;
    JUTNameTab mKRegNameTab;
    J3DAnmCRegKeyTable* mAnmCRegKeyTable;
    J3DAnmKRegKeyTable* mAnmKRegKeyTable;
    s16* mCRValues;
    s16* mCGValues;
    s16* mCBValues;
    s16* mCAValues;
    s16* mKRValues;
    s16* mKGValues;
    s16* mKBValues;
    s16* mKAValues;
};

class J2DAnmColor : public J2DAnmBase {
public:
    J2DAnmColor() {
        field_0x10 = field_0x12 = field_0x14 = field_0x16 = 0;
        mUpdateMaterialNum = 0;
        mUpdateMaterialID = NULL;
        mKind = KIND_COLOR;
    }
    virtual ~J2DAnmColor() {}
    virtual void searchUpdateMaterialID(J2DScreen*);
    virtual void getColor(u16, GXColor*) const {}
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    u16 getUpdateMaterialID(u16 i) const {
        return mUpdateMaterialID[i];
    }

    u16 field_0x10;
    u16 field_0x12;
    u16 field_0x14;
    u16 field_0x16;
    u16 mUpdateMaterialNum;
    u16* mUpdateMaterialID;
    JUTNameTab field_0x20;
};

class J2DAnmColorKey : public J2DAnmColor {
public:
    J2DAnmColorKey() {
        mRValues = NULL;
        mGValues = NULL;
        mBValues = NULL;
        mAValues = NULL;
        mInfoTable = NULL;
    }
    virtual ~J2DAnmColorKey() {}
    virtual void getColor(u16, GXColor*) const;

    s16* mRValues;
    s16* mGValues;
    s16* mBValues;
    s16* mAValues;
    J3DAnmColorKeyTable* mInfoTable;
};

struct J2DAnmColorFullInfo {
    u16 mRMaxFrame;
    u16 mROffset;
    u16 mGMaxFrame;
    u16 mGOffset;
    u16 mBMaxFrame;
    u16 mBOffset;
    u16 mAMaxFrame;
    u16 mAOffset;
};

class J2DAnmColorFull : public J2DAnmColor {
public:
    J2DAnmColorFull() {
        mRValues = NULL;
        mGValues = NULL;
        mBValues = NULL;
        mAValues = NULL;
        mInfoTable = NULL;
    }
    virtual ~J2DAnmColorFull() {}
    virtual void getColor(u16, GXColor*) const;

    u8* mRValues;
    u8* mGValues;
    u8* mBValues;
    u8* mAValues;
    J3DAnmColorFullTable* mInfoTable;
};

inline f32 J2DHermiteInterpolation(f32 f1, const f32* f2, const f32* f3, const f32* f4, const f32* f5, const f32* f6, const f32* f7) {
    return JMAHermiteInterpolation(f1, *f2, *f3, *f4, *f5, *f6, *f7);
}

inline f32 J2DHermiteInterpolation(f32 pp1, s16* pp2, s16* pp3, s16* pp4, s16* pp5, s16* pp6, s16* pp7) {
    f32 duration = *pp5 - *pp2;
    f32 t = (pp1 - *pp2) / duration;
    f32 t2 = t * t;
    f32 t3 = t2 * t;

    f32 delta = *pp6 - *pp3;
    f32 m0 = *pp4 * duration;
    f32 m1 = *pp7 * duration;

    return *pp3 + m0 * t + (3.0f * delta - 2.0f * m0 - m1) * t2 + (m0 + m1 - 2.0f * delta) * t3;
}

#endif
