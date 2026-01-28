#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "global.h"
#include <cstring>

struct J3DLightInfo {
    bool operator==(J3DLightInfo& other) const;
    J3DLightInfo& operator=(J3DLightInfo const&);

    Vec mLightPosition;
    Vec mLightDirection;
    GXColor mColor;
    Vec mCosAtten;
    Vec mDistAtten;
};

struct J3DTextureSRTInfo {
    f32 mScaleX;
    f32 mScaleY;
    s16 mRotation;
    f32 mTranslationX;
    f32 mTranslationY;

    bool operator==(J3DTextureSRTInfo&) const;
    inline void operator=(J3DTextureSRTInfo const& other) {
        mScaleX = other.mScaleX;
        mScaleY = other.mScaleY;
        mRotation = other.mRotation;
        mTranslationX = other.mTranslationX;
        mTranslationY = other.mTranslationY;
    }
};

enum J3DTexMtxMode {
    J3DTexMtxMode_None,
    J3DTexMtxMode_EnvmapBasic,
    J3DTexMtxMode_ProjmapBasic,
    J3DTexMtxMode_ViewProjmapBasic,
    J3DTexMtxMode_Unknown4,
    J3DTexMtxMode_Unknown5,
    J3DTexMtxMode_EnvmapOld,
    J3DTexMtxMode_Envmap,
    J3DTexMtxMode_Projmap,
    J3DTexMtxMode_ViewProjmap,
    J3DTexMtxMode_EnvmapOldEffectMtx,
    J3DTexMtxMode_EnvmapEffectMtx,
};

struct J3DTexMtxInfo {
    bool operator==(J3DTexMtxInfo& other) const;
    J3DTexMtxInfo& operator=(J3DTexMtxInfo const&);
    void setEffectMtx(Mtx);

    u8 mProjection;
    u8 mInfo;
    u8 field_0x2;
    u8 field_0x3;
    Vec mCenter;
    J3DTextureSRTInfo mSRT;
    Mtx44 mEffectMtx;
};

struct J3DIndTexMtxInfo {
    J3DIndTexMtxInfo& operator=(J3DIndTexMtxInfo const&);
    Mtx23 field_0x0;
    s8 field_0x18;
};

struct J3DFogInfo {
    bool operator==(J3DFogInfo&) const;
    J3DFogInfo& operator=(const J3DFogInfo&);

    u8 mType;
    u8 mAdjEnable;
    u16 mCenter;
    f32 mStartZ;
    f32 mEndZ;
    f32 mNearZ;
    f32 mFarZ;
    GXColor mColor;
    GXFogAdjTable mFogAdjTable;
};

struct J3DNBTScaleInfo {
    bool operator==(const J3DNBTScaleInfo& other) const;
    J3DNBTScaleInfo& operator=(const J3DNBTScaleInfo&);

    u8 mbHasScale;
    Vec mScale;
};

struct J3DIndTexOrderInfo {
    u8 mCoord;
    u8 mMap;
    u8 field_0x2;
    u8 field_0x3;

    void operator=(J3DIndTexOrderInfo const& other) {
        std::memcpy(this, &other, sizeof(J3DIndTexOrderInfo));
    }
};

struct J3DTevSwapModeInfo {
    u8 mRasSel;
    u8 mTexSel;
    u8 field_0x2;
    u8 field_0x3;
};

struct J3DTevSwapModeTableInfo {
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2;
    u8 field_0x3;
};

struct J3DTevStageInfo {
    u8 field_0x0;
    u8 mTevColorOp;
    u8 mTevColorAB;
    u8 mTevColorCD;
    u8 field_0x4;
    u8 mTevAlphaOp;
    u8 mTevAlphaAB;
    u8 mTevSwapModeInfo;
    u8 field_0x8;
    u8 field_0x9;
    u8 field_0xa;
    u8 field_0xb;
    u8 field_0xc;
    u8 field_0xd;
    u8 field_0xe;
    u8 field_0xf;
    u8 field_0x10;
    u8 field_0x11;
    u8 field_0x12;
    u8 field_0x13;
};

struct J3DIndTevStageInfo {
    u8 mIndStage;
    u8 mIndFormat;
    u8 mBiasSel;
    u8 mMtxSel;
    u8 mWrapS;
    u8 mWrapT;
    u8 mPrev;
    u8 mLod;
    u8 mAlphaSel;
    u8 pad[3];
};

struct J3DTexCoordInfo {
    u8 mTexGenType;
    u8 mTexGenSrc;
    u8 mTexGenMtx;
    u8 pad;

    J3DTexCoordInfo& operator=(const J3DTexCoordInfo& other) {
        std::memcpy(this, &other, sizeof(J3DTexCoordInfo));
        return *this;
    }
};

struct J3DIndTexCoordScaleInfo {
    u8 mScaleS;
    u8 mScaleT;
    u8 field_0x2;
    u8 field_0x3;

    J3DIndTexCoordScaleInfo& operator=(const J3DIndTexCoordScaleInfo& other) {
        std::memcpy(this, &other, sizeof(J3DIndTexCoordScaleInfo));
        return *this;
    }
};

struct J3DBlendInfo {
    void operator=(J3DBlendInfo const& other) {
        std::memcpy(this, &other, sizeof(J3DBlendInfo));
    }
    u8 mType;
    u8 mSrcFactor;
    u8 mDstFactor;
    u8 mOp;
};

struct J3DTevOrderInfo {
    void operator=(const J3DTevOrderInfo& other) {
        *(u32*) this = *(u32*)&other;
    }

    u8 mTexCoord;
    u8 mTexMap;
    u8 mColorChan;
    u8 field_0x3; // Maybe padding
};

struct J3DColorChanInfo {
    u8 mEnable;
    u8 mMatSrc;
    u8 mLightMask;
    u8 mDiffuseFn;
    u8 mAttnFn;
    u8 mAmbSrc;
    u8 pad[2];
};

struct J3DZModeInfo {
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2;
    u8 pad;
};

struct J3DAlphaCompInfo {
    u8 mComp0;
    u8 mRef0;
    u8 mOp;
    u8 mComp1;
    u8 mRef1;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;

    J3DAlphaCompInfo& operator=(const J3DAlphaCompInfo& other) {
        mComp0 = other.mComp0;
        mRef0 = other.mRef0;
        mOp = other.mOp;
        mComp1 = other.mComp1;
        mRef1 = other.mRef1;
        return *this;
    }
};

#endif
