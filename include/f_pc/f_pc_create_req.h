#ifndef F_PC_CREATE_REQ_H_
#define F_PC_CREATE_REQ_H_

#include "SSystem/SComponent/c_phase.h"
#include "f_pc/f_pc_create_tag.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_method_tag.h"
#include "f_pc/f_pc_base.h"

typedef struct base_process_class base_process_class;
typedef struct layer_class layer_class;

typedef struct create_request_method_class {
    cPhs__Handler phase_handler;
    process_method_func cancel_method;
    process_method_func delete_method;
} create_request_method_class;

typedef struct create_request {
    create_tag base;
    s8 is_doing;
    s8 is_cancel;
    process_method_tag_class method_tag;
    create_request_method_class* methods;
    void* unk_0x38;
    fpc_ProcID id;
    struct base_process_class* process;
    layer_class* layer;
} create_request;

BOOL fpcCtRq_isCreatingByID(create_tag* i_createTag, fpc_ProcID* i_id);
BOOL fpcCtRq_IsCreatingByID(fpc_ProcID i_id);
void fpcCtRq_CreateQTo(create_request* i_request);
void fpcCtRq_ToCreateQ(create_request* i_request);
BOOL fpcCtRq_Delete(create_request* i_request);
BOOL fpcCtRq_Cancel(create_request* i_request);
BOOL fpcCtRq_IsDoing(create_request* i_request);
int fpcCtRq_Handler();
create_request* fpcCtRq_Create(layer_class* i_layer, u32 i_size, create_request_method_class* i_methods);

#endif
