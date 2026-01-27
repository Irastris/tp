#include "SSystem/SComponent/c_tree.h"
#include "SSystem/SComponent/c_list.h"

void cTr_Create(node_lists_tree_class* tree, node_list_class* lists, int numLists) {
    tree->mpLists = lists;
    tree->mNumLists = numLists;

    while (numLists-- > 0)
        cLs_Create(lists++);
}