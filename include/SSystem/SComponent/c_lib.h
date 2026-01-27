#ifndef C_LIB_H_
#define C_LIB_H_

// #include <string>

#include <dolphin/mtx.h>
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_xyz.h"

template <typename T>
inline void cLib_offBit(T& value, T bit) {
    value = (T)(value & ~bit);
}

template <typename T>
inline void cLib_onBit(T& value, T bit) {
    value = (T)(value | bit);
}

template <typename T>
inline T cLib_checkBit(T value, T bit) {
    return (T)(value & bit);
}

#endif
