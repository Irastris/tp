#ifndef JSURANDOMINPUTSTREAM_H_
#define JSURANDOMINPUTSTREAM_H_

#include "JSystem/JSupport/JSUInputStream.h"

class JSURandomInputStream : public JSUInputStream {
public:
    JSURandomInputStream() {}
    virtual ~JSURandomInputStream() {}

    virtual s32 getAvailable() const {
        return getLength() - getPosition();
    }
    virtual s32 skip(s32);
    virtual u32 readData(void*, s32) = 0;
    virtual s32 getLength() const = 0;
    virtual s32 getPosition() const = 0;
    virtual s32 seekPos(s32, JSUStreamSeekFrom) = 0;

    s32 align(s32);
    s32 peek(void*, s32);
    s32 seek(s32, JSUStreamSeekFrom);
};

#endif
