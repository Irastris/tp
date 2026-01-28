#include "SSystem/SComponent/c_m2d.h"
#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_m3d_g_cir.h"

void cM2d_CrossCirLin(cM2dGCir& param_0, f32 param_1, f32 param_2, f32 param_3, f32 param_4, f32* param_5, f32* param_6) {
    int ans = 0;
    f32 fVar1 = param_1 - param_0.GetCx();
    f32 fVar15 = param_2 - param_0.GetCy();
    f32 dVar13 = param_3 * param_3 + param_4 * param_4;
    f32 dVar14 = 2.0f * ((param_3 * fVar1) + (param_4 * fVar15));

    f32 c = (fVar1 * fVar1 + fVar15 * fVar15) - (param_0.GetR() * param_0.GetR());

    f32 t;

    if (cM3d_IsZero(dVar13)) {
        if (cM3d_IsZero(dVar14)) {
            ans = 0;
        } else {
            ans = 1;
            t = -c / dVar14;
        }
    } else {
        f32 dVar10 = ((dVar14 * dVar14) - (4.0f * dVar13) * c);
        if (cM3d_IsZero(dVar10)) {
            ans = 1;
            t = (-dVar14 / (2.0f * dVar13));
        } else {
            if (dVar10 < 0.0f) {
                ans = 0;
            } else {
                ans = 2;

                f32 fVar2 = 1.0f / (2.0f * dVar13);
                f32 fVar15 = fVar2 * (-dVar14 + sqrtf(dVar10));
                f32 fVar4 = fVar2 * (-dVar14 - sqrtf(dVar10));
                if (fVar15 > fVar4) {
                    t = fVar15;
                } else {
                    t = fVar4;
                }
            }
        }
    }

    if (cM3d_IsZero(t)) {
        *param_5 = param_1;
        *param_6 = param_2;
    } else {
        *param_5 = param_1 + (t * param_3);
        *param_6 = param_2 + (t * param_4);
    }
}
