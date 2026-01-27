#ifndef F_PC_BASE_H_
#define F_PC_BASE_H_

#include "f_pc/f_pc_delete_tag.h"
#include "f_pc/f_pc_layer_tag.h"
#include "f_pc/f_pc_line_tag.h"
#include "f_pc/f_pc_priority.h"

typedef unsigned int fpc_ProcID;

typedef struct create_request create_request;
typedef struct process_method_class process_method_class; 
typedef struct process_profile_definition process_profile_definition;
typedef struct profile_method_class profile_method_class;

typedef struct state_class {
    s8 init_state;  // maybe inaccurate name
    u8 create_phase;
} state_class;

typedef struct base_process_class {
    int type;
    fpc_ProcID id;
    s16 name;
    s8 unk_0xA;
    u8 pause_flag;
    state_class state;
    s16 profname;
    process_profile_definition* profile;
    struct create_request* create_req;
    layer_management_tag_class layer_tag;
    line_tag line_tag_;
    delete_tag_class delete_tag;
    process_priority_class priority;
    process_method_class* methods;
    void* append;
    u32 parameters;
    int subtype;
} base_process_class;

BOOL fpcBs_Is_JustOfType(int i_typeA, int i_typeB);
int fpcBs_MakeOfType(int* i_type);
int fpcBs_MakeOfId();
int fpcBs_Execute(base_process_class* i_proc);
void fpcBs_DeleteAppend(base_process_class* i_proc);
int fpcBs_IsDelete(base_process_class* i_proc);
int fpcBs_Delete(base_process_class* i_proc);
base_process_class* fpcBs_Create(s16 i_profname, fpc_ProcID i_procID, void* i_append);
int fpcBs_SubCreate(base_process_class* i_proc);

extern int g_fpcBs_type;

#endif
