#ifndef F_PC_PROFILE_H_
#define F_PC_PROFILE_H_

#include "dolphin/types.h"

typedef struct nodedraw_method_class nodedraw_method_class;
typedef struct leafdraw_method_class leafdraw_method_class;
typedef struct process_method_class process_method_class;

typedef struct process_profile_definition {
    unsigned int layer_id;
    u16 list_id;
    u16 list_priority;
    s16 name;
    process_method_class* methods;
    u32 process_size;
    u32 unk_size;
    u32 parameters;
} process_profile_definition;

#define LAYER_DEFAULT (-2)

struct leaf_process_profile_definition;
process_profile_definition* fpcPf_Get(s16 i_profname);
extern process_profile_definition** g_fpcPf_ProfileList_p;

#endif
