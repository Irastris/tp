#ifndef JMATH_H
#define JMATH_H

#include <iostream>

#include "dolphin/mtx.h"
#include <cmath>
#include <cstring>

void JMAMTXApplyScale(const Mtx, Mtx, f32, f32, f32);
void JMAEulerToQuat(s16 param_0, s16 param_1, s16 param_2, Quaternion* param_3);
void JMAQuatLerp(const Quaternion*, const Quaternion*, f32, Quaternion*);
void JMAFastVECNormalize(__REGISTER const Vec* src, __REGISTER Vec* dst);
void JMAVECScaleAdd(__REGISTER const Vec* vec1, __REGISTER const Vec* vec2, __REGISTER Vec* dst, __REGISTER f32 scale);

inline int JMAAbs(int value) {
    return std::abs(value);
}

inline f32 JMAAbs(f32 x) {
    return std::abs(x);
}

inline f32 JMAFastReciprocal(f32 value) {
    return 1.0f / value;
}

inline float __frsqrtes(double f) {
    return 1.0f / std::sqrt(f);
}

inline f32 JMAFastSqrt(const f32 input) {
    if (input > 0.0f) {
        return std::sqrt(input);
    } else {
        return input;
    }
}

inline f32 JMAHermiteInterpolation(f32 p1, f32 p2, f32 p3, f32 p4, f32 p5, f32 p6, f32 p7) {
    f32 ff31 = p1 - p2;
    f32 ff30 = p5 - p2;
    f32 ff29 = ff31 / ff30;
    f32 ff28 = ff29 * ff29;
    f32 ff25 = ff29 + ff29;
    f32 ff27 = ff28 - ff29;
    ff30 = p3 - p6;
    f32 ff26 = ff25 * ff27 - ff28;
    ff25 = p4 * ff27 + p4;
    ff26 = ff26 * ff30 + p3;
    ff25 = p7 * ff27 + ff25;
    ff25 = ff29 * p4 - ff25;
    ff25 = ff26 - ff31 * ff25;

    return ff25;
}

namespace JMath {

template <typename T>
inline T fastSqrt(T value) {
    return JMAFastSqrt(value);
}

inline f32 fastReciprocal(f32 value) {
    return JMAFastReciprocal(value);
}

inline void fastVECNormalize(const Vec* src, Vec* dst) {
    return JMAFastVECNormalize(src, dst);
}

inline void gekko_ps_copy3(void* dst, const void* src) {
    memcpy(dst, src, sizeof(f32) * 3);
}

inline void gekko_ps_copy6(void* dst, const void* src) {
    memcpy(dst, src, sizeof(f32) * 6);
}

inline void gekko_ps_copy12(void* dst, const void* src) {
    memcpy(dst, src, sizeof(f32) * 12);
}

inline void gekko_ps_copy16(void* dst, const void* src) {
    memcpy(dst, src, sizeof(f32) * 16);
}

};  // namespace JMath

namespace JMathInlineVEC {
    inline void C_VECAdd(__REGISTER const Vec* a, __REGISTER const Vec* b, __REGISTER Vec* ab) {
        std::cout << "JMathInlineVec::C_VECAdd() is stubbed and should be substituted with Aurora" << std::endl;
    }

    inline void C_VECSubtract(__REGISTER const Vec* a, __REGISTER const Vec* b, __REGISTER Vec* ab) {
        std::cout << "JMathInlineVec::C_VECSubtract() is stubbed and should be substituted with Aurora" << std::endl;
    }

    inline f32 C_VECSquareMag(__REGISTER const Vec* v) {
        std::cout << "JMathInlineVec::C_VECSquareMag() is stubbed and should be substituted with Aurora" << std::endl;
    }

    inline f32 C_VECDotProduct(__REGISTER const Vec *a, __REGISTER const Vec *b) {
        std::cout << "JMathInlineVec::C_VECDotProduct() is stubbed and should be substituted with Aurora" << std::endl;
    }
};

template<typename T>
inline T JMAMax(T param_0, T param_1) {
    T ret;
    if (param_0 > param_1) {
        ret = param_0;
    } else {
        ret = param_1;
    }
    return ret;
}

#endif
