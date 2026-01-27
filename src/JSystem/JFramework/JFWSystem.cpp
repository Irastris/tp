#include "JSystem/JFramework/JFWSystem.h"

JKRExpHeap* JFWSystem::rootHeap;
JKRExpHeap* JFWSystem::systemHeap;

void JFWSystem::init() {
    std::cout << "Hello from JFWSystem::init() @ JFWSystem.cpp" << std::endl;
    std::cout << "JFWSystem::init() is partially stubbed" << std::endl;

    /* OSInit();
    DVDInit(); */
    rootHeap = JKRExpHeap::createRoot(0, false);
    systemHeap = JKRExpHeap::create(0x5E6CA8, rootHeap, false);

    std::cout << "rootHeap size is " << rootHeap->getSize() << std::endl;
    std::cout << "systemHeap size is " << systemHeap->getSize() << std::endl;

    /* JKRAram::create(0xA00000, -1, 8, 7, 6);
    JUTVideo::createManager(&GXNtsc480IntDf);
    JUTGamePad::init(); */
}
