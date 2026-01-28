#ifndef JPAEMITTERMANAGER_H
#define JPAEMITTERMANAGER_H

#include <dolphin/types.h>
#include "JSystem/JParticle/JPAList.h"
#include "JSystem/JParticle/JPADrawInfo.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JGeometry.h"

class JPAEmitterCallBack;
class JPAParticleCallBack;
class JPABaseEmitter;
class JPAResourceManager;
class JPABaseParticle;
class JKRHeap;
struct JPAEmitterWorkData;

class JPAEmitterManager {
public:
    JPAEmitterManager(u32, u32, JKRHeap*, u8, u8);
    JPABaseEmitter* createSimpleEmitterID(JGeometry::TVec3<f32> const&, u16, u8, u8, JPAEmitterCallBack*, JPAParticleCallBack*);
    void calc(u8);
    void draw(JPADrawInfo const*, u8);
    void forceDeleteAllEmitter();
    void forceDeleteGroupEmitter(u8);
    void forceDeleteEmitter(JPABaseEmitter*);
    void entryResourceManager(JPAResourceManager*, u8);
    void clearResourceManager(u8);
    void calcYBBCam();
    JPAResourceManager* getResourceManager(u16 idx) const { return pResMgrAry[idx]; }
    JPAResourceManager* getResourceManager(u8 res_mgr_id) const { return pResMgrAry[res_mgr_id]; }
    int getEmitterNumber() const { return emtrNum - mFreeEmtrList.getNumLinks(); }

public:
    JSUList<JPABaseEmitter>* pEmtrUseList;
    JSUList<JPABaseEmitter> mFreeEmtrList;
    JPAList<JPABaseParticle> mPtclPool;
    JPAResourceManager** pResMgrAry;
    JPAEmitterWorkData* pWd;
    u32 emtrNum;
    u32 ptclNum;
    u8 gidMax;
    u8 ridMax;
};

#endif
