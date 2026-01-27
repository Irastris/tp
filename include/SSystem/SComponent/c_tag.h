#ifndef C_TAG_H
#define C_TAG_H

#include "SSystem/SComponent/c_node.h"
#include <dolphin/types.h>

typedef struct create_tag_class {
    node_class mpNode;
    void* mpTagData;
    s8 mbIsUse;
} create_tag_class;

#endif
