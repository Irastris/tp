#ifndef C_NODE_H
#define C_NODE_H

typedef struct node_class {
    struct node_class* mpPrevNode;
    void* mpData;
    struct node_class* mpNextNode;
} node_class;

void cNd_Join(node_class* pA, node_class* pB);
node_class* cNd_Last(node_class* pNode);
void cNd_Addition(node_class* pA, node_class* pB);

#define NODE_GET_PREV(pNode) (pNode ? pNode->mpPrevNode : NULL)
#define NODE_GET_NEXT(pNode) (pNode ? pNode->mpNextNode : NULL)

#endif
