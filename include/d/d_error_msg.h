#ifndef D_D_ERROR_MSG_H
#define D_D_ERROR_MSG_H

#include <iostream>

struct dShutdownErrorMsg_c {
    static bool execute();
};

struct dDvdErrorMsg_c {
    static void draw(s32);
    static bool execute();
};

#endif
