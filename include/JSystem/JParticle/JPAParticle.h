#ifndef JPAPARTICLE_H
#define JPAPARTICLE_H

#include <dolphin/gx.h>
#include "JSystem/JGeometry.h"

class JKRHeap;
class JPABaseEmitter;
class JPABaseParticle;
class JPAEmitterCallBack;
class JPAEmitterManager;
class JPAParticleCallBack;
class JPAResourceManager;
struct JPAEmitterWorkData;

class JPABaseParticle {
public:
    ~JPABaseParticle() {}
    void init_p(JPAEmitterWorkData*);
    void init_c(JPAEmitterWorkData*, JPABaseParticle*);
    bool calc_p(JPAEmitterWorkData*);
    bool calc_c(JPAEmitterWorkData*);
    bool canCreateChild(JPAEmitterWorkData*);
    f32 getWidth(JPABaseEmitter const*) const;
    f32 getHeight(JPABaseEmitter const*) const;
    int getAge() const { return mAge; }
    void setOffsetPosition(const JGeometry::TVec3<f32>& pos) { mOffsetPosition.set(pos); }
    void setOffsetPosition(f32 x, f32 y, f32 z) { mOffsetPosition.set(x, y, z); }
    void getOffsetPosition(JGeometry::TVec3<f32>& pos) { pos.set(mOffsetPosition); }
    void getOffsetPosition(JGeometry::TVec3<f32>* pos) const { pos->set(mOffsetPosition); }
    u16 getRotateAngle() const { return mRotateAngle; }
    void getGlobalPosition(JGeometry::TVec3<f32>& pos) const { pos.set(mPosition); }
    void getGlobalPosition(JGeometry::TVec3<f32>* pos) const { pos->set(mPosition); }
    f32 getParticleScaleX() const { return mParticleScaleX; }
    f32 getParticleScaleY() const { return mParticleScaleY; }
    void setStatus(u32 flag) { mStatus |= flag; }
    u32 checkStatus(u32 flag) { return mStatus & flag; }
    void initStatus(u32 status) { mStatus = status; }
    void setInvisibleParticleFlag() { setStatus(8); }
    void setDeleteParticleFlag() { setStatus(2); }
    void getVelVec(JGeometry::TVec3<f32>& vec) const { vec.set(mVelocity); }
    void getLocalPosition(JGeometry::TVec3<f32>& vec) const { vec.set(mLocalPosition); }
    void getLocalPosition(JGeometry::TVec3<f32>* vec) const { vec->set(mLocalPosition); }
    void getBaseAxis(JGeometry::TVec3<f32>& vec) const { vec.set(mBaseAxis); }
    void getBaseAxis(JGeometry::TVec3<f32>* vec) const { vec->set(mBaseAxis); }

public:
    JGeometry::TVec3<f32> mPosition;
    JGeometry::TVec3<f32> mLocalPosition;
    JGeometry::TVec3<f32> mOffsetPosition;
    JGeometry::TVec3<f32> mVelocity;
    JGeometry::TVec3<f32> mVelType1;
    JGeometry::TVec3<f32> mVelType0;
    JGeometry::TVec3<f32> mVelType2;
    JGeometry::TVec3<f32> mBaseAxis;
    f32 mParticleScaleX;
    f32 mParticleScaleY;
    f32 mScaleOut;
    f32 mAlphaWaveRandom;
    f32 mMoment;
    f32 mDrag;
    u32 field_0x78;
    u32 mStatus;
    s16 mAge;
    s16 mLifeTime;
    f32 mTime;
    u16 mRotateAngle;
    s16 mRotateSpeed;
    GXColor mPrmClr;
    GXColor mEnvClr;
    u8 mTexAnmIdx;
    u8 mAnmRandom;
    u8 mPrmColorAlphaAnm;
};

class JPAParticleCallBack {
public:
    virtual ~JPAParticleCallBack() = 0;
    virtual void execute(JPABaseEmitter*, JPABaseParticle*) {}
    virtual void draw(JPABaseEmitter*, JPABaseParticle*) {}
};

static inline u32 COLOR_MULTI(u32 a, u32 b) {
    return ((a * (b + 1)) * 0x10000) >> 24;
}

#endif
