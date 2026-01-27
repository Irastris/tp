#ifndef C_M3D_G_CPS_H
#define C_M3D_G_CPS_H

#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"

struct cM3dGCpsS {
    Vec mStart;
    Vec mEnd;
    f32 mRadius;
};

class cM3dGCps : public cM3dGLin {
public:
    f32 mRadius;

    cM3dGCps(void);
    virtual ~cM3dGCps(void);
    void Set(const cXyz&, const cXyz&, f32);
    void Set(const cM3dGCpsS&);
    void SetCps(const cM3dGCps&);
    bool Cross(cM3dGCps const* other, cXyz* xyz) const {
        return cM3d_Cross_CpsCps(*this, *other, xyz);
    }
    bool Cross(cM3dGCyl const* cyl, cXyz* xyz) const { return cM3d_Cross_CpsCyl(*this, *cyl, xyz); }
    bool Cross(cM3dGSph const* sph, cXyz* xyz) const { return cM3d_Cross_CpsSph(*this, *sph, xyz); }
    void SetR(f32 r) { mRadius = r; }
    f32 GetR() const { return mRadius; }

};

#endif
