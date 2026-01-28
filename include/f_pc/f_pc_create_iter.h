#ifndef F_PC_CREATE_ITER_H_
#define F_PC_CREATE_ITER_H_

#include <dolphin/types.h>

typedef struct create_tag create_tag;

typedef int (*fpcCtIt_MethodFunc)(void*, void*);
typedef void* (*fpcCtIt_JudgeFunc)(void*, void*);

typedef struct node_method_data {
    fpcCtIt_MethodFunc method;
    void* data;
} node_method_data;

typedef struct node_judge_data {
    fpcCtIt_JudgeFunc method;
    void* data;
} node_judge_data;

typedef struct fpcCtIt_jilprm_c {
    unsigned int layer_id;
    fpcCtIt_JudgeFunc method;
    void* data;
} fpcCtIt_jilprm_c;

int fpcCtIt_Method(fpcCtIt_MethodFunc i_method, void* i_data);
void* fpcCtIt_Judge(fpcCtIt_JudgeFunc i_judge, void* i_data);
void* fpcCtIt_filter_JudgeInLayer(create_tag* i_createTag, fpcCtIt_jilprm_c* i_iterData);
void* fpcCtIt_JudgeInLayer(unsigned int i_layerID, fpcCtIt_JudgeFunc i_method, void* i_data);

#endif
