#ifndef JSURANDOMOUTPUTSTREAM_H_
#define JSURANDOMOUTPUTSTREAM_H_

#include "JSystem/JSupport/JSUOutputStream.h"

class JSURandomOutputStream : public JSUOutputStream {
public:
    JSURandomOutputStream() {}
    virtual ~JSURandomOutputStream() {}

    virtual s32 writeData(const void*, s32) = 0;
    virtual s32 getLength() const = 0;
    virtual s32 getPosition() const = 0;
    virtual s32 seek(s32, JSUStreamSeekFrom);
    virtual s32 getAvailable() const;
    virtual s32 seekPos(s32, JSUStreamSeekFrom) = 0;
};

#endif
