#include "SSystem/SComponent/c_list.h"
#include "SSystem/SComponent/c_node.h"
#include <dolphin/types.h>

void cLs_Init(node_list_class* list) {
    list->mpHead = NULL;
    list->mpTail = NULL;
    list->mSize = 0;
}

int cLs_Addition(node_list_class* list, node_class* node) {
    if (list->mpTail == NULL) {
        list->mpHead = node;
    } else {
        cNd_Addition(list->mpTail, node);
    }

    list->mpTail = cNd_Last(node);
    cNd_SetObject(node, list);
    list->mSize = cNd_LengthOf(list->mpHead);
    return list->mSize;
}

void cLs_Create(node_list_class* list) {
    cLs_Init(list);
}