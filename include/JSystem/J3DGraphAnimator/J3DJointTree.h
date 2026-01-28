#ifndef J3DJOINTTREE_H
#define J3DJOINTTREE_H

#include "JSystem/J3DGraphBase/J3DTransform.h"

class J3DJoint;
class J3DMtxBuffer;
class J3DMtxCalc;
class JUTNameTab;

struct J3DModelHierarchy {
    u16 mType;
    u16 mValue;
};

class J3DMaterialTable;

struct J3DDrawMtxData {
    J3DDrawMtxData();
    ~J3DDrawMtxData();

    u16 mEntryNum;
    u16 mDrawFullWgtMtxNum;
    u8* mDrawMtxFlag;
    u16* mDrawMtxIndex;
};

class J3DShapeTable;

class J3DJointTree {
public:
    J3DJointTree();
    void makeHierarchy(J3DJoint*, J3DModelHierarchy const**, J3DMaterialTable*, J3DShapeTable*);
    void findImportantMtxIndex();

    virtual void calc(J3DMtxBuffer*, Vec const&, f32 const (&)[3][4]);
    virtual ~J3DJointTree() {}

    const J3DModelHierarchy* getHierarchy() const { return mHierarchy; }
    void setHierarchy(J3DModelHierarchy* hierarchy) { mHierarchy = hierarchy; }
    void setBasicMtxCalc(J3DMtxCalc* calc) { mBasicMtxCalc = calc; }
    u16 getWEvlpMtxNum() const { return mWEvlpMtxNum; }
    u16* getWEvlpMixIndex() const { return mWEvlpMixMtxIndex; }
    u8 getWEvlpMixMtxNum(u16 idx) const { return mWEvlpMixMtxNum[idx]; }
    u16 * getWEvlpMixMtxIndex() const { return mWEvlpMixMtxIndex; }
    f32 * getWEvlpMixWeight() const { return mWEvlpMixWeight; }
    u16 * getWEvlpImportantMtxIndex() const { return mWEvlpImportantMtxIdx; }
    u16 getDrawFullWgtMtxNum() const { return mDrawMtxData.mDrawFullWgtMtxNum; }
    u16 getJointNum() const { return mJointNum; }
    u16 getDrawMtxNum() const { return mDrawMtxData.mEntryNum; }
    u8 getDrawMtxFlag(u16 idx) const { return mDrawMtxData.mDrawMtxFlag[idx]; }
    u16 getDrawMtxIndex(u16 idx) const { return mDrawMtxData.mDrawMtxIndex[idx]; }
    J3DDrawMtxData* getDrawMtxData() { return &mDrawMtxData; }
    JUTNameTab* getJointName() const { return mJointName; }
    J3DJoint* getRootNode() { return mRootNode; }
    J3DJoint* getJointNodePointer(u16 idx) const { return mJointNodePointer[idx]; }
    J3DMtxCalc* getBasicMtxCalc() { return mBasicMtxCalc; }
    Mtx& getInvJointMtx(int idx) { return mInvJointMtx[idx]; }
    u32 getModelDataType() const { return mModelDataType; }
    void setModelDataType(u32 type) { mModelDataType = type; }
    bool checkFlag(u32 flag) const { return mFlags & flag ? true : false; }
    void setFlag(u32 flag) { mFlags = flag; }

private:
    friend class J3DModelLoader;

    J3DModelHierarchy* mHierarchy;
    u32 mFlags;
    u32 mModelDataType;
    J3DJoint* mRootNode;
    J3DMtxCalc* mBasicMtxCalc;
    J3DJoint** mJointNodePointer;
    u16 mJointNum;
    u16 mWEvlpMtxNum;
    u8* mWEvlpMixMtxNum;
    u16* mWEvlpMixMtxIndex;
    f32* mWEvlpMixWeight;
    Mtx* mInvJointMtx;
    u16* mWEvlpImportantMtxIdx;
    J3DDrawMtxData mDrawMtxData;
    u32 field_0x40;
    JUTNameTab* mJointName;
};

#endif
