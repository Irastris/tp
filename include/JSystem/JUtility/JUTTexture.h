#ifndef JUTTEXTURE_H
#define JUTTEXTURE_H

#include <dolphin/gx.h>
#include <stdint.h>

class JUTPalette;

struct ResTIMG {
    u8 format;
    u8 alphaEnabled;
    u16 width;
    u16 height;
    u8 wrapS;
    u8 wrapT;
    u8 indexTexture;
    u8 colorFormat;
    u16 numColors;
    uintptr_t paletteOffset;
    u8 mipmapEnabled;
    u8 doEdgeLOD;
    u8 biasClamp;
    u8 maxAnisotropy;
    u8 minFilter;
    u8 magFilter;
    s8 minLOD;
    s8 maxLOD;
    u8 mipmapCount;
    u8 unknown;
    s16 LODBias;
    uintptr_t imageOffset;
};

class JUTTexture {
public:
    JUTTexture() {
        setCaptureFlag(false);
        mEmbPalette = NULL;
        mTexInfo = NULL;
    }

    JUTTexture(const ResTIMG* p_timg, u8 param_1) {
        mEmbPalette = NULL;
        storeTIMG(p_timg, param_1);
        setCaptureFlag(false);
    }

    ~JUTTexture();
    void storeTIMG(ResTIMG const*, JUTPalette*, GXTlut);
    void storeTIMG(ResTIMG const*, u8);
    void storeTIMG(ResTIMG const*, JUTPalette*);
    void attachPalette(JUTPalette*);
    void init();
    void initTexObj(GXTlut);
    void initTexObj();
    void load(GXTexMapID);

    const ResTIMG* getTexInfo() const { return mTexInfo; }
    s32 getFormat() const { return mTexInfo->format; }
    s32 getTransparency() const { return mTexInfo->alphaEnabled; }
    s32 getWidth() const { return mTexInfo->width; }
    s32 getHeight() const { return mTexInfo->height; }
    void setCaptureFlag(bool flag) { mFlags &= 2 | flag; }
    bool getCaptureFlag() const { return mFlags & 1; }
    bool getEmbPaletteDelFlag() const { return mFlags & 2; }
    void setEmbPaletteDelFlag(bool flag) { mFlags = (mFlags & 1) | (flag << 1);}
    int getTlutName() const { return mTlutName; }
    bool operator==(const JUTTexture& other) {
        return mTexInfo == other.mTexInfo
            && field_0x2c == other.field_0x2c
            && mWrapS == other.mWrapS
            && mWrapT == other.mWrapT
            && mMinFilter == other.mMinFilter
            && mMagFilter == other.mMagFilter
            && mMinLOD == other.mMinLOD
            && mMinLOD == other.mMinLOD
            && mLODBias == other.mLODBias;
    }
    bool operator!=(const JUTTexture& other) {
        return !operator==(other);
    }

private:
    GXTexObj mTexObj;
    const ResTIMG* mTexInfo;
    void* mTexData;
    JUTPalette* mEmbPalette;
    JUTPalette* field_0x2c;
    u8 mWrapS;
    u8 mWrapT;
    u8 mMinFilter;
    u8 mMagFilter;
    u16 mMinLOD;
    u16 mMaxLOD;
    s16 mLODBias;
    u8 mTlutName;
    u8 mFlags;
    void* field_0x3c;
};

#endif
