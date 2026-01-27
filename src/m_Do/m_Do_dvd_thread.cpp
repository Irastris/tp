#include "m_Do/m_Do_dvd_thread.h"

mDoDvdThd_param_c mDoDvdThd::l_param;

mDoDvdThd_command_c::~mDoDvdThd_command_c() {
    // No-op
}

mDoDvdThd_param_c::mDoDvdThd_param_c() {
    std::cout << "mDoDvdThd_param_c::mDoDvdThd_param_c() is stubbed" << std::endl;

    /* OSInitMessageQueue(&mMessageQueue, &mMessageQueueMessages, 1);
    OSInitMutex(&mMutext);
    cLs_Create(&mNodeList); */
}

void mDoDvdThd_param_c::addition(mDoDvdThd_command_c* pCommand) {
    std::cout << "mDoDvdThd_param_c::addition() is stubbed" << std::endl;

    /* OSLockMutex(&mMutext);
    cLs_Addition(&mNodeList, pCommand);
    OSUnlockMutex(&mMutext);
    this->kick(); */
}

mDoDvdThd_command_c::mDoDvdThd_command_c() {
    std::cout << "mDoDvdThd_command_c::mDoDvdThd_command_c() is stubbed" << std::endl;

    mIsDone = false;
    // cNd_ForcedClear(this);
}

mDoDvdThd_callback_c::~mDoDvdThd_callback_c() {
    // No-op
}

mDoDvdThd_callback_c::mDoDvdThd_callback_c(mDoDvdThd_callback_func pFunc, void* pData) {
    mFunction = pFunc;
    mData = pData;
    mResult = NULL;
}

mDoDvdThd_callback_c* mDoDvdThd_callback_c::create(mDoDvdThd_callback_func pFunc, void* pData) {
    mDoDvdThd_callback_c* callCmd = new (mDoExt_getCommandHeap(), -4) mDoDvdThd_callback_c(pFunc, pData);

    if (callCmd != NULL) {
        mDoDvdThd::l_param.addition(callCmd);
    }

    return callCmd;
}

s32 mDoDvdThd_callback_c::execute() {
    mResult = mFunction(mData);
    mIsDone = true;

    return mResult != NULL;
}