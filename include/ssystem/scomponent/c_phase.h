#ifndef C_PHASE_H
#define C_PHASE_H

#include <dolphin/types.h>

typedef int (*cPhs__Handler)(void*);

enum cPhs__Step {
    cPhs_INIT_e,
    cPhs_LOADING_e,
    cPhs_NEXT_e,
    cPhs_UNK3_e,  // appears to be an alternate error code, unsure how it differs
    cPhs_COMPLEATE_e,
    cPhs_ERROR_e,
};

typedef struct request_of_phase_process_class {
    cPhs__Handler* mpHandlerTable;
    int id;
} request_of_phase_process_class;

typedef int (*request_of_phase_process_fn)(void*);

void cPhs_Reset(request_of_phase_process_class* pPhase);
void cPhs_Set(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable);
void cPhs_UnCompleate(request_of_phase_process_class* pPhase);
int cPhs_Compleate(request_of_phase_process_class* pPhase);
int cPhs_Next(request_of_phase_process_class* pPhase);
int cPhs_Do(request_of_phase_process_class* pPhase, void* pUserData);
int cPhs_Handler(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable, void* pUserData);

#endif
