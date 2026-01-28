#ifndef JUTPALETTE_H
#define JUTPALETTE_H

#include <dolphin/gx.h>

enum JUTTransparency { UNK0, UNK1 };

struct ResTLUT {
    u8 format;
    u8 transparency;
    u16 numColors;
};

class JUTPalette {
public:
    JUTPalette(GXTlut p1, GXTlutFmt p2, JUTTransparency p3, u16 p4, void* p5) {
        this->storeTLUT(p1, p2, p3, p4, p5);
    }

    JUTPalette(GXTlut tlutNo, ResTLUT* p_tlutRes) {
        storeTLUT(tlutNo, p_tlutRes);
    }

    void storeTLUT(GXTlut, ResTLUT*);
    void storeTLUT(GXTlut, GXTlutFmt, JUTTransparency, u16, void*);
    bool load();

    GXTlut getTlutName() const { return GXTlut(mTlutName); }
    GXTlutFmt getFormat() const { return GXTlutFmt(mFormat); }
    JUTTransparency getTransparency() const { return JUTTransparency(mTransparency); }
    u16 getNumColors() const { return mNumColors; }
    ResTLUT* getColorTable() const { return mColorTable; }

private:
    GXTlutObj mTlutObj;
    u8 mTlutName;
    u8 mFormat;
    ResTLUT* mColorTable;
    u16 mNumColors;
    u8 mTransparency;
};

#endif
