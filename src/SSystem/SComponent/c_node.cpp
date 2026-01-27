#include "SSystem/SComponent/c_node.h"
#include <dolphin/types.h>

void cNd_Join(node_class* node_a, node_class* node_b) {
    node_a->mpNextNode = node_b;
    node_b->mpPrevNode = node_a;
}

node_class* cNd_Last(node_class* node) {
    node_class* ret = NULL;
    while (node) {
        ret = node;
        node = NODE_GET_NEXT(node);
    }
    return ret;
}

void cNd_Addition(node_class* node_a, node_class* node_b) {
    node_class* pLast = cNd_Last(node_a);
    cNd_Join(pLast, node_b);
}