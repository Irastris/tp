#ifndef J3DVERTEX_H
#define J3DVERTEX_H

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class J3DModel;
class J3DAnmVtxColor;
class J3DVertexBuffer;

struct J3DVtxColorCalc {
    void calc(J3DModel*);
    virtual void calc(J3DVertexBuffer*);
    virtual ~J3DVtxColorCalc() {}

    bool checkFlag(u32 flag) { return mFlags & flag ? true : false; }

    u32 mFlags;
    J3DAnmVtxColor* mpVtxColor;
};

class J3DVertexData {
public:
    J3DVertexData();
    ~J3DVertexData() {}

    void* getVtxPosArray() const { return mVtxPosArray; }
    void* getVtxNrmArray() const { return mVtxNrmArray; }
    GXColor* getVtxColorArray(u8 idx) const { return mVtxColorArray[idx]; }
    void* getVtxTexCoordArray(u8 idx) const { return mVtxTexCoordArray[idx]; }
    void* getVtxNBTArray() const { return mVtxNBTArray; }
    u32 getNrmNum() const { return mNrmNum; }
    u32 getVtxNum() const { return mVtxNum; }
    u32 getColNum() const { return mColNum; }
    // GXVtxAttrFmtList* getVtxAttrFmtList() const { return mVtxAttrFmtList; }
    u8 getVtxPosFrac() const { return mVtxPosFrac; }
    u8 getVtxNrmFrac() const { return mVtxNrmFrac; }
    int getVtxPosType() const { return mVtxPosType; }
    int getVtxNrmType() const { return mVtxNrmType; }

    void setVtxPosFrac(u8 frac) { mVtxPosFrac = frac; }
    void setVtxPosType(GXCompType type) { mVtxPosType = type; }
    void setVtxNrmFrac(u8 frac) { mVtxNrmFrac = frac; }
    void setVtxNrmType(GXCompType type) { mVtxNrmType = type; }

private:
    friend class J3DModelLoader;

    u32 mVtxNum;
    u32 mNrmNum;
    u32 mColNum;
    u32 mTexCoordNum;
    u32 mPacketNum;
    // GXVtxAttrFmtList* mVtxAttrFmtList;
    void* mVtxPosArray;
    void* mVtxNrmArray;
    void* mVtxNBTArray;
    GXColor* mVtxColorArray[2];
    void* mVtxTexCoordArray[8];
    u8 mVtxPosFrac;
    GXCompType mVtxPosType;
    u8 mVtxNrmFrac;
    GXCompType mVtxNrmType;
};

class J3DVertexBuffer {
public:
    J3DVertexBuffer() { init(); }

    void setVertexData(J3DVertexData*);
    void init();
    ~J3DVertexBuffer();
    void setArray() const;
    s32 copyLocalVtxPosArray(u32);
    s32 copyLocalVtxNrmArray(u32);
    s32 copyLocalVtxArray(u32);
    s32 allocTransformedVtxPosArray();
    s32 allocTransformedVtxNrmArray();

    void setCurrentVtxPos(void* pVtxPos) { mCurrentVtxPos = pVtxPos; }
    void* getCurrentVtxPos() { return mCurrentVtxPos; }

    void setCurrentVtxNrm(void* pVtxNrm) { mCurrentVtxNrm = pVtxNrm; }
    void* getCurrentVtxNrm() { return mCurrentVtxNrm; }

    void setCurrentVtxCol(GXColor* pVtxCol) { mCurrentVtxCol = pVtxCol; }

    void frameInit() {
        setCurrentVtxPos(mVtxPosArray[0]);
        setCurrentVtxNrm(mVtxNrmArray[0]);
        setCurrentVtxCol(mVtxColArray[0]);
    }

    void* getTransformedVtxPos(int idx) { return mTransformedVtxPosArray[idx]; }
    void* getTransformedVtxNrm(int idx) { return mTransformedVtxNrmArray[idx]; }
    J3DVertexData* getVertexData() const { return mVtxData; }

    void swapTransformedVtxPos() {
        void* tmp = mTransformedVtxPosArray[0];
        mTransformedVtxPosArray[0] = mTransformedVtxPosArray[1];
        mTransformedVtxPosArray[1] = tmp;
    }

    void swapTransformedVtxNrm() {
        void* tmp = mTransformedVtxNrmArray[0];
        mTransformedVtxNrmArray[0] = mTransformedVtxNrmArray[1];
        mTransformedVtxNrmArray[1] = tmp;
    }

    void swapVtxPosArrayPointer() {
        void* temp = mVtxPosArray[0];
        mVtxPosArray[0] = mVtxPosArray[1];
        mVtxPosArray[1] = temp;
    }

    void swapVtxNrmArrayPointer() {
        void* temp = mVtxNrmArray[0];
        mVtxNrmArray[0] = mVtxNrmArray[1];
        mVtxNrmArray[1] = temp;
    }

    void swapVtxColArrayPointer() {
        GXColor* temp = mVtxColArray[0];
        mVtxColArray[0] = mVtxColArray[1];
        mVtxColArray[1] = temp;
    }

    void* getVtxPosArrayPointer(int index) {
        return mVtxPosArray[index];
    }

    void* getVtxNrmArrayPointer(int index) {
        return mVtxNrmArray[index];
    }

    GXColor* getVtxColArrayPointer(int index) {
        return mVtxColArray[index];
    }

private:
    J3DVertexData* mVtxData;
    void* mVtxPosArray[2];
    void* mVtxNrmArray[2];
    GXColor* mVtxColArray[2];
    void* mTransformedVtxPosArray[2];
    void* mTransformedVtxNrmArray[2];
    void* mCurrentVtxPos;
    void* mCurrentVtxNrm;
    GXColor* mCurrentVtxCol;
};

#endif
