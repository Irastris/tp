#ifndef JUTFADER_H
#define JUTFADER_H

#include "JSystem/JGeometry.h"
#include "JSystem/JUtility/TColor.h"

class JUTFader {
public:
    enum EStatus {
        UNKSTATUS_M1 = -1,
        UNKSTATUS_0 = 0,
    };

    JUTFader(int, int, int, int, JUtility::TColor);
    void control();
    void setStatus(JUTFader::EStatus, int);

    virtual ~JUTFader();
    virtual bool startFadeIn(int);
    virtual bool startFadeOut(int);
    virtual void draw();

    s32 getStatus() const { return mStatus; }
    void setColor(JUtility::TColor color) { mColor.set(color); }

    s32 mStatus;
    u16 field_0x8;
    u16 field_0xa;
    JUtility::TColor mColor;
    JGeometry::TBox2<f32> mBox;
    int mEStatus;
    u32 field_0x24;
};

#endif
