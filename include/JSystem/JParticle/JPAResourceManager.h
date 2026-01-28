#ifndef JPARESOURCEMANAGER_H
#define JPARESOURCEMANAGER_H

#include "JSystem/JParticle/JPATexture.h"

class JKRHeap;
class JPAResource;
struct ResTIMG;

class JPAResourceManager {
public:
    JPAResourceManager(void const*, JKRHeap*);
    JPAResource* getResource(u16) const;
    bool checkUserIndexDuplication(u16) const;
    const ResTIMG* swapTexture(ResTIMG const*, char const*);
    void registRes(JPAResource*);
    void registTex(JPATexture*);
    u32 getResUserWork(u16) const;

    void load(u16 idx, GXTexMapID texMapID) { mpTexArr[idx]->load(texMapID); }

public:
    JKRHeap* mpHeap;
    JPAResource** mpResArr;
    JPATexture** mpTexArr;
    u16 mResMax;
    u16 mResNum;
    u16 mTexMax;
    u16 mTexNum;
};

#endif
