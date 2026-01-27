#ifndef F_PC_METHOD_H_
#define F_PC_METHOD_H_

#include "dolphin/types.h"

typedef int (*process_method_func)(void*);

typedef struct process_method_class {
    process_method_func create_method;
    process_method_func delete_method;
    process_method_func execute_method;
    process_method_func is_delete_method;
} process_method_class;

int fpcMtd_Method(process_method_func i_method, void* i_process);
int fpcMtd_Execute(process_method_class* i_methods, void* i_process);
int fpcMtd_IsDelete(process_method_class* i_methods, void* i_process);
int fpcMtd_Delete(process_method_class* i_methods, void* i_process);
int fpcMtd_Create(process_method_class* i_methods, void* i_process);

#endif
