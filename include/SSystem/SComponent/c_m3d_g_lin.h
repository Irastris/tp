#ifndef C_M3D_G_LIN_H
#define C_M3D_G_LIN_H

#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

// Line
class cM3dGLin {
    // private:
public:
    cXyz mStart;
    cXyz mEnd;

    cM3dGLin() {}
    cM3dGLin(const cXyz&, const cXyz&);
    virtual ~cM3dGLin() {}
    void SetStartEnd(const cXyz&, const cXyz&);
    void SetStartEnd(const Vec&, const Vec&);
    void CalcPos(Vec*, f32) const;
    void CalcVec(Vec* pOut) const { VECSubtract(&this->mEnd, &this->mStart, pOut); }
    void SetEnd(const cXyz&);

    void set(const Vec& i_start, const Vec& i_end) { SetStartEnd(i_start, i_end); }
    const cXyz& GetStartP(void) const { return mStart; }
    cXyz& GetStartP(void) { return mStart; }
    cXyz& GetStart() { return mStart; }
    const cXyz& GetStart() const { return mStart; }

    const cXyz& GetEndP(void) const { return mEnd; }
    cXyz& GetEndP(void) { return mEnd; }
    cXyz& GetEnd() { return mEnd; }
    const cXyz& GetEnd() const { return mEnd; }
    f32 GetLen() const { return VECDistance(&mStart, &mEnd); }
};

#endif
