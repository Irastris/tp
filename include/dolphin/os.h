#ifndef _DOLPHIN_OS_H_
#define _DOLPHIN_OS_H_

#include <cstdio>

#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OSRoundUp32B(x)   (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

inline s16 __OSf32tos16(f32 inF) {
    if (inF >= 32767.0f) {
        return 32767;
    }

    if (inF <= -32768.0f) {
        return -32768;
    }

    return static_cast<s16>(inF);
}

inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}

inline u8 __OSf32tou8(f32 inF) {
    if (inF >= 255.0f) {
        return 255;
    }

    if (inF <= 0.0f) {
        return 0;
    }

    return static_cast<u8>(inF);
}

inline void OSf32tou8(f32* f, u8* out) {
    *out = __OSf32tou8(*f);
}

#ifdef __cplusplus
}
#endif

#endif
