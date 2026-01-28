#ifndef F_PC_LEAF_H_
#define F_PC_LEAF_H_

#include "f_pc/f_pc_base.h"
#include "f_pc/f_pc_draw_priority.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_profile.h"
// #include "d/d_procname.h"

typedef struct leafdraw_method_class {
    process_method_class base;
    process_method_func draw_method;
} leafdraw_method_class;

typedef struct leafdraw_class {
    base_process_class base;
    leafdraw_method_class* leaf_methods;
    s8 unk_0xBC;
    u8 unk_0xBD;
    draw_priority_class draw_priority;
} leafdraw_class;

typedef struct leaf_process_profile_definition {
    process_profile_definition base;
    leafdraw_method_class* sub_method; // Subclass methods
    s16 priority; // mDrawPriority
} leaf_process_profile_definition;

s16 fpcLf_GetPriority(const leafdraw_class* i_leaf);
int fpcLf_DrawMethod(leafdraw_method_class* i_method, void* i_process);
int fpcLf_Draw(leafdraw_class* i_method);
int fpcLf_Execute(leafdraw_class* i_leaf);
int fpcLf_IsDelete(leafdraw_class* i_leaf);
int fpcLf_Delete(leafdraw_class* i_leaf);
int fpcLf_Create(leafdraw_class* i_leaf);

extern int g_fpcLf_type;
extern leafdraw_method_class g_fpcLf_Method;

#endif
