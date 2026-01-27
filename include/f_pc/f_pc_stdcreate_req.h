#ifndef F_PC_STDCREATE_H_
#define F_PC_STDCREATE_H_

#include "f_pc/f_pc_create_req.h"

typedef struct layer_class layer_class;

typedef int (*stdCreateFunc)(void*, void*);

typedef struct standard_create_request_class {
    create_request base;
    request_of_phase_process_class phase_request;
    s16 process_name;
    void* process_append;
    stdCreateFunc create_post_method;
    void* unk_0x5C;
} standard_create_request_class;

int fpcSCtRq_phase_CreateProcess(standard_create_request_class* i_request);
int fpcSCtRq_phase_SubCreateProcess(standard_create_request_class* i_request);
int fpcSCtRq_phase_IsComplete(standard_create_request_class* i_request);
int fpcSCtRq_phase_PostMethod(standard_create_request_class* i_request);
int fpcSCtRq_phase_Done(standard_create_request_class* i_request);
int fpcSCtRq_Handler(standard_create_request_class* i_request);
int fpcSCtRq_Delete(standard_create_request_class* i_request);
int fpcSCtRq_Cancel(standard_create_request_class* i_request);
fpc_ProcID fpcSCtRq_Request(layer_class* i_layer, s16 i_procName, stdCreateFunc i_createFunc, void* param_4, void* i_append);

#endif
