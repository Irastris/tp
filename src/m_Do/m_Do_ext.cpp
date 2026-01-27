#include "game/ext.h"

JKRExpHeap* commandHeap;

JKRExpHeap* mDoExt_createCommandHeap(u32 heapSize, JKRHeap* parentHeap) {
    std::cout << "Hello from mDoExt_createCommandHeap() @ ext.cpp (m_Do_ext)" << std::endl;
    commandHeap = JKRExpHeap::create(heapSize, parentHeap, true);
    return commandHeap;
}

JKRExpHeap* mDoExt_getCommandHeap() {
    return commandHeap;
}

JKRExpHeap* archiveHeap;

JKRExpHeap* mDoExt_createArchiveHeap(u32 heapSize, JKRHeap* parentHeap) {
    std::cout << "Hello from mDoExt_createArchiveHeap() @ ext.cpp (m_Do_ext)" << std::endl;
    archiveHeap = JKRExpHeap::create(heapSize, parentHeap, true);
    archiveHeap->setAllocationMode(JKRExpHeap::ALLOC_MODE_1);
    return archiveHeap;
}

JKRExpHeap* mDoExt_getArchiveHeap() {
    return archiveHeap;
}

static JKRExpHeap* j2dHeap;

JKRExpHeap* mDoExt_createJ2dHeap(u32 heapSize, JKRHeap* parentHeap) {
    std::cout << "Hello from mDoExt_createJ2dHeap() @ ext.cpp (m_Do_ext)" << std::endl;
    j2dHeap = JKRExpHeap::create(heapSize, parentHeap, true);
    j2dHeap->setAllocationMode(JKRExpHeap::ALLOC_MODE_1);
    return j2dHeap;
}

JKRExpHeap* mDoExt_getJ2dHeap() {
    return j2dHeap;
}

JKRExpHeap* gameHeap;

JKRExpHeap* mDoExt_createGameHeap(u32 heapSize, JKRHeap* parentHeap) {
    std::cout << "Hello from mDoExt_createGameHeap() @ ext.cpp (m_Do_ext)" << std::endl;
    gameHeap = JKRExpHeap::create(heapSize, parentHeap, true);
    gameHeap->setAllocationMode(JKRExpHeap::ALLOC_MODE_1);
    return gameHeap;
}

JKRExpHeap* mDoExt_getGameHeap() {
    return gameHeap;
}

JKRExpHeap* zeldaHeap;

JKRExpHeap* mDoExt_createZeldaHeap(u32 heapSize, JKRHeap* parentHeap) {
    std::cout << "Hello from mDoExt_createZeldaHeap() @ ext.cpp (m_Do_ext)" << std::endl;
    zeldaHeap = JKRExpHeap::create(heapSize, parentHeap, true);
    return zeldaHeap;
}

JKRExpHeap* mDoExt_getZeldaHeap() {
    return zeldaHeap;
}

void mDoExt_destroyExpHeap(JKRExpHeap* i_heap) {
    JKRDestroyExpHeap(i_heap);
}
