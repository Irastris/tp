#include "m_Do/m_Do_machine.h"

// TODO: Determine if this custom profile should be used vs. the generic GX profiles
/* GXRenderModeObj g_ntscZeldaProg = {
    VI_TVMODE_NTSC_PROG,
    608,
    448,
    448,
    27,
    16,
    666,
    448,
    VI_XFBMODE_SF,
    0,
    0,
    {{6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6},
     {6, 6}},
    {0, 0, 21, 22, 21, 0, 0},
};

GXRenderModeObj* mDoMch_render_c::mRenderModeObj = &g_ntscZeldaIntDf; */

void mDoMch_Create() {
    std::cout << "Hello from mDoMch_Create() @ m_Do_machine.cpp" << std::endl;

    JFWSystem::init();

    JKRHeap* rootHeap = (JKRHeap*)JKRGetRootHeap();

    mDoExt_createCommandHeap(0x1000, rootHeap); // 4 KB
    mDoExt_createArchiveHeap(0x8DF400, rootHeap); // 9085 KB
    mDoExt_createJ2dHeap(0x7D000, rootHeap); // 500 KB
    mDoExt_createGameHeap(0x44E000, rootHeap); // 4408 KB

    JKRHeap* systemHeap = JKRGetSystemHeap();
    s32 size = systemHeap->getFreeSize();
    size -= 0x10000;
    JKRHeap* zeldaHeap = mDoExt_createZeldaHeap(size, systemHeap);
    JKRSetCurrentHeap(zeldaHeap);

    std::cout << "commandHeap initialized with size " << mDoExt_getCommandHeap()->getSize() << " bytes" << std::endl;
    std::cout << "archiveHeap initialized with size " << mDoExt_getArchiveHeap()->getSize() << " bytes" << std::endl;
    std::cout << "j2dHeap initialized with size " << mDoExt_getJ2dHeap()->getSize() << " bytes" << std::endl;
    std::cout << "gameHeap initialized with size " << mDoExt_getGameHeap()->getSize() << " bytes" << std::endl;
    std::cout << "zeldaHeap initialized with size " << mDoExt_getZeldaHeap()->getSize() << " bytes" << std::endl;

    /* JKRSetAramTransferBuffer(NULL, 0x2000, JKRGetSystemHeap());
    JKRThreadSwitch::createManager(NULL);
    JKRThread* thread = new JKRThread(OSGetCurrentThread(), 0);

    cMl::init(mDoExt_getZeldaHeap());
    cM_initRnd(100, 100, 100);
    JKRDvdRipper::setSZSBufferSize(0x4000);
    JKRDvdAramRipper::setSZSBufferSize(0x4000);
    JKRAram::setSZSBufferSize(0x2000);
    mDoDvdThd::create(OSGetThreadPriority(OSGetCurrentThread()) - 2);
    mDoDvdErr_ThdInit();
    mDoMemCd_ThdInit(); */
}