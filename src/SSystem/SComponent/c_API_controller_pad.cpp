#include "SSystem/SComponent/c_API_controller_pad.h"
#include "m_Do/m_Do_controller_pad.h"
#include "global.h"

void cAPICPad_recalibrate() {
    mDoCPd_c::recalibrate();
}

u32 cAPICPad_ANY_BUTTON(u32 portNo) {
    return mDoCPd_c::getTrig(portNo) & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_START);
}
