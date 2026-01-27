#include "SSystem/SComponent/c_list.h"
#include "f_pc/f_pc_delete_tag.h"

node_list_class g_fpcDtTg_Queue = {NULL, NULL, 0};

BOOL fpcDtTg_IsEmpty() {
    if (g_fpcDtTg_Queue.mSize == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void fpcDtTg_ToDeleteQ(delete_tag_class* i_deleteTag) {
    i_deleteTag->timer = 1;
    cTg_Addition(&g_fpcDtTg_Queue, &i_deleteTag->base);
}

void fpcDtTg_DeleteQTo(delete_tag_class* i_deleteTag) {
    cTg_SingleCut(&i_deleteTag->base);
}

int fpcDtTg_Do(delete_tag_class* i_deleteTag, delete_tag_func i_func) {
    if (i_deleteTag->timer <= 0) {
        fpcDtTg_DeleteQTo(i_deleteTag);

        if (i_func(i_deleteTag->base.mpTagData) == 0) {
            fpcDtTg_ToDeleteQ(i_deleteTag);
            return 0;
        } else {
            return 1;
        }
    } else {
        i_deleteTag->timer--;
        return 0;
    }
}

int fpcDtTg_Init(delete_tag_class* i_deleteTag, void* i_data) {
    cTg_Create(&i_deleteTag->base, i_data);
    return 1;
}
