#ifndef J3DJOINT_H
#define J3DJOINT_H

#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

class J3DAnmTransform;
class J3DJoint;
class J3DMaterial;
class J3DMtxBuffer;

class J3DMtxCalc {
public:
    static void setMtxBuffer(J3DMtxBuffer*);

    virtual ~J3DMtxCalc() {}
    virtual void setAnmTransform(J3DAnmTransform*) {}
    virtual J3DAnmTransform* getAnmTransform() {
        return NULL;
    }
    virtual void setAnmTransform(u8, J3DAnmTransform*) {}
    virtual J3DAnmTransform* getAnmTransform(u8) {
        return NULL;
    }
    virtual void setWeight(u8, f32) {}
    virtual f32 getWeight(u8) const {
        return 0.0f;
    }
    virtual void init(const Vec& param_0, const Mtx&) = 0;
    virtual void calc() = 0;

    static J3DMtxBuffer* getMtxBuffer() { return mMtxBuffer; }
    static J3DJoint* getJoint() {
        return mJoint;
    }
    static void setJoint(J3DJoint* joint) { mJoint = joint; }

    static J3DMtxBuffer* mMtxBuffer;
    static J3DJoint* mJoint;
};

typedef int (*J3DJointCallBack)(J3DJoint*, int);

class J3DJoint {
public:
    void appendChild(J3DJoint*);
    J3DJoint();
    void entryIn();
    void recursiveCalc();

    u32 getType() const { return 'NJNT'; }

    J3DMaterial* getMesh() { return mMesh; }
    void addMesh(J3DMaterial* pMesh) {
        if (mMesh != NULL) {
            pMesh->setNext(mMesh);
        }

        mMesh = pMesh;
    }

    u16 getJntNo() const { return mJntNo; }
    u8 getScaleCompensate() const { return mScaleCompensate; }
    J3DJoint* getYounger() { return mYounger; }
    void setYounger(J3DJoint* pYounger) { mYounger = pYounger; }
    void setCurrentMtxCalc(J3DMtxCalc* pMtxCalc) { mCurrentMtxCalc = pMtxCalc; }
    J3DTransformInfo& getTransformInfo() { return mTransformInfo; }
    void setTransformInfo(const J3DTransformInfo& i_info) { mTransformInfo = i_info; }
    Vec* getMax() { return &mMax; }
    Vec* getMin() { return &mMin; }
    void setCallBack(J3DJointCallBack callback) { mCallBack = callback; }
    J3DJointCallBack getCallBack() { return mCallBack; }
    void setMtxCalc(J3DMtxCalc* i_mtxCalc) { mMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getMtxCalc() { return mMtxCalc; }
    J3DMtxCalc* getCurrentMtxCalc() { return mCurrentMtxCalc; };
    J3DJoint* getChild() { return mChild; }
    u8 getMtxType() const { return (mKind & 0xf0) >> 4; }
    void setMtxType(u8 type) { mKind = (mKind & ~0xf0) | (type << 4); }
    f32 getRadius() const { return mBoundingSphereRadius; }

    static J3DMtxCalc* mCurrentMtxCalc;

    u8 getKind() const { return mKind & 15; }

private:
    friend struct J3DJointFactory;
    friend class J3DJointTree;

    void* mCallBackUserData;
    J3DJointCallBack mCallBack;
    void* field_0x8;
    J3DJoint* mChild;
    J3DJoint* mYounger;
    u16 mJntNo;
    u8 mKind;
    u8 mScaleCompensate;
    J3DTransformInfo mTransformInfo;
    f32 mBoundingSphereRadius;
    Vec mMin;
    Vec mMax;
    J3DMtxCalc* mMtxCalc;
    J3DMaterial* mMesh;
};

class J3DMtxCalcNoAnmBase : public J3DMtxCalc {
public:
    virtual ~J3DMtxCalcNoAnmBase() {}
};

template <class A, class B>
class J3DMtxCalcNoAnm : public J3DMtxCalcNoAnmBase {
public:
    J3DMtxCalcNoAnm() {}
    virtual ~J3DMtxCalcNoAnm() {}
    virtual void init(const Vec& param_0, const Mtx& param_1) { B::init(param_0, param_1); }
    virtual void calc() {
        J3DTransformInfo& transInfo = getJoint()->getTransformInfo();
        A::calcTransform(transInfo);
    }
};

struct J3DMtxCalcAnmBase: public J3DMtxCalc {
    J3DMtxCalcAnmBase(J3DAnmTransform* pAnmTransform) { mAnmTransform = pAnmTransform; }
    ~J3DMtxCalcAnmBase() {}
    J3DAnmTransform* getAnmTransform() { return mAnmTransform; }
    void setAnmTransform(J3DAnmTransform* pAnmTransform) { mAnmTransform = pAnmTransform; }

    J3DAnmTransform* mAnmTransform;
};

struct J3DMtxCalcAnimationAdaptorBase {
    J3DMtxCalcAnimationAdaptorBase() {}
    void change(J3DAnmTransform*) {}
};

template <typename A0>
struct J3DMtxCalcAnimationAdaptorDefault : public J3DMtxCalcAnimationAdaptorBase {
    J3DMtxCalcAnimationAdaptorDefault(J3DAnmTransform* pAnmTransform) {}

    void calc(J3DMtxCalcAnmBase* pMtxCalc) {
        J3DTransformInfo transform;
        J3DTransformInfo* transform_p;
        if (pMtxCalc->getAnmTransform() != NULL) {
            pMtxCalc->getAnmTransform()->getTransform(J3DMtxCalc::getJoint()->getJntNo(), &transform);
            transform_p = &transform;
        } else {
            transform_p = &J3DMtxCalc::getJoint()->getTransformInfo();
        }

        A0::calcTransform(*transform_p);
    }
};

template <typename A0, typename B0>
struct J3DMtxCalcAnimation : public J3DMtxCalcAnmBase {
    J3DMtxCalcAnimation(J3DAnmTransform* pAnmTransform) : J3DMtxCalcAnmBase(pAnmTransform), field_0x8(pAnmTransform) {}
    ~J3DMtxCalcAnimation() {}

    void setAnmTransform(J3DAnmTransform* pAnmTransform) {
        mAnmTransform = pAnmTransform;
        field_0x8.change(pAnmTransform);
    }

    void init(const Vec& param_0, const Mtx& param_1) { B0::init(param_0, param_1); }
    void calc() { field_0x8.calc(this); }

    A0 field_0x8;
};

struct J3DMtxCalcJ3DSysInitMaya {
    static void init(const Vec&, const Mtx& param_1);
};

struct J3DMtxCalcJ3DSysInitBasic {
    static void init(const Vec&, const Mtx& param_1);
};

struct J3DMtxCalcCalcTransformSoftimage {
    static void calcTransform(J3DTransformInfo const&);
};

struct J3DMtxCalcCalcTransformMaya {
    static void calcTransform(J3DTransformInfo const&);
};

struct J3DMtxCalcCalcTransformBasic {
    static void calcTransform(J3DTransformInfo const&);
};

#endif
