#ifndef F_PC_FSTCREATE_REQ_H_
#define F_PC_FSTCREATE_REQ_H_

#include "f_pc/f_pc_create_req.h"

typedef struct base_process_class base_process_class;
typedef struct layer_class layer_class;

typedef int (*fstCreateFunc)(void*, void*);

typedef struct fast_create_request {
    create_request base;
    fstCreateFunc create_func;
    void* data;
} fast_create_request;

int fpcFCtRq_Do(fast_create_request* i_createReq);
int fpcFCtRq_Delete(fast_create_request* i_createReq);
base_process_class* fpcFCtRq_Request(layer_class* i_layer, s16 i_procname, fstCreateFunc i_createFunc, void* i_createData, void* i_append);

#endif
