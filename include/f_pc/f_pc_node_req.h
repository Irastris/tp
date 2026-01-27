#ifndef F_PC_NODE_REQ_H_
#define F_PC_NODE_REQ_H_

#include "SSystem/SComponent/c_phase.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_method_tag.h"
#include "f_pc/f_pc_base.h"

typedef struct layer_class layer_class;
typedef struct process_node_class process_node_class;

typedef struct node_create_request_method_class {
    process_method_func execute_method;
    process_method_func cancel_method;
    process_method_func delete_method;
    process_method_func post_method;
} node_create_request_method_class;

typedef struct unk_process_node_class {
    process_node_class* node;
    fpc_ProcID id;
} unk_process_node_class;

typedef struct node_create_request {
    create_tag_class create_tag;
    process_method_tag_class method_tag;
    request_of_phase_process_class phase_request;
    cPhs__Handler* phase_handler;
    node_create_request_method_class* create_req_methods;
    s32 parameters;
    fpc_ProcID request_id;
    unk_process_node_class node_proc;
    layer_class* layer;
    fpc_ProcID creating_id;
    s16 name;
    void* data;
    s16 unk_0x60;
} node_create_request;

typedef struct request_node_class {
    node_class node;
    node_create_request* node_create_req;
} request_node_class;

void fpcNdRq_RequestQTo(node_create_request* i_request);
void fpcNdRq_ToRequestQ(node_create_request* i_request);
int fpcNdRq_phase_IsCreated(node_create_request* i_request);
int fpcNdRq_phase_Create(node_create_request* i_request);
int fpcNdRq_phase_IsDeleteTiming(node_create_request* i_request);
int fpcNdRq_phase_IsDeleted(node_create_request* i_request);
int fpcNdRq_phase_Delete(node_create_request* i_request);
int fpcNdRq_DoPhase(node_create_request* i_request);
int fpcNdRq_Execute(node_create_request* i_request);
int fpcNdRq_Delete(node_create_request* i_request);
int fpcNdRq_Cancel(node_create_request* i_request);
int fpcNdRq_Handler();
int fpcNdRq_IsPossibleTarget(process_node_class* i_procNode);
int fpcNdRq_IsIng(process_node_class* i_procNode);
node_create_request* fpcNdRq_Create(u32 i_requestSize);
node_create_request* fpcNdRq_ChangeNode(u32 i_requestSize, process_node_class* i_procNode, s16 i_procName, void* i_data);
node_create_request* fpcNdRq_DeleteNode(u32 i_requestSize, process_node_class* i_procNode);
node_create_request* fpcNdRq_CreateNode(u32 i_requestSize, s16 i_procName, void* i_data);
node_create_request*
fpcNdRq_Request(u32 i_requestSize, int i_reqType, process_node_class* i_procNode, s16 i_procName, void* i_data, node_create_request_method_class* i_create_req_methods);
int fpcNdRq_ReChangeNode(fpc_ProcID i_requestID, s16 i_procName, void* i_data);
int fpcNdRq_ReRequest(fpc_ProcID i_requestID, s16 i_procName, void* i_data);

#endif
