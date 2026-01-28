#ifndef J3DTRANSFORM_H
#define J3DTRANSFORM_H

#include <dolphin/mtx.h>

// TODO: Deduplicate instances of these
typedef f32 Mtx33[3][3];
typedef f32 (*Mtx3P)[3];
typedef f32 (*MtxP)[4];

struct J3DTextureSRTInfo;

struct J3DTransformInfo {
    Vec mScale;
    S16Vec mRotation;
    Vec mTranslate;

    inline J3DTransformInfo& operator=(const J3DTransformInfo& b) {
        mScale = b.mScale;
        mRotation = b.mRotation;
        mTranslate = b.mTranslate;
        return *this;
    }
};

extern J3DTransformInfo const j3dDefaultTransformInfo;
extern Vec const j3dDefaultScale;
extern Mtx const j3dDefaultMtx;
extern f32 const PSMulUnit01[];

void J3DGQRSetup7(u32 param_0, u32 param_1, u32 param_2, u32 param_3);
void J3DCalcBBoardMtx(f32 (*)[4]);
void J3DCalcYBBoardMtx(f32 (*)[4]);
void J3DPSCalcInverseTranspose(f32 (*param_0)[4], f32 (*param_1)[3]);
void J3DGetTranslateRotateMtx(const J3DTransformInfo&, Mtx);
void J3DGetTranslateRotateMtx(s16, s16, s16, f32, f32, f32, Mtx);
void J3DGetTextureMtx(const J3DTextureSRTInfo&, const Vec&, f32 (*)[4]);
void J3DGetTextureMtxOld(const J3DTextureSRTInfo&, const Vec&, f32 (*)[4]);
void J3DGetTextureMtxMaya(const J3DTextureSRTInfo&, f32 (*)[4]);
void J3DGetTextureMtxMayaOld(const J3DTextureSRTInfo& param_0, f32 (*)[4]);
void J3DScaleNrmMtx(f32 (*)[4], const Vec&);
void J3DScaleNrmMtx33(f32 (*)[3], const Vec&);
void J3DMtxProjConcat(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void J3DPSMtxArrayConcat(f32 (*)[4], f32 (*)[4], f32 (*)[4], u32);

inline void J3DPSMtx33Copy(Mtx3P src, Mtx3P dst) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

inline void J3DPSMtx33CopyFrom34(MtxP src, Mtx3P dst) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

inline void J3DPSMulMtxVec(MtxP mtx, Vec* vec, Vec* dst) {
    dst->x = mtx[0][0] * vec->x + mtx[0][1] * vec->y + mtx[0][2] * vec->z + mtx[0][3];
    dst->y = mtx[1][0] * vec->x + mtx[1][1] * vec->y + mtx[1][2] * vec->z + mtx[1][3];
    dst->z = mtx[2][0] * vec->x + mtx[2][1] * vec->y + mtx[2][2] * vec->z + mtx[2][3];
}

inline void J3DPSMulMtxVec(MtxP mtx, S16Vec* vec, S16Vec* dst) {
    dst->x = mtx[0][0] * vec->x + mtx[0][1] * vec->y + mtx[0][2] * vec->z + mtx[0][3];
    dst->y = mtx[1][0] * vec->x + mtx[1][1] * vec->y + mtx[1][2] * vec->z + mtx[1][3];
    dst->z = mtx[2][0] * vec->x + mtx[2][1] * vec->y + mtx[2][2] * vec->z + mtx[2][3];
}

inline void J3DPSMulMtxVec(Mtx3P mtx, Vec* vec, Vec* dst) {
    dst->x = mtx[0][0] * vec->x + mtx[0][1] * vec->y + mtx[0][2] * vec->z;
    dst->y = mtx[1][0] * vec->x + mtx[1][1] * vec->y + mtx[1][2] * vec->z;
    dst->z = mtx[2][0] * vec->x + mtx[2][1] * vec->y + mtx[2][2] * vec->z;
}

inline void J3DPSMulMtxVec(Mtx3P mtx, S16Vec* vec, S16Vec* dst) {
    dst->x = mtx[0][0] * vec->x + mtx[0][1] * vec->y + mtx[0][2] * vec->z;
    dst->y = mtx[1][0] * vec->x + mtx[1][1] * vec->y + mtx[1][2] * vec->z;
    dst->z = mtx[2][0] * vec->x + mtx[2][1] * vec->y + mtx[2][2] * vec->z;
}

#endif
