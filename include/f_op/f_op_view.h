#ifndef F_F_OP_VIEW_H_
#define F_F_OP_VIEW_H_

#include "SSystem/SComponent/c_xyz.h"
#include <dolphin/mtx.h>
#include "f_pc/f_pc_leaf.h"

struct view_process_profile_definition {
    leaf_process_profile_definition base;
    leafdraw_method_class* sub_method;
    u8 unk_0x28;
    u32 unk_0x2C;
    u32 unk_0x30;
    u32 unk_0x34;
    u32 unk_0x38;
};

class lookat_class {
public:
    cXyz eye;
    cXyz center;
    cXyz up;
};

struct scissor_class {
    f32 x_orig;
    f32 y_orig;
    f32 width;
    f32 height;
};

struct view_port_class {
    f32 x_orig;
    f32 y_orig;
    f32 width;
    f32 height;
    f32 near_z;
    f32 far_z;
    scissor_class scissor;
};

struct view_class {
    leafdraw_class base;
    leafdraw_method_class* sub_method;
    u8 field_0xc4;
    f32 near;
    f32 far;
    f32 fovy;
    f32 aspect;
    lookat_class lookat;
    s16 bank;
    Mtx44 projMtx;
    Mtx viewMtx;
    Mtx invViewMtx;
    Mtx44 projViewMtx;
    Mtx viewMtxNoTrans;
};

extern leafdraw_method_class g_fopVw_Method;

#endif
