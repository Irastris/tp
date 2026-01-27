#include "game/controller.h"

void mDoCPd_c::create() {
    std::cout << "mDoCPd_c::create() is stubbed" << std::endl;

    /* m_gamePad[0] = new JUTGamePad(JUTGamePad::EPort1);
    m_gamePad[1] = NULL;
    m_gamePad[2] = NULL;
    m_gamePad[3] = NULL;

    if (!mDoRst::isReset()) {
        JUTGamePad::clearResetOccurred();
        JUTGamePad::setResetCallback(mDoRst_resetCallBack, NULL);
    }
    JUTGamePad::setAnalogMode(3);

    interface_of_controller_pad* cpad = &m_cpadInfo[0];
    for (int i = 0; i < 4; i++) {
        cpad->mHoldLockL = cpad->mTrigLockL = false;
        cpad->mHoldLockR = cpad->mTrigLockR = false;
        cpad++;
    } */
}
