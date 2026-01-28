#ifndef J3DANIMATION_H
#define J3DANIMATION_H

#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "global.h"

// TODO: Not originally included directly
#include "dolphin/os.h"

struct JUTDataBlockHeader {
    u32 mType;
    u32 mSize;

    const JUTDataBlockHeader* getNext() const { return reinterpret_cast<const JUTDataBlockHeader*>(reinterpret_cast<const u8*>(this) + mSize); }
};

struct JUTDataFileHeader {
    u32 mMagic;
    u32 mType;
    u32 mFileSize;
    u32 mBlockNum;
    u8 _10[0x1C - 0x10];
    u32 mSeAnmOffset;
    JUTDataBlockHeader mFirstBlock;
};

struct J3DAnmTransform_ANK1 {
    u32 magic;
    u32 size;
    u8 attribute;
    u8 rotation_frac;
    s16 duration;
    s16 keyframe_num;
    s16 scale_entries;
    s16 rotation_entries;
    s16 translation_entries;
    u32 anm_data_offset;
    u32 scale_data_offset;
    u32 rotation_data_offset;
    u32 translation_data_offset;
};

struct J3DAnmKeyTableBase {
    u16 mMaxFrame;
    u16 mOffset;
    u16 mType;
};

struct J3DAnmColorKeyTable {
    J3DAnmKeyTableBase mRInfo;
    J3DAnmKeyTableBase mGInfo;
    J3DAnmKeyTableBase mBInfo;
    J3DAnmKeyTableBase mAInfo;
};

struct J3DAnmVtxColorIndexData {
    u16 mNum;
    void* mpData;
};

struct J3DAnmColorFullTable {
    u16 mRMaxFrame;
    u16 mROffset;
    u16 mGMaxFrame;
    u16 mGOffset;
    u16 mBMaxFrame;
    u16 mBOffset;
    u16 mAMaxFrame;
    u16 mAOffset;
};

struct J3DAnmVisibilityFullTable {
    u16 _0;
    u16 _2;
};

struct J3DAnmTransformKeyTable {
    J3DAnmKeyTableBase mScaleInfo;
    J3DAnmKeyTableBase mRotationInfo;
    J3DAnmKeyTableBase mTranslateInfo;
};

struct J3DAnmTransformFullTable {
    u16 mScaleMaxFrame;
    u16 mScaleOffset;
    u16 mRotationMaxFrame;
    u16 mRotationOffset;
    u16 mTranslateMaxFrame;
    u16 mTranslateOffset;
};

struct J3DAnmTexPatternFullTable {
    u16 mMaxFrame;
    u16 mOffset;
    u8 mTexNo;
    u16 _6;
};

struct J3DAnmCRegKeyTable {
    J3DAnmKeyTableBase mRTable;
    J3DAnmKeyTableBase mGTable;
    J3DAnmKeyTableBase mBTable;
    J3DAnmKeyTableBase mATable;
    u8 mColorId;
    u8 padding[3];
};

struct J3DAnmKRegKeyTable {
    J3DAnmKeyTableBase mRTable;
    J3DAnmKeyTableBase mGTable;
    J3DAnmKeyTableBase mBTable;
    J3DAnmKeyTableBase mATable;
    u8 mColorId;
    u8 padding[3];
};

struct J3DAnmDataBlockHeader {  // actual name unknown
    u32 mType;
    u32 mNextOffset;
};

struct J3DAnmDataHeader {  // actual name unknown
    u32 mMagic;
    u32 mType;
    u8 _8[4];
    u32 mCount;
    u8 _10[0x20 - 0x10];
    J3DAnmDataBlockHeader mFirst;
};

struct J3DAnmVtxColorFullData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;  // padding?
    s16 mFrameMax;
    u16 mAnmTableNum[2];
    u8 field_0x10[0x18 - 0x10];
    void* mTableOffsets[2];
    void* mVtxColorIndexDataOffsets[2];
    void* mVtxColorIndexPointerOffsets[2];
    void* mRValuesOffset;
    void* mGValuesOffset;
    void* mBValuesOffset;
    void* mAValuesOffset;
};

struct J3DAnmVisibilityFullData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;  // padding?
    s16 mFrameMax;
    u16 field_0xc;
    u16 field_0xe;
    void* mTableOffset;
    void* mValuesOffset;
};

struct J3DAnmTransformFullData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;
    s16 mFrameMax;
    u16 field_0xc;
    u8 field_0xe[0x14 - 0xe];
    void* mTableOffset;
    void* mScaleValOffset;
    void* mRotValOffset;
    void* mTransValOffset;
};

struct J3DAnmColorKeyData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9[3];
    s16 mFrameMax;
    u16 mUpdateMaterialNum;
    u16 field_0x10;
    u16 field_0x12;
    u16 field_0x14;
    u16 field_0x16;
    void* mTableOffset;
    void* mUpdateMaterialIDOffset;
    void* mNameTabOffset;
    void* mRValOffset;
    void* mGValOffset;
    void* mBValOffset;
    void* mAValOffset;
};

struct J3DAnmTextureSRTKeyData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;
    s16 field_0xa;
    u16 field_0xc;
    u16 field_0xe;
    u16 field_0x10;
    u16 field_0x12;
    void* mTableOffset;
    void* mUpdateMatIDOffset;
    void* mNameTab1Offset;
    void* mUpdateTexMtxIDOffset;
    void* unkOffset;
    void* mScaleValOffset;
    void* mRotValOffset;
    void* mTransValOffset;
    u16 field_0x34;
    u16 field_0x36;
    u16 field_0x38;
    u16 field_0x3a;
    void* mInfoTable2Offset;
    void* field_0x40;
    void* mNameTab2Offset;
    void* field_0x48;
    void* field_0x4c;
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    s32 field_0x5c;
};

struct J3DAnmVtxColorKeyData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;
    s16 mFrameMax;
    u16 mAnmTableNum[2];
    u8 field_0x10[0x18 - 0x10];
    void* mTableOffsets[2];
    void* mVtxColoIndexDataOffset[2];
    void* mVtxColoIndexPointerOffset[2];
    void* mRValOffset;
    void* mGValOffset;
    void* mBValOffset;
    void* mAValOffset;
};

struct J3DAnmTexPatternFullData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;
    s16 mFrameMax;
    u16 field_0xc;
    u16 field_0xe;
    void* mTableOffset;
    void* mValuesOffset;
    void* mUpdateMaterialIDOffset;
    void* mNameTabOffset;
};

struct J3DAnmTevRegKeyData {
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;  // maybe padding
    s16 mFrameMax;
    u16 mCRegUpdateMaterialNum;
    u16 mKRegUpdateMaterialNum;
    u16 field_0x10;
    u16 field_0x12;
    u16 field_0x14;
    u16 field_0x16;
    u16 field_0x18;
    u16 field_0x1a;
    u16 field_0x1c;
    u16 field_0x1e;
    void* mCRegTableOffset;
    void* mKRegTableOffset;
    void* mCRegUpdateMaterialIDOffset;
    void* mKRegUpdateMaterialIDOffset;
    void* mCRegNameTabOffset;
    void* mKRegNameTabOffset;
    void* mCRValuesOffset;
    void* mCGValuesOffset;
    void* mCBValuesOffset;
    void* mCAValuesOffset;
    void* mKRValuesOffset;
    void* mKGValuesOffset;
    void* mKBValuesOffset;
    void* mKAValuesOffset;
};

struct J3DAnmColorFullData { /* PlaceHolder Structure */
    J3DAnmDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9[3];
    s16 mFrameMax;
    u16 mUpdateMaterialNum;
    u8 field_0x10[0x18 - 0x10];
    void* mTableOffset;
    void* mUpdateMaterialIDOffset;
    void* mNameTabOffset;
    void* mRValuesOffset;
    void* mGValuesOffset;
    void* mBValuesOffset;
    void* mAValuesOffset;
};

struct J3DAnmClusterKeyTable {
    J3DAnmKeyTableBase mWeightTable;
};

struct J3DAnmTransformKeyData {
    JUTDataBlockHeader mHeader;
    u8 field_0x8;
    u8 field_0x9;
    s16 mFrameMax;
    u16 field_0xc;
    int field_0x10;
    void* mTableOffset;
    void* field_0x18;
    void* field_0x1c;
    void* field_0x20;
};

struct J3DAnmClusterKeyData {
    JUTDataBlockHeader mHeader;
    u8 field_0x8;
    s16 mFrameMax;
    s32 field_0xc;
    void* mTableOffset;
    void* mWeightOffset;
};

struct J3DAnmClusterFullData {
    JUTDataBlockHeader mHeader;
    u8 field_0x8;
    s16 mFrameMax;
    s32 field_0xc;
    void* mTableOffset;
    void* mWeightOffset;
};

struct J3DAnmClusterFullTable {
    u16 mMaxFrame;
    u16 mOffset;
};

class J3DAnmBase {
public:
    J3DAnmBase() {
        mAttribute = 0;
        field_0x5 = 0;
        mFrameMax = 0;
        mFrame = 0.0f;
    }

    J3DAnmBase(s16 frameMax) {
        mAttribute = 0;
        field_0x5 = 0;
        mFrameMax = frameMax;
        mFrame = 0.0f;
    }

    virtual ~J3DAnmBase() {}
    virtual s32 getKind() const = 0;

    u8 getAttribute() const { return mAttribute; }
    s16 getFrameMax() const { return mFrameMax; }
    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }

    u8 mAttribute;
    u8 field_0x5;
    s16 mFrameMax;
    f32 mFrame;
};

class J3DAnmTransform : public J3DAnmBase {
public:
    J3DAnmTransform(s16, f32*, s16*, f32*);

    virtual ~J3DAnmTransform() {}
    virtual s32 getKind() const { return 0; }
    virtual void getTransform(u16, J3DTransformInfo*) const = 0;

    f32* mScaleData;
    s16* mRotData;
    f32* mTransData;
    s16 field_0x18;
    s16 field_0x1a;
    u16 field_0x1c;
    u16 field_0x1e;
};

class J3DAnmTransformKey : public J3DAnmTransform {
public:
    J3DAnmTransformKey() : J3DAnmTransform(0, NULL, NULL, NULL) {
        mDecShift = 0;
        mAnmTable = 0;
    }

    void calcTransform(f32, u16, J3DTransformInfo*) const;

    virtual ~J3DAnmTransformKey() {}
    virtual s32 getKind() const { return 8; }
    virtual void getTransform(u16 jointNo, J3DTransformInfo* pTransform) const {
        calcTransform(mFrame, jointNo, pTransform);
    }

    int mDecShift;
    J3DAnmTransformKeyTable* mAnmTable;
};

class J3DAnmTransformFull : public J3DAnmTransform {
public:
    J3DAnmTransformFull() : J3DAnmTransform(0, NULL, NULL, NULL) { mAnmTable = NULL; }

    virtual ~J3DAnmTransformFull() {}
    virtual s32 getKind() const { return 9; }
    virtual void getTransform(u16, J3DTransformInfo*) const;

    J3DAnmTransformFullTable* mAnmTable;
};

class J3DAnmTransformFullWithLerp : public J3DAnmTransformFull {
public:
    virtual ~J3DAnmTransformFullWithLerp() {}
    virtual s32 getKind() const { return 16; }
    virtual void getTransform(u16, J3DTransformInfo*) const;
};

struct J3DTextureSRTInfo;
class J3DModelData;
class J3DMaterialTable;

class J3DAnmTextureSRTKey : public J3DAnmBase {
public:
    J3DAnmTextureSRTKey();
    void calcTransform(f32, u16, J3DTextureSRTInfo*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTextureSRTKey() {}
    virtual s32 getKind() const { return 4; }

    void getTransform(u16 jointNo, J3DTextureSRTInfo* pSRTInfo) const {
        calcTransform(getFrame(), jointNo, pSRTInfo);
    }

    u16 getUpdateMaterialID(u16 idx) const {
        return mUpdateMaterialID[idx];
    }
    u16 getUpdateMaterialNum() const { return mTrackNum / 3; }
    u16 getPostUpdateMaterialNum() const { return field_0x4a / 3; }

    int getUpdateTexMtxID(u16 idx) const {
        return mUpdateTexMtxID[idx];
    }
    bool isValidUpdateMaterialID(u16 idx) const { return mUpdateMaterialID[idx] != 0xffff; }
    u32 getTexMtxCalcType() { return mTexMtxCalcType; }
    Vec* getSRTCenter(u16 idx) {
        return &mSRTCenter[idx];
    }

    int mDecShift;
    J3DAnmTransformKeyTable* mAnmTable;
    u16 mTrackNum;
    u16 mScaleNum;
    u16 mRotNum;
    u16 mTransNum;
    f32* mScaleData;
    s16* mRotData;
    f32* mTransData;
    u8* mUpdateTexMtxID;
    u16* mUpdateMaterialID;
    JUTNameTab mUpdateMaterialName;
    Vec* mSRTCenter;
    u16 field_0x44;
    u16 field_0x46;
    u16 field_0x48;
    u16 field_0x4a;
    void* field_0x4c;
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    u8* mPostUpdateTexMtxID;
    u16* mPostUpdateMaterialID;
    JUTNameTab mPostUpdateMaterialName;
    Vec* mPostSRTCenter;
    u32 mTexMtxCalcType;
};

class J3DAnmCluster : public J3DAnmBase {
public:
    J3DAnmCluster(s16 frameMax, f32* pWeight) : J3DAnmBase(frameMax) { mWeight = pWeight; }

    virtual ~J3DAnmCluster() {}
    virtual s32 getKind() const { return 3; }
    virtual f32 getWeight(u16) const { return 1.0f; }

    f32* mWeight;
};

class J3DAnmClusterFull : public J3DAnmCluster {
public:
    J3DAnmClusterFull() : J3DAnmCluster(0, NULL) { mAnmTable = NULL; }

    virtual ~J3DAnmClusterFull() {}
    virtual s32 getKind() const { return 12; }
    virtual f32 getWeight(u16) const;

    J3DAnmClusterFullTable* mAnmTable;
};

class J3DAnmClusterKey : public J3DAnmCluster {
public:
    J3DAnmClusterKey() : J3DAnmCluster(0, NULL) { mAnmTable = NULL; }

    virtual ~J3DAnmClusterKey() {}
    virtual s32 getKind() const { return 13; }
    virtual f32 getWeight(u16) const;

    J3DAnmClusterKeyTable* mAnmTable;
};

class J3DAnmVtxColor : public J3DAnmBase {
public:
    J3DAnmVtxColor();

    virtual ~J3DAnmVtxColor() {}
    virtual s32 getKind() const { return 7; }
    virtual void getColor(u8, u16, GXColor*) const {}

    u16 getAnmTableNum(u8 idx) {
        return mAnmTableNum[idx];
    }

    J3DAnmVtxColorIndexData* getAnmVtxColorIndexData(u8 p1, u16 p2) {
        return mAnmVtxColorIndexData[p1] + p2;
    }

    u16 mAnmTableNum[2];
    J3DAnmVtxColorIndexData* mAnmVtxColorIndexData[2];
};

class J3DAnmVtxColorFull : public J3DAnmVtxColor {
public:
    J3DAnmVtxColorFull();

    virtual ~J3DAnmVtxColorFull() {}
    virtual s32 getKind() const { return 14; }
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorFullTable* mpTable[2];
    u8* mColorR;
    u8* mColorG;
    u8* mColorB;
    u8* mColorA;
};

class J3DAnmVtxColorKey : public J3DAnmVtxColor {
public:
    J3DAnmVtxColorKey();

    virtual ~J3DAnmVtxColorKey() {}
    virtual s32 getKind() const { return 15; }
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorKeyTable* mpTable[2];
    s16* mColorR;
    s16* mColorG;
    s16* mColorB;
    s16* mColorA;
};

class J3DAnmColor : public J3DAnmBase {
public:
    J3DAnmColor();
    void searchUpdateMaterialID(J3DMaterialTable*);

    virtual ~J3DAnmColor() {}
    virtual s32 getKind() const { return 1; }
    virtual void getColor(u16, GXColor*) const {}

    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    bool isValidUpdateMaterialID(u16 id) const { return mUpdateMaterialID[id] != 0xFFFF; }
    u16 getUpdateMaterialID(u16 idx) const {
        return mUpdateMaterialID[idx];
    }

    u16 field_0xc;
    u16 field_0xe;
    u16 field_0x10;
    u16 field_0x12;
    u16 mUpdateMaterialNum;
    u16* mUpdateMaterialID;
    JUTNameTab mUpdateMaterialName;
};

class J3DAnmColorFull : public J3DAnmColor {
public:
    J3DAnmColorFull();

    virtual ~J3DAnmColorFull() {}
    virtual s32 getKind() const { return 10; }
    virtual void getColor(u16, GXColor*) const;

    u8* mColorR;
    u8* mColorG;
    u8* mColorB;
    u8* mColorA;
    J3DAnmColorFullTable* mAnmTable;
};

class J3DAnmColorKey : public J3DAnmColor {
public:
    J3DAnmColorKey();

    virtual ~J3DAnmColorKey() {}
    virtual s32 getKind() const { return 11; }
    virtual void getColor(u16, GXColor*) const;

    s16* mColorR;
    s16* mColorG;
    s16* mColorB;
    s16* mColorA;
    J3DAnmColorKeyTable* mAnmTable;
};

class J3DAnmTevRegKey : public J3DAnmBase {
public:
    J3DAnmTevRegKey();
    void getTevColorReg(u16, GXColorS10*) const;
    void getTevKonstReg(u16, GXColor*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTevRegKey() {}
    virtual s32 getKind() const { return 5; }

    u16 getCRegUpdateMaterialNum() const { return mCRegUpdateMaterialNum; }
    u16 getKRegUpdateMaterialNum() const { return mKRegUpdateMaterialNum; }

    u16 getCRegUpdateMaterialID(u16 idx) const {
        return mCRegUpdateMaterialID[idx];
    }
    u16 getKRegUpdateMaterialID(u16 idx) const {
        return mKRegUpdateMaterialID[idx];
    }

    const J3DAnmCRegKeyTable* getAnmCRegKeyTable() { return mAnmCRegKeyTable; }
    const J3DAnmKRegKeyTable* getAnmKRegKeyTable() { return mAnmKRegKeyTable; }

    bool isValidCRegUpdateMaterialID(u16 idx) const { return mCRegUpdateMaterialID[idx] != 0xffff; }
    bool isValidKRegUpdateMaterialID(u16 idx) const { return mKRegUpdateMaterialID[idx] != 0xffff; }

    u16 mCRegUpdateMaterialNum;
    u16 mKRegUpdateMaterialNum;
    u16 mCRegDataCountR;
    u16 mCRegDataCountG;
    u16 mCRegDataCountB;
    u16 mCRegDataCountA;
    u16 mKRegDataCountR;
    u16 mKRegDataCountG;
    u16 mKRegDataCountB;
    u16 mKRegDataCountA;
    u16* mCRegUpdateMaterialID;
    JUTNameTab mCRegUpdateMaterialName;
    u16* mKRegUpdateMaterialID;
    JUTNameTab mKRegUpdateMaterialName;
    J3DAnmCRegKeyTable* mAnmCRegKeyTable;
    J3DAnmKRegKeyTable* mAnmKRegKeyTable;
    s16* mAnmCRegDataR;
    s16* mAnmCRegDataG;
    s16* mAnmCRegDataB;
    s16* mAnmCRegDataA;
    s16* mAnmKRegDataR;
    s16* mAnmKRegDataG;
    s16* mAnmKRegDataB;
    s16* mAnmKRegDataA;
};

class J3DAnmTexPattern : public J3DAnmBase {
public:
    J3DAnmTexPattern();
    void getTexNo(u16, u16*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTexPattern() {}
    virtual s32 getKind() const { return 2; }

    u16 getUpdateMaterialID(u16 idx) const {
        return mUpdateMaterialID[idx];
    }
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    bool isValidUpdateMaterialID(u16 id) const { return mUpdateMaterialID[id] != 0xFFFF; }
    J3DAnmTexPatternFullTable* getAnmTable() { return mAnmTable; }

    u16* mTextureIndex;
    J3DAnmTexPatternFullTable* mAnmTable;
    u16 field_0x14;
    u16 mUpdateMaterialNum;
    u16* mUpdateMaterialID;
    JUTNameTab mUpdateMaterialName;
};

class J3DAnmVisibilityFull : public J3DAnmBase {
public:
    J3DAnmVisibilityFull() : J3DAnmBase() {
        mUpdateMaterialNum = 0;
        field_0xe = 0;
        mAnmTable = NULL;
        mVisibility = NULL;
    }

    virtual ~J3DAnmVisibilityFull() {}
    virtual s32 getKind() const { return 6; }

    u16 mUpdateMaterialNum;
    u16 field_0xe;
    J3DAnmVisibilityFullTable* mAnmTable;
    u8* mVisibility;
};

class J3DFrameCtrl {
public:
    enum Attribute_e {
        EMode_NULL = -1,
        EMode_NONE,
        EMode_RESET,
        EMode_LOOP,
        EMode_REVERSE,
        EMode_LOOP_REVERSE,
    };

    J3DFrameCtrl() { this->init(0); }
    void init(s16);
    void init(int endFrame) { init((s16)endFrame); }
    BOOL checkPass(f32);
    void update();
    virtual ~J3DFrameCtrl() {}

    u8 getAttribute() const { return mAttribute; }
    void setAttribute(u8 attr) { mAttribute = attr; }
    u8 getState() const { return mState; }
    bool checkState(u8 state) const { return mState & state ? true : false; }
    s16 getStart() const { return mStart; }
    void setStart(s16 start) {
        mStart = start;
        mFrame = start;
    }
    s16 getEnd() const { return mEnd; }
    void setEnd(s16 end) { mEnd = end; }
    s16 getLoop() const { return mLoop; }
    void setLoop(s16 loop) { mLoop = loop; }
    f32 getRate() const { return mRate; }
    void setRate(f32 rate) { mRate = rate; }
    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }
    void reset() {
        mFrame = mStart;
        mRate = 1.0f;
        mState = 0;
    }

    u8 mAttribute;
    u8 mState;
    s16 mStart;
    s16 mEnd;
    s16 mLoop;
    f32 mRate;
    f32 mFrame;
};

#endif
