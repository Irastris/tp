#include "JSystem/JSystem.h"
#include "JSystem/JMath/JMath.h"
#include "JSystem/JMath/JMATrigonometric.h"

void JMAEulerToQuat(s16 x, s16 y, s16 z, Quaternion* quat) {
    f32 cosX = JMASCos(x / 2);
    f32 cosY = JMASCos(y / 2);
    f32 cosZ = JMASCos(z / 2);
    f32 sinX = JMASSin(x / 2);
    f32 sinY = JMASSin(y / 2);
    f32 sinZ = JMASSin(z / 2);

    f32 cyz = cosY * cosZ;
    f32 syz = sinY * sinZ;
    quat->w = cosX * (cyz) + sinX * (syz);
    quat->x = sinX * (cyz)-cosX * (syz);
    quat->y = cosZ * (cosX * sinY) + sinZ * (sinX * cosY);
    quat->z = sinZ * (cosX * cosY) - cosZ * (sinX * sinY);
}

void JMAQuatLerp(const Quaternion* p, const Quaternion* q, f32 t, Quaternion* dst) {
    f32 dp = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;

    if (dp < 0.0) {
        dst->x = -t * (p->x + q->x) + p->x;
        dst->y = -t * (p->y + q->y) + p->y;
        dst->z = -t * (p->z + q->z) + p->z;
        dst->w = -t * (p->w + q->w) + p->w;
    } else {
        dst->x = -t * (p->x - q->x) + p->x;
        dst->y = -t * (p->y - q->y) + p->y;
        dst->z = -t * (p->z - q->z) + p->z;
        dst->w = -t * (p->w - q->w) + p->w;
    }
}

void JMAFastVECNormalize(const Vec* src, Vec* dst) {
    f32 length = std::sqrt(src->x * src->x + src->y * src->y + src->z * src->z);
    f32 invLength = 1.0f / length;
    dst->x = src->x * invLength;
    dst->y = src->y * invLength;
    dst->z = src->z * invLength;
}

void JMAVECScaleAdd(const Vec* vec1, const Vec* vec2, Vec* dst, f32 scale) {
    dst->x = vec1->x * scale + vec2->x;
    dst->y = vec1->y * scale + vec2->y;
    dst->z = vec1->z * scale + vec2->z;
}

void JMAMTXApplyScale(const Mtx src, Mtx dst, f32 xScale, f32 yScale, f32 zScale) {
    for (int i = 0; i < 3; i++) {
        dst[i][0] = src[i][0] * xScale;
        dst[i][1] = src[i][1] * yScale;
        dst[i][2] = src[i][2] * zScale;
        dst[i][3] = src[i][3];
    }
}
