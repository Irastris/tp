#include <iostream>
#include "global.h"
#include "JSystem/JKernel/JKRExpHeap.h"

JKRExpHeap* mDoExt_createCommandHeap(u32 heapSize, JKRHeap* parentHeap);
JKRExpHeap* mDoExt_createArchiveHeap(u32 heapSize, JKRHeap* parentHeap);
JKRExpHeap* mDoExt_createJ2dHeap(u32 heapSize, JKRHeap* parentHeap);
JKRExpHeap* mDoExt_createGameHeap(u32 heapSize, JKRHeap* parentHeap);
JKRExpHeap* mDoExt_createZeldaHeap(u32 heapSize, JKRHeap* parentHeap);

void mDoExt_destroyExpHeap(JKRExpHeap* i_heap);

JKRExpHeap* mDoExt_getCommandHeap();
JKRExpHeap* mDoExt_getArchiveHeap();
JKRExpHeap* mDoExt_getJ2dHeap();
JKRExpHeap* mDoExt_getGameHeap();
JKRExpHeap* mDoExt_getZeldaHeap();
