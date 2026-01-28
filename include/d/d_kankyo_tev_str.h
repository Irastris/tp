#ifndef D_D_KANKYO_TEV_STR
#define D_D_KANKYO_TEV_STR

// #include "JSystem/J3DGraphBase/J3DTevs.h"
#include "SSystem/SComponent/c_xyz.h"
#include <dolphin/types.h>

class dKy_tevstr_c {
public:
    /* J3DLightObj mLightObj;
    J3DLightObj mLights[6]; */
    cXyz field_0x32c;
    cXyz mLightPosWorld;
    f32 field_0x344;
    GXColorS10 AmbCol;
    GXColorS10 FogCol;
    GXColorS10 TevColor;
    GXColor TevKColor;
    GXColor mLightInf;
    f32 mFogStartZ;
    f32 mFogEndZ;
    f32 pat_ratio;
    f32 field_0x374;
    u16 Material_id;
    u8 Type;
    u8 mInitTimer;
    u8 UseCol;
    u8 PrevCol;
    u8 wether_pat1;
    u8 wether_pat0;
    s8 room_no;
    u8 YukaCol;
    u8 mLightMode;
    u8 Material_use_fg;
    u8 field_0x384;
    u8 field_0x385;
};

#endif
