#ifndef JPATEXTURE_H
#define JPATEXTURE_H

#include "JSystem/JUtility/JUTTexture.h"

struct JPATextureData {
    char field_0x00[0x0C];
    char mName[0x14];
    ResTIMG mResTIMG;
};

class JPATexture {
public:
    JPATexture(u8 const*);
    virtual ~JPATexture();

    void load(GXTexMapID texMapID) { mTexture.load(texMapID); }

    JUTTexture* getJUTTexture() { return &mTexture; }
    const char* getName() const { return mpData->mName; }

public:
    JUTTexture mTexture;
    const JPATextureData* mpData;
};

#endif
