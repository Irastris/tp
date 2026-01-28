#include "JSystem/JSystem.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "JSystem/JMath/JMath.h"

// TODO: Deduplicate instances of this
typedef f32 Mtx33[3][3];

void __MTGQR7(u32 v) {
	// No-op
}

void J3DGQRSetup7(u32 r0, u32 r1, u32 r2, u32 r3) {
    u32 v = ((r0 << 8) + r1) << 16;
	v |= (r2 << 8) + r3;
    __MTGQR7(v);
}

void J3DCalcBBoardMtx(Mtx mtx) {
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

void J3DPSCalcInverseTranspose(Mtx src, Mtx33 dst) {
    f32 a = src[0][0], b = src[0][1], c = src[0][2];
    f32 d = src[1][0], e = src[1][1], f = src[1][2];
    f32 g = src[2][0], h = src[2][1], i = src[2][2];

    f32 c00 = e * i - f * h;
    f32 c01 = f * g - d * i;
    f32 c02 = d * h - e * g;
    f32 c10 = c * h - b * i;
    f32 c11 = a * i - c * g;
    f32 c12 = b * g - a * h;
    f32 c20 = b * f - c * e;
    f32 c21 = c * d - a * f;
    f32 c22 = a * e - b * d;

    f32 det = a * c00 + b * c01 + c * c02;

    if (det == 0.0f) {
        return;
    }

    f32 invDet = 1.0f / det;

    dst[0][0] = c00 * invDet;
    dst[0][1] = c01 * invDet;
    dst[0][2] = c02 * invDet;
    dst[1][0] = c10 * invDet;
    dst[1][1] = c11 * invDet;
    dst[1][2] = c12 * invDet;
    dst[2][0] = c20 * invDet;
    dst[2][1] = c21 * invDet;
    dst[2][2] = c22 * invDet;
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

void J3DScaleNrmMtx(Mtx mtx, const Vec& scl) {
    for (int i = 0; i < 3; i++) {
        mtx[i][0] *= scl.x;
        mtx[i][1] *= scl.y;
        mtx[i][2] *= scl.z;
    }
}

void J3DScaleNrmMtx33(Mtx33 mtx, const Vec& scale) {
    for (int i = 0; i < 3; i++) {
        mtx[i][0] *= scale.x;
        mtx[i][1] *= scale.y;
        mtx[i][2] *= scale.z;
    }
}

void J3DMtxProjConcat(Mtx mtx1, Mtx mtx2, Mtx dst) {
    f32* m2 = &mtx2[0][0];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            dst[i][j] = mtx1[i][0] * m2[0 * 4 + j] +
                        mtx1[i][1] * m2[1 * 4 + j] +
                        mtx1[i][2] * m2[2 * 4 + j] +
                        mtx1[i][3] * m2[3 * 4 + j];
        }
    }
}

static f32 Unit01[2] = {
    0.0f, 1.0f
};

void J3DPSMtxArrayConcat(Mtx mA, Mtx mB, Mtx mAB, u32 count) {
	std::cout << "J3DPSMtxArrayConcat() is stubbed and might be substitutable with PSMtxConcat" << std::endl;
}

f32 const PSMulUnit01[] = {
    0.0f,
    -1.0f,
};
