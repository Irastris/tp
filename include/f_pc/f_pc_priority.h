#ifndef F_PC_PRIORITY_H_
#define F_PC_PRIORITY_H_

#include "f_pc/f_pc_method_tag.h"

enum {
    fpcPi_CURRENT_e = 0xFFFD,
    fpcPi_SPECIAL_e = 0xFFFE,
    fpcPi_NONE_e = 0xFFFF,
};

typedef struct priority_id {
    unsigned int layer_id;
    u16 list_id;
    u16 list_priority;
} priority_id;

typedef struct process_priority_class {
    create_tag_class base;
    process_method_tag_class method_tag;
    priority_id queue_info;
    priority_id current_info;
} process_priority_class;

int fpcPi_IsInQueue(process_priority_class* pPi);
int fpcPi_QueueTo(process_priority_class* pPi);
int fpcPi_ToQueue(process_priority_class* pPi);
process_priority_class* fpcPi_GetFromQueue(void);
int fpcPi_Delete(process_priority_class* pPi);
int fpcPi_IsNormal(unsigned int layer, u16 listID, u16 priority);
int fpcPi_Change(process_priority_class* pPi, unsigned int layer, u16 listID, u16 priority);
int fpcPi_Handler(void);
int fpcPi_Init(process_priority_class* pPi, void* pUserData, unsigned int layer, u16 listID, u16 priority);

#endif
