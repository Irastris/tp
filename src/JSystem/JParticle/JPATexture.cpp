#include "JSystem/JSystem.h"
#include "JSystem/JParticle/JPATexture.h"

JPATexture::JPATexture(u8 const* pData) {
    mpData = (const JPATextureData*)pData;
    mTexture.storeTIMG(&mpData->mResTIMG, (u8)0);
}

JPATexture::~JPATexture() {}
