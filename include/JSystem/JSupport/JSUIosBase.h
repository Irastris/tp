#ifndef JSUIOSBASE_H_
#define JSUIOSBASE_H_

#include "dolphin/types.h"

enum JSUStreamSeekFrom {
    JSUStreamSeekFrom_SET = 0,
    JSUStreamSeekFrom_CUR = 1,
    JSUStreamSeekFrom_END = 2,
};

class JSUIosBase {
public:
    enum EIoState {
        IOS_STATE_1 = 1,
        IOS_STATE_2 = 2,
    };

    JSUIosBase() { mState = false; }

    virtual ~JSUIosBase() {}

    bool isGood() const { return mState == 0; }
    void clrState(EIoState state) { mState &= ~state; }
    void setState(EIoState state) { mState |= state; }

private:
    bool mState;
};

#endif
