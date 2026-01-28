inline s16 __OSf32tos16(__REGISTER f32 inF) {
    __REGISTER s16 out;
    u32 tmp;
    __REGISTER u32* tmpPtr = &tmp;
    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_st inF, 0(tmpPtr), 0x1, 5
        lha out, 0(tmpPtr)
    }
#endif
    // clang-format on

    return out;
}

inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}

inline u8 __OSf32tou8(__REGISTER f32 inF) {
    __REGISTER u8 out;
    u32 tmp;
    __REGISTER u32* tmpPtr = &tmp;
    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_st inF, 0(tmpPtr), 0x1, 2
        lbz out, 0(tmpPtr)
    }
#endif
    // clang-format on

    return out;
}

inline void OSf32tou8(f32* f, u8* out) {
    *out = __OSf32tou8(*f);
}