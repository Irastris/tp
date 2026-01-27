#ifndef JFWSYSTEM_H
#define JFWSYSTEM_H

#include <iostream>

#include "global.h"
#include "JSystem/JKernel/JKRExpHeap.h"
/* #include "JSystem/JKernel/JKRAram.h"
#include "jsystem/jutility/JUTVideo.h"
#include "jsystem/jutility/JUTGamePad.h" */

struct JFWSystem {
    static void init();

    static JKRExpHeap* getSystemHeap() { return systemHeap; }

    static JKRExpHeap* rootHeap;
    static JKRExpHeap* systemHeap;
};

#endif
