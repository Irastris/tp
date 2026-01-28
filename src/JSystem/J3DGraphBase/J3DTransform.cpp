#include "JSystem/JSystem.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "JSystem/JMath/JMath.h"

void __MTGQR7(__REGISTER u32 v) {
#ifdef __MWERKS__
	asm {
	    mtspr GQR7, v
    }
#endif
}

void J3DGQRSetup7(u32 r0, u32 r1, u32 r2, u32 r3) {
    u32 v = ((r0 << 8) + r1) << 16;
	v |= (r2 << 8) + r3;
    __MTGQR7(v);
}

void J3DCalcBBoardMtx(__REGISTER Mtx mtx) {
    f32 x = (mtx[0][0] * mtx[0][0]) + (mtx[1][0] * mtx[1][0]) + (mtx[2][0] * mtx[2][0]);
    f32 y = (mtx[0][1] * mtx[0][1]) + (mtx[1][1] * mtx[1][1]) + (mtx[2][1] * mtx[2][1]);
    f32 z = (mtx[0][2] * mtx[0][2]) + (mtx[1][2] * mtx[1][2]) + (mtx[2][2] * mtx[2][2]);

    if (x > 0.0f) {
        x = sqrtf(x);
    }
    if (y > 0.0f) {
        y = sqrtf(y);
    }
    if (z > 0.0f) {
        z = sqrtf(z);
    }

	mtx[0][1] = 0.0f;
	mtx[0][2] = 0.0f;
	mtx[2][0] = 0.0f;
	mtx[2][1] = 0.0f;

    mtx[0][0] = x;
	mtx[1][0] = 0.0f;
	mtx[1][1] = y;
	mtx[1][2] = 0.0f;
	mtx[2][2] = z;
}

J3DTransformInfo const j3dDefaultTransformInfo = {
    {1.0f, 1.0f, 1.0f}, {0, 0, 0}, {0.0f, 0.0f, 0.0f}};

Vec const j3dDefaultScale = {1.0f, 1.0f, 1.0f};

Mtx const j3dDefaultMtx = {
    {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}};

void J3DCalcYBBoardMtx(Mtx mtx) {
    f32 x = (mtx[0][0] * mtx[0][0]) + (mtx[1][0] * mtx[1][0]) + (mtx[2][0] * mtx[2][0]);
    f32 z = (mtx[0][2] * mtx[0][2]) + (mtx[1][2] * mtx[1][2]) + (mtx[2][2] * mtx[2][2]);

	if (x > 0.0f) {
		x = JMath::fastSqrt(x);
	}
	if (z > 0.0f) {
		z = JMath::fastSqrt(z);
	}

	Vec vec = { 0.0f, -mtx[2][1], mtx[1][1] };
	VECNormalize(&vec, &vec);

	mtx[0][0] = x;
	mtx[0][2] = 0.0f;
	mtx[1][0] = 0.0f;

	mtx[1][2] = vec.y * z;
	mtx[2][0] = 0.0f;
	mtx[2][2] = vec.z * z;
}

ASM void J3DPSCalcInverseTranspose(__REGISTER Mtx src, __REGISTER Mtx33 dst) {
#ifdef __MWERKS__
	psq_l    f0, 0(src), 1, 0
	psq_l    f1, 4(src), 0, 0
	psq_l    f2, 16(src), 1, 0
	ps_merge10 f6, f1, f0
	psq_l    f3, 20(src), 0, 0
	psq_l    f4, 32(src), 1, 0
	ps_merge10 f7, f3, f2
	psq_l    f5, 36(src), 0, 0
	ps_mul   f11, f3, f6
	ps_merge10 f8, f5, f4
	ps_mul   f13, f5, f7
	ps_msub  f11, f1, f7, f11
	ps_mul   f12, f1, f8
	ps_msub  f13, f3, f8, f13
	ps_msub  f12, f5, f6, f12
	ps_mul   f10, f3, f4
	ps_mul   f9, f0, f5
	ps_mul   f8, f1, f2
	ps_msub  f10, f2, f5, f10
	ps_msub  f9, f1, f4, f9
	ps_msub  f8, f0, f3, f8
	ps_mul   f7, f0, f13
	ps_sub   f1, f1, f1
	ps_madd  f7, f2, f12, f7
	ps_madd  f7, f4, f11, f7
	ps_cmpo0 cr0, f7, f1
	bne      lbl_8005F118
	li       r3, 0
	blr

lbl_8005F118:
	fres     f0, f7
	ps_add   f6, f0, f0
	ps_mul   f5, f0, f0
	ps_nmsub f0, f7, f5, f6
	ps_add   f6, f0, f0
	ps_mul   f5, f0, f0
	ps_nmsub f0, f7, f5, f6
	ps_muls0 f13, f13, f0
	ps_muls0 f12, f12, f0
	psq_st   f13, 0(dst), 0, 0
	ps_muls0 f11, f11, f0
	psq_st   f12, 12(dst), 0, 0
	ps_muls0 f10, f10, f0
	psq_st   f11, 24(dst), 0, 0
	ps_muls0 f9, f9, f0
	psq_st   f10, 8(dst), 1, 0
	ps_muls0 f8, f8, f0
	psq_st   f9, 20(r4), 1, 0
	li       r3, 1
	psq_st   f8, 32(r4), 1, 0
	blr
#endif
}

void J3DGetTranslateRotateMtx(const J3DTransformInfo& tx, Mtx dst) {
	f32 cxsz;
	f32 sxcz;

    f32 sx = JMASSin(tx.mRotation.x), cx = JMASCos(tx.mRotation.x);
    f32 sy = JMASSin(tx.mRotation.y), cy = JMASCos(tx.mRotation.y);
    f32 sz = JMASSin(tx.mRotation.z), cz = JMASCos(tx.mRotation.z);

    dst[2][0] = -sy;
    dst[0][0] = cz * cy;
    dst[1][0] = sz * cy;
    dst[2][1] = cy * sx;
    dst[2][2] = cy * cx;

    cxsz = cx * sz;
    sxcz = sx * cz;
    dst[0][1] = sxcz * sy - cxsz;
    dst[1][2] = cxsz * sy - sxcz;

    cxsz = sx * sz;
    sxcz = cx * cz;
    dst[0][2] = sxcz * sy + cxsz;
    dst[1][1] = cxsz * sy + sxcz;

    dst[0][3] = tx.mTranslate.x;
    dst[1][3] = tx.mTranslate.y;
    dst[2][3] = tx.mTranslate.z;
}

void J3DGetTranslateRotateMtx(s16 rx, s16 ry, s16 rz, f32 tx, f32 ty, f32 tz, Mtx dst) {
	f32 cxsz;
	f32 sxcz;

    f32 sx = JMASSin(rx), cx = JMASCos(rx);
    f32 sy = JMASSin(ry), cy = JMASCos(ry);
    f32 sz = JMASSin(rz), cz = JMASCos(rz);

    dst[2][0] = -sy;
    dst[0][0] = cz * cy;
    dst[1][0] = sz * cy;
    dst[2][1] = cy * sx;
    dst[2][2] = cy * cx;

    cxsz = cx * sz;
    sxcz = sx * cz;
    dst[0][1] = sxcz * sy - cxsz;
    dst[1][2] = cxsz * sy - sxcz;

    cxsz = sx * sz;
    sxcz = cx * cz;
    dst[0][2] = sxcz * sy + cxsz;
    dst[1][1] = cxsz * sy + sxcz;

    dst[0][3] = tx;
    dst[1][3] = ty;
    dst[2][3] = tz;
}

void J3DGetTextureMtx(const J3DTextureSRTInfo& srt, const Vec& center, Mtx dst) {
    f32 sr = JMASSin(srt.mRotation), cr = JMASCos(srt.mRotation);

    f32 cx = srt.mScaleX * cr;
    f32 sx = srt.mScaleX * sr;
    f32 sy = srt.mScaleY * sr;
    f32 cy = srt.mScaleY * cr;

    dst[0][0] = cx;
    dst[0][1] = -sx;
    dst[0][2] = (-cx * center.x + sx * center.y) + center.x + srt.mTranslationX;

    dst[1][0] = sy;
    dst[1][1] = cy;
    dst[1][2] = (-sy * center.x - cy * center.y) + center.y + srt.mTranslationY;

    dst[0][3] = dst[1][3] = dst[2][0] = dst[2][1] = dst[2][3] = 0.0f;
	dst[2][2] = 1.0f;
}

void J3DGetTextureMtxOld(const J3DTextureSRTInfo& srt, const Vec& center, Mtx dst) {
    f32 sr = JMASSin(srt.mRotation), cr = JMASCos(srt.mRotation);

    f32 cx = srt.mScaleX * cr;
    f32 sx = srt.mScaleX * sr;
    f32 sy = srt.mScaleY * sr;
    f32 cy = srt.mScaleY * cr;

    dst[0][0] = cx;
    dst[0][1] = -sx;
    dst[0][3] = (-cx * center.x + sx * center.y) + center.x + srt.mTranslationX;

    dst[1][0] = sy;
    dst[1][1] = cy;
    dst[1][3] = (-sy * center.x - cy * center.y) + center.y + srt.mTranslationY;

    dst[0][2] = dst[1][2] = dst[2][0] = dst[2][1] = dst[2][3] = 0.0f;
	dst[2][2] = 1.0f;
}

void J3DGetTextureMtxMaya(const J3DTextureSRTInfo& srt, Mtx dst) {
    f32 sr = JMASSin(srt.mRotation), cr = JMASCos(srt.mRotation);
    f32 tx = srt.mTranslationX - 0.5f;
    f32 ty = srt.mTranslationY - 0.5f;

    dst[0][0] = srt.mScaleX * cr;
    dst[0][1] = srt.mScaleY * sr;
    dst[0][2] = tx * cr - sr * (ty + srt.mScaleY) + 0.5f;

    dst[1][0] = -srt.mScaleX * sr;
    dst[1][1] = srt.mScaleY * cr;
    dst[1][2] = -tx * sr - cr * (ty + srt.mScaleY) + 0.5f;

	dst[0][3] = dst[1][3] = dst[2][0] = dst[2][1] = dst[2][3] = 0.0f;
	dst[2][2] = 1.0f;
}

void J3DGetTextureMtxMayaOld(const J3DTextureSRTInfo& srt, Mtx dst) {
    f32 sr = JMASSin(srt.mRotation), cr = JMASCos(srt.mRotation);
    f32 tx = srt.mTranslationX - 0.5f;
    f32 ty = srt.mTranslationY - 0.5f;

    dst[0][0] = srt.mScaleX * cr;
    dst[0][1] = srt.mScaleY * sr;
    dst[0][3] = tx * cr - sr * (ty + srt.mScaleY) + 0.5f;

    dst[1][0] = -srt.mScaleX * sr;
    dst[1][1] = srt.mScaleY * cr;
    dst[1][3] = -tx * sr - cr * (ty + srt.mScaleY) + 0.5f;

	dst[0][2] = dst[1][2] = dst[2][0] = dst[2][1] = dst[2][3] = 0.0f;
	dst[2][2] = 1.0f;
}

ASM void J3DScaleNrmMtx(__REGISTER Mtx mtx, const __REGISTER Vec& scl) {
#ifdef __MWERKS__
	nofralloc;

	psq_l  fp2, 0(scl), 0, 0
	psq_l  fp0, 0(mtx), 0, 0
	lfs    fp3, 8(scl)
	lfs    fp1, 8(mtx)
	ps_mul f4, fp0, fp2
	psq_st f4, 0(mtx), 0, 0
	fmuls  f4, fp1, fp3
	stfs   f4, 8(mtx)

	/* Row 1 */
	psq_l  fp2, 0(scl), 0, 0
	psq_l  fp0, 16(mtx), 0, 0
	lfs    fp3, 8(scl)
	lfs    fp1, 24(mtx)
	ps_mul f4, fp0, fp2
	psq_st f4, 16(mtx), 0, 0
	fmuls  f4, fp1, fp3
	stfs   f4, 24(mtx)

	/* Row 2 */
	psq_l  fp2, 0(scl), 0, 0
	psq_l  fp0, 32(mtx), 0, 0
	lfs    fp3, 8(scl)
	lfs    fp1, 40(mtx)
	ps_mul f4, fp0, fp2
	psq_st f4, 32(mtx), 0, 0
	fmuls  f4, fp1, fp3
	stfs   f4, 40(mtx)
	blr
#endif
}

ASM void J3DScaleNrmMtx33(__REGISTER Mtx33 mtx, const __REGISTER Vec& scale) {
#ifdef __MWERKS__
	psq_l    f0, 0(mtx), 0, 0
	psq_l    f6, 0(scale), 0, 0
	lfs      f1, 8(mtx)
	lfs      f7, 8(scale)
	ps_mul   f0, f0, f6
	psq_l    f2, 12(mtx), 0, 0
	fmuls    f1, f1, f7
	lfs      f3, 0x14(mtx)
	ps_mul   f2, f2, f6
	psq_l    f4, 24(mtx), 0, 0
	fmuls    f3, f3, f7
	lfs      f5, 0x20(mtx)
	ps_mul   f4, f4, f6
	psq_st   f0, 0(mtx), 0, 0
	fmuls    f5, f5, f7
	stfs     f1, 8(mtx)
	psq_st   f2, 12(mtx), 0, 0
	stfs     f3, 0x14(mtx)
	psq_st   f4, 24(mtx), 0, 0
	stfs     f5, 0x20(mtx)
	blr
#endif
}

ASM void J3DMtxProjConcat(__REGISTER Mtx mtx1, __REGISTER Mtx mtx2, __REGISTER Mtx dst) {
#ifdef __MWERKS__
	psq_l    f2, 0(mtx1), 0, 0
	psq_l    f3, 8(mtx1), 0, 0
	ps_merge00 f6, f2, f2
	ps_merge11 f7, f2, f2
	ps_merge00 f8, f3, f3
	ps_merge11 f9, f3, f3
	psq_l    f10, 0(mtx2), 0, 0
	psq_l    f11, 16(mtx2), 0, 0
	psq_l    f12, 32(mtx2), 0, 0
	psq_l    f13, 48(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 0(dst), 0, 0
	psq_l    f10, 8(mtx2), 0, 0
	psq_l    f11, 24(mtx2), 0, 0
	psq_l    f12, 40(mtx2), 0, 0
	psq_l    f13, 56(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 8(dst), 0, 0
	psq_l    f2, 16(mtx1), 0, 0
	psq_l    f3, 24(mtx1), 0, 0
	ps_merge00 f6, f2, f2
	ps_merge11 f7, f2, f2
	ps_merge00 f8, f3, f3
	ps_merge11 f9, f3, f3
	psq_l    f10, 0(mtx2), 0, 0
	psq_l    f11, 16(mtx2), 0, 0
	psq_l    f12, 32(mtx2), 0, 0
	psq_l    f13, 48(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 16(dst), 0, 0
	psq_l    f10, 8(mtx2), 0, 0
	psq_l    f11, 24(mtx2), 0, 0
	psq_l    f12, 40(mtx2), 0, 0
	psq_l    f13, 56(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 24(dst), 0, 0
	psq_l    f2, 32(mtx1), 0, 0
	psq_l    f3, 40(mtx1), 0, 0
	ps_merge00 f6, f2, f2
	ps_merge11 f7, f2, f2
	ps_merge00 f8, f3, f3
	ps_merge11 f9, f3, f3
	psq_l    f10, 0(mtx2), 0, 0
	psq_l    f11, 16(mtx2), 0, 0
	psq_l    f12, 32(mtx2), 0, 0
	psq_l    f13, 48(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 32(dst), 0, 0
	psq_l    f10, 8(mtx2), 0, 0
	psq_l    f11, 24(mtx2), 0, 0
	psq_l    f12, 40(mtx2), 0, 0
	psq_l    f13, 56(mtx2), 0, 0
	ps_mul   f0, f6, f10
	ps_madd  f0, f7, f11, f0
	ps_madd  f0, f8, f12, f0
	ps_madd  f0, f9, f13, f0
	psq_st   f0, 40(dst), 0, 0
	blr
#endif
}

static f32 Unit01[2] = {
    0.0f, 1.0f
};

void J3DPSMtxArrayConcat(Mtx mA, Mtx mB, Mtx mAB, u32 count) {
	std::cout << "J3DPSMtxArrayConcat() is stubbed and should be substituted with PSMtxConcat" << std::endl;
}

f32 const PSMulUnit01[] = {
    0.0f,
    -1.0f,
};
