#ifndef F_PC_DELETE_TAG_H_
#define F_PC_DELETE_TAG_H_

#include "SSystem/SComponent/c_tag.h"
#include "global.h"

typedef struct layer_class layer_class;

typedef int (*delete_tag_func)(void*);

typedef struct delete_tag_class {
    create_tag_class base;
    layer_class* layer;
    s16 timer;
} delete_tag_class;

BOOL fpcDtTg_IsEmpty();
void fpcDtTg_ToDeleteQ(delete_tag_class* i_deleteTag);
void fpcDtTg_DeleteQTo(delete_tag_class* i_deleteTag);
int fpcDtTg_Do(delete_tag_class* i_deleteTag, delete_tag_func i_func);
int fpcDtTg_Init(delete_tag_class* i_deleteTag, void* i_data);

extern node_list_class g_fpcDtTg_Queue;

#endif
