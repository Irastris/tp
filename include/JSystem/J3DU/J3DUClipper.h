#ifndef J3DUCLIPPER_H
#define J3DUCLIPPER_H

#include <dolphin/mtx.h>

class J3DUClipper {
public:
    J3DUClipper() { init(); }
    virtual ~J3DUClipper() {}
    void init();
    void calcViewFrustum();
    int clip(f32 const (*)[4], Vec, f32) const;
    int clip(f32 const (*)[4], Vec*, Vec*) const;

    void setFovy(f32 fovy) { mFovY = fovy; }
    void setAspect(f32 aspect) { mAspect = aspect; }
    void setNear(f32 near) { mNear = near; }
    void setFar(f32 far) { mFar = far; }

    f32 getFar() { return mFar; }

private:
    Vec _04;
    Vec _10;
    Vec _1C;
    Vec _28;
    u8 _34[0x4C - 0x34];
    f32 mFovY;
    f32 mAspect;
    f32 mNear;
    f32 mFar;
};

#endif
