#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "global.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "SSystem/SComponent/c_m3d.h"

class cM3dGAab {
private:
public:
    cXyz mMin;
    cXyz mMax;

    virtual ~cM3dGAab() {}
    void Set(const cXyz*, const cXyz*);
    bool CrossY(const cXyz*) const;
    bool UnderPlaneYUnder(f32) const;
    bool TopPlaneYUnder(f32) const;
    void ClearForMinMax(void);
    void SetMinMax(const cXyz&);
    void SetMinMax(const cM3dGAab&);
    void SetMin(const cXyz&);
    void SetMax(const cXyz&);
    void CalcCenter(cXyz*) const;
    void PlusR(f32);
    const cXyz* GetMaxP(void) const { return &mMax; }
    cXyz* GetMaxP(void) { return &mMax; }
    const cXyz* GetMinP(void) const { return &mMin; }
    cXyz* GetMinP(void) { return &mMin; }
    const f32 GetMaxX(void) const { return mMax.x; }
    const f32 GetMaxY(void) const { return mMax.y; }
    const f32 GetMaxZ(void) const { return mMax.z; }
    const f32 GetMinX(void) const { return mMin.x; }
    const f32 GetMinY(void) const { return mMin.y; }
    const f32 GetMinZ(void) const { return mMin.z; }
    bool Cross(const cM3dGLin *param_1) {
        return cM3d_Cross_MinMaxBoxLine(GetMinP(), GetMaxP(), (Vec*)&param_1->GetStartP(), (Vec*)&param_1->GetEndP());
    }
    bool Cross(const cM3dGAab *param_1) {
        return cM3d_Cross_AabAab(this, param_1);
    }
    bool Cross(const cM3dGCyl *param_1) {
        return cM3d_Cross_AabCyl(this, param_1);
    }
    bool Cross(const cM3dGSph *param_1) {
        return cM3d_Cross_AabSph(this, param_1);
    }
};

#endif
