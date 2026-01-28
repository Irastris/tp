#ifndef J3DSKINDEFORM_H
#define J3DSKINDEFORM_H

#include "JSystem/J3DGraphAnimator/J3DCluster.h"
#include "JSystem/J3DGraphAnimator/J3DMtxBuffer.h"
#include <dolphin/types.h>

class J3DModel;
class J3DAnmCluster;
class J3DClusterVertex;
class JUTNameTab;

struct J3DSkinNList {
    J3DSkinNList();
    void calcSkin_VtxPosF32(f32 (*)[4], void*, void*);
    void calcSkin_VtxNrmF32(f32 (*)[4], void*, void*);

    u16* field_0x0;
    u16* field_0x4;
    f32* field_0x8;
    f32* field_0xc;
    u16 field_0x10;
    u16 field_0x12;
};

class J3DSkinDeform {
public:
    J3DSkinDeform();
    void initSkinInfo(J3DModelData*);
    int initMtxIndexArray(J3DModelData*);
    void changeFastSkinDL(J3DModelData*);
    void calcNrmMtx(J3DMtxBuffer*);
    void transformVtxPosNrm(J3DModelData*);
    void calcAnmInvJointMtx(J3DMtxBuffer*);
    void deformFastVtxPos_F32(J3DVertexBuffer*, J3DMtxBuffer*) const;
    void deformFastVtxNrm_F32(J3DVertexBuffer*, J3DMtxBuffer*) const;
    void deformVtxPos_F32(J3DVertexBuffer*, J3DMtxBuffer*) const;
    void deformVtxPos_S16(J3DVertexBuffer*, J3DMtxBuffer*) const;
    void deformVtxNrm_F32(J3DVertexBuffer*) const;
    void deformVtxNrm_S16(J3DVertexBuffer*) const;
    void deform(J3DModel*);
    void setNrmMtx(int i, MtxP mtx) {
        J3DPSMtx33CopyFrom34(mtx, (Mtx3P)mNrmMtx[i]);
    }
    Mtx3P getNrmMtx(int i) { return mNrmMtx[i]; }
    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) { return mFlags & flag ? true : false; }

    virtual void deform(J3DVertexBuffer*, J3DMtxBuffer*);
    virtual ~J3DSkinDeform();

    static u16* sWorkArea_WEvlpMixMtx[1024];
    static f32* sWorkArea_WEvlpMixWeight[1024];
    static u16 sWorkArea_MtxReg[1024];

private:
    u16* mPosData;
    u16* mNrmData;
    Mtx* mPosMtx;
    Mtx33* mNrmMtx;
    u32 mFlags;
    u8 field_0x18;
    u8 field_0x19;
    int field_0x1c;
    int field_0x20;
    J3DSkinNList* mSkinNList;
};

class J3DDeformer {
public:
    J3DDeformer(J3DDeformData*);
    void deform(J3DVertexBuffer*, u16, f32*);
    void deform(J3DVertexBuffer*, u16);
    void deform_VtxPosF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void deform_VtxNrmF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void normalizeWeight(int, f32*);

    void offFlag(u32 i_flag) { mFlags &= ~i_flag; }
    bool checkFlag(u32 i_flag) { return mFlags & i_flag ? true : false; }
    void setAnmCluster(J3DAnmCluster* anm) { mAnmCluster = anm; }
    void normalize(f32* i_vec) { VECNormalize((Vec*)i_vec, (Vec*)i_vec); }

    J3DDeformData* mDeformData;
    J3DAnmCluster* mAnmCluster;
    f32* field_0x8;
    f32* field_0xc;
    u32 mFlags;
};

inline void J3DFillZero32B(__REGISTER void* param_0, __REGISTER u32 param_1) {
#ifdef __MWERKS__
    asm {
        srwi param_1, param_1, 5
        mtctr param_1
    lbl_8032D948:
    	dcbz 0, param_0
    	addi param_0, param_0, 0x20
    	bdnz lbl_8032D948
    }
#endif
}

#endif
