#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include "JSystem/JKernel/JKRDisposer.h"
// #include <dolphin/dolphin.h>

typedef void (*callbackFn)(int, void*);

struct JUTGamePadRecordBase {
    virtual ~JUTGamePadRecordBase() {}
    virtual void getStatus(PADStatus* pad) = 0;
    virtual void write(PADStatus* pad) = 0;

    bool isActive() const { return mActive; }

    bool mActive;
};

struct JUTGamePad : public JKRDisposer {
public:
    enum EStickMode {
        EStickMode1 = 1,
    };

    enum EWhichStick {
        EMainStick,
        ESubStick,
    };

    enum EPadPort {
        EPortInvalid = -1,
        EPort1,
        EPort2,
        EPort3,
        EPort4,
    };

    enum EClampMode {
        EClampNone,
        EClampStick,
        EClampCircle,
    };

    JUTGamePad(JUTGamePad::EPadPort port);
    virtual ~JUTGamePad();

    void initList();
    static BOOL init();
    void clear();
    static u32 read();
    void assign();
    void checkResetCallback(OSTime holdTime);
    void update();
    void stopPatternedRumble() { mRumble.stopPatternedRumble(mPortNum); }
    void setButtonRepeat(u32, u32, u32);

    static void checkResetSwitch();
    static void clearForReset();
    static JUTGamePad* getGamePad(int port);
    static bool recalibrate(u32 mask);

    static void setAnalogMode(u32 mode) {
        sAnalogMode = mode;
        PADSetAnalogMode(mode);
    }

    static int getClampMode() { return sClampMode; }

    static void clearResetOccurred() { C3ButtonReset::sResetOccurred = false; }

    static void setResetCallback(callbackFn callback, void* arg) {
        C3ButtonReset::sCallback = callback;
        C3ButtonReset::sCallbackArg = arg;
    }

    u32 getButton() const { return mButton.mButton; }
    u32 getTrigger() const { return mButton.mTrigger; }
    u32 getRelease() const { return mButton.mRelease; }
    u32 getRepeat() const { return mButton.mRepeat; }
    f32 getMainStickX() const { return mMainStick.mPosX; }
    f32 getMainStickY() const { return mMainStick.mPosY; }
    f32 getMainStickValue() const { return mMainStick.mValue; }
    s16 getMainStickAngle() const { return mMainStick.mAngle; }
    f32 getSubStickX() const { return mSubStick.mPosX; }
    f32 getSubStickY() const { return mSubStick.mPosY; }
    f32 getSubStickValue() const { return mSubStick.mValue; }
    s16 getSubStickAngle() const { return mSubStick.mAngle; }
    u8 getAnalogA() const { return mButton.mAnalogA; }
    u8 getAnalogB() const { return mButton.mAnalogB; }
    u8 getAnalogL() const { return mButton.mAnalogL; }
    u8 getAnalogR() const { return mButton.mAnalogR; }
    s8 getErrorStatus() const { return mErrorStatus; }

    s16 getPortNum() const { return mPortNum; }

    JUTGamePadRecordBase* getPadReplay() const { return mPadReplay; }
    JUTGamePadRecordBase* getPadRecord() const { return mPadRecord; }

    bool testButton(u32 button) const { return mButton.mButton & button; }
    bool testTrigger(u32 button) const { return mButton.mTrigger & button; }

    bool isPushing3ButtonReset() const { return mPortNum != EPortInvalid && mButtonReset.mReset != false; }

    void stopMotorWave() { mRumble.stopPatternedRumbleAtThePeriod(); }
    void stopMotor() { mRumble.stopMotor(mPortNum, false); }
    void stopMotorHard() { CRumble::stopMotorHard(mPortNum); }

    static s8 getPortStatus(EPadPort port) { return mPadStatus[port].err; }

    struct CButton {
        CButton() { clear(); }
        void clear();
        void update(const PADStatus* padStatus, u32 stickStatus);
        void setRepeat(u32 mask, u32 delay, u32 rate);

        u32 mButton;
        u32 mTrigger;  // Pressed Buttons
        u32 mRelease;  // Released Buttons
        u8 mAnalogA;
        u8 mAnalogB;
        u8 mAnalogL;
        u8 mAnalogR;
        f32 mAnalogLf;
        f32 mAnalogRf;
        u32 mRepeat;
        u32 mRepeatCount;
        u32 mRepeatStart;
        u32 mRepeatMask;
        u32 mRepeatDelay;
        u32 mRepeatRate;
    };

    struct C3ButtonReset {
        C3ButtonReset() { mReset = false; }

        static u32 sResetPattern;
        static u32 sResetMaskPattern;
        static callbackFn sCallback;
        static void* sCallbackArg;
        static OSTime sThreshold;
        static s32 sResetOccurredPort;
        static bool sResetOccurred;
        static bool sResetSwitchPushing;

        bool mReset;
    };

    struct CStick {
        static f32 sPressPoint;
        static f32 sReleasePoint;

        CStick() { clear(); }
        void clear();
        void clear(JUTGamePad* pad);
        u32 update(s8 x, s8 u, JUTGamePad::EStickMode mode, JUTGamePad::EWhichStick stick, u32 buttons);
        u32 getButton(u32 buttons);

        f32 mPosX;
        f32 mPosY;
        f32 mValue;
        s16 mAngle;
        s8 mRawX;
        s8 mRawY;
    };

    void stopMotorWaveHard() { mRumble.stopPatternedRumble(mPortNum); }

    struct CRumble {
        CRumble(JUTGamePad* pad) { clear(pad); }

        static u32 sChannelMask[4];
        static u8 mStatus[4];
        static u32 mEnabled;

        enum ERumble {
            VAL_0 = 0,
            VAL_1 = 1,
            VAL_2 = 2,
        };

        void clear();
        void clear(JUTGamePad* pad);
        static void startMotor(int port);
        static void stopMotor(int port, bool hard_stop);
        void update(s16 port);
        void triggerPatternedRumble(u32 length);
        void startPatternedRumble(void* data, ERumble rumble, u32 length);
        void stopPatternedRumble(s16 port);
        void stopPatternedRumbleAtThePeriod();
        static void setEnabled(u32 mask);

        static void stopMotor(int port) { stopMotor(port, false); }
        static void stopMotorHard(int port) { stopMotor(port, true); }

        static bool isEnabled(u32 mask) {
            bool result;
            if (mEnabled & mask) {
                result = true;
            } else {
                result = false;
            }
            return result;
        }

        static bool isEnabledPort(int port) { return isEnabled(sChannelMask[port]); }

        u32 mFrame;
        u32 mLength;
        u8* mPattern;
        u32 mFrameCount;
        u8* field_0x10;
    };

    void startMotorWave(void* data, CRumble::ERumble rumble, u32 length) { mRumble.startPatternedRumble(data, rumble, length); }

    static JSUList<JUTGamePad> mPadList;
    static bool mListInitialized;
    static PADStatus mPadStatus[4];
    static CButton mPadButton[4];
    static CStick mPadMStick[4];
    static CStick mPadSStick[4];
    static EStickMode sStickMode;
    static int sClampMode;
    static u8 mPadAssign[4];
    static u32 sSuppressPadReset;
    static s32 sAnalogMode;
    static u32 sRumbleSupported;

    CButton mButton;
    CStick mMainStick;
    CStick mSubStick;
    CRumble mRumble;
    s16 mPortNum;
    s8 mErrorStatus;
    JSULink<JUTGamePad> mLink;
    JUTGamePadRecordBase* mPadRecord;
    JUTGamePadRecordBase* mPadReplay;
    C3ButtonReset mButtonReset;
    u8 field_0x9c[4];
    OSTime mResetHoldStartTime;
    u8 field_0xa8;
};

struct JUTGamePadLongPress {
    static JSUList<JUTGamePadLongPress> sPatternList;
    void checkCallback(int port, u32 hold_time);

    u32 getMaskPattern() const { return mMaskPattern; }
    u32 getPattern() const { return mPattern; }
    bool isValid() const { return mValid; }

    u8 field_0x0[0x10];
    bool mValid;
    bool field_0x11;
    u32 mPattern;
    u32 mMaskPattern;
    u32 mThreshold;
    bool mLongPressStatus[4];
    OSTime mStartHoldTime[4];
    bool field_0x48[4];
    void (*mCallback)(s32, JUTGamePadLongPress*, s32);
    s32 field_0x50;
};

inline void JUTReadGamePad() { JUTGamePad::read(); }

#endif
