#ifndef J3DDRAWBUFFER_H
#define J3DDRAWBUFFER_H

#include "JSystem/J3DGraphBase/J3DSys.h"

// TODO: Deduplicate instances of this
typedef f32 (*MtxP)[3];

inline f32 J3DCalcZValue(MtxP m, Vec* v) {
    return m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3];
}

class J3DDrawBuffer;
class J3DPacket;
class J3DDrawPacket;
class J3DMatPacket;
class J3DShapePacket;

enum J3DDrawBufDrawMode {
    J3DDrawBufDrawMode_Head,
    J3DDrawBufDrawMode_Tail,

    J3DDrawBufDrawMode_MAX,
};

enum J3DDrawBufSortMode {
    J3DDrawBufSortMode_Mat,
    J3DDrawBufSortMode_MatAnm,
    J3DDrawBufSortMode_Z,
    J3DDrawBufSortMode_Model,
    J3DDrawBufSortMode_Invalid,
    J3DDrawBufSortMode_Non,

    J3DDrawBufSortMode_MAX,
};

class J3DDrawBuffer {
public:
    typedef int (J3DDrawBuffer::*sortFunc)(J3DMatPacket*);
    typedef void (J3DDrawBuffer::*drawFunc)() const;

    J3DDrawBuffer() { initialize(); }
    ~J3DDrawBuffer();
    void initialize();
    int allocBuffer(u32);
    void frameInit();
    int entryMatSort(J3DMatPacket*);
    int entryMatAnmSort(J3DMatPacket*);
    int entryZSort(J3DMatPacket*);
    int entryModelSort(J3DMatPacket*);
    int entryInvalidSort(J3DMatPacket*);
    int entryNonSort(J3DMatPacket*);
    int entryImm(J3DPacket* pPacket, u16 index);
    void draw() const;
    void drawHead() const;
    void drawTail() const;

    u32 getEntryTableSize() { return mEntryTableSize; }
    int getSortMode() { return mSortMode; }

    inline void calcZRatio();
    void setNonSort() { mSortMode = J3DDrawBufSortMode_Non; }
    void setZSort() { mSortMode = J3DDrawBufSortMode_Z; }
    void setZMtx(MtxP mtx) { mpZMtx = mtx; }

public:
    J3DPacket** mpBuffer;
    u32 mEntryTableSize;
    u32 mDrawMode;
    u32 mSortMode;
    f32 mZNear;
    f32 mZFar;
    f32 mZRatio;
    MtxP mpZMtx;
    J3DPacket* mpCallBackPacket;

    static sortFunc sortFuncTable[6];
    static drawFunc drawFuncTable[2];
    static int entryNum;
};

#endif
