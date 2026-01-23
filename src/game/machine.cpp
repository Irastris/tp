#include "game/machine.h"

/* GXRenderModeObj g_ntscZeldaIntDf = {
    VI_TVMODE_NTSC_INT,
    608,
    448,
    448,
    27,
    16,
    666,
    448,
    VI_XFBMODE_DF,
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
    {8, 8, 10, 12, 10, 8, 8},
}; */

int mDoMch_Create() {
    printf("Hello from mDoMch_Create() @ game/machine.cpp \n");

    // JKRHeap::setDefaultDebugFill(mDoMch::mDebugFill);
    // JFWSystem::setMaxStdHeap(1);

    // JFWSystem::setSysHeapSize(0x5E6CA8);
    // JFWSystem::setFifoBufSize(0xA0000);
    // JFWSystem::setAramAudioBufSize(0xA00000);
    // JFWSystem::setAramGraphBufSize(-1);

    // JFWSystem::setRenderMode(mDoMch_render_c::getRenderModeObj());
    // JFWSystem::firstInit();
    // JKRExpHeap* dbPrintHeap = mDoExt_createDbPrintHeap(0x1800, JKRGetRootHeap()); // 6 KB
    // JUTDbPrint::start(NULL, dbPrintHeap);
    // mDoExt_createAssertHeap(JKRGetRootHeap());
    // JFWSystem::init();

    // JUTAssertion::setVisible(false);
    // JUTDbPrint::getManager()->setVisible(false);

    // JKRSetErrorFlag(JKRHeap::getRootHeap(), true);
    // JKRSetErrorFlag(JFWSystem::getSystemHeap(), true);

    // JKRHeap* rootHeap = (JKRHeap*)JKRGetRootHeap();
    // JKRHeap* rootHeap2 = rootHeap;

    // JKRHeap* systemHeap = JKRGetSystemHeap();
    // s32 size = systemHeap->getFreeSize();
    // size -= 0x10000;
    // JKRHeap* zeldaHeap = mDoExt_createZeldaHeap(size, systemHeap);
    // JKRSetCurrentHeap(zeldaHeap);

    // JKRSetAramTransferBuffer(NULL, 0x2000, JKRGetSystemHeap());
    // JKRThreadSwitch::createManager(NULL);
    // JKRThread* thread = new JKRThread(OSGetCurrentThread(), 0);

    // JUTConsole* sysConsole = JFWSystem::getSystemConsole();
    // sysConsole->setOutput(JUTConsole::OUTPUT_CONSOLE | JUTConsole::OUTPUT_OSREPORT);
    // sysConsole->setPosition(16, 42);

    // JUTException::setMapFile(MAP_FOLDER MAP_FILE);

    // cMl::init(mDoExt_getZeldaHeap());
    // cM_initRnd(100, 100, 100);
    // JKRDvdRipper::setSZSBufferSize(0x4000);
    // JKRDvdAramRipper::setSZSBufferSize(0x4000);
    // JKRAram::setSZSBufferSize(0x2000);
    // mDoDvdThd::create(OSGetThreadPriority(OSGetCurrentThread()) - 2);
    // mDoDvdErr_ThdInit();
    // mDoMemCd_ThdInit();

    return 1;
}