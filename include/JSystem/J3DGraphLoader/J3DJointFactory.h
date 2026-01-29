#ifndef J3DJOINTFACTORY_H
#define J3DJOINTFACTORY_H

#include "JSystem/J3DGraphBase/J3DTransform.h"

class J3DJoint;
struct J3DJointBlock;

struct J3DJointInitData {
    u16 mKind;
    bool mScaleCompensate;
    J3DTransformInfo mTransformInfo;
    f32 mRadius;
    Vec mMin;
    Vec mMax;
};

struct J3DJointFactory {
    J3DJointFactory(J3DJointBlock const&);
    J3DJoint* create(int);

    J3DJointInitData* mJointInitData;
    u16* mIndexTable;

    u8 getKind(int no) const { return mJointInitData[mIndexTable[no]].mKind; }
    u8 getScaleCompensate(int no) const { return mJointInitData[mIndexTable[no]].mScaleCompensate; }
    const J3DTransformInfo& getTransformInfo(int no) const { return mJointInitData[mIndexTable[no]].mTransformInfo; }
    f32 getRadius(int no) const { return mJointInitData[mIndexTable[no]].mRadius; }
    Vec& getMin(int no) const { return mJointInitData[mIndexTable[no]].mMin; }
    Vec& getMax(int no) const { return mJointInitData[mIndexTable[no]].mMax; }
};

#endif
