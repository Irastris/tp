#ifndef C_LIST_H
#define C_LIST_H

#include <dolphin/types.h>
#include "ssystem/scomponent/c_node.h"

typedef struct node_list_class {
    node_class* mpHead;
    node_class* mpTail;
    int mSize;
} node_list_class;

#endif
