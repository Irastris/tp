#include "JSystem/JSystem.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "JSystem/J3DGraphAnimator/J3DMtxBuffer.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include "JSystem/JKernel/JKRHeap.h"

Mtx J3DMtxBuffer::sNoUseDrawMtx;

Mtx33 J3DMtxBuffer::sNoUseNrmMtx;

Mtx* J3DMtxBuffer::sNoUseDrawMtxPtr = &J3DMtxBuffer::sNoUseDrawMtx;

Mtx33* J3DMtxBuffer::sNoUseNrmMtxPtr = &J3DMtxBuffer::sNoUseNrmMtx;

void J3DMtxBuffer::initialize() {
    mJointTree = NULL;
    mpScaleFlagArr = NULL;
    mpEvlpScaleFlagArr = NULL;
    mpAnmMtx = NULL;
    mpWeightEvlpMtx = NULL;
    mpDrawMtxArr[0] = NULL;
    mpDrawMtxArr[1] = NULL;
    mpNrmMtxArr[0] = NULL;
    mpNrmMtxArr[1] = NULL;
    mpBumpMtxArr[0] = NULL;
    mpBumpMtxArr[1] = NULL;
    mMtxNum = 1;
    mCurrentViewNo = 0;
    mpUserAnmMtx = NULL;
}

enum {
    J3DMdlDataFlag_ConcatView = 0x10,
    J3DMdlDataFlag_NoAnimation = 0x100,
};

s32 J3DMtxBuffer::create(J3DModelData* pModelData, u32 mtxNum) {
    s32 ret = kJ3DError_Success;
    mMtxNum = mtxNum;
    mJointTree = &pModelData->getJointTree();

    ret = createAnmMtx(pModelData);
    if (ret != kJ3DError_Success)
        return ret;

    ret = createWeightEnvelopeMtx(pModelData);
    if (ret != kJ3DError_Success)
        return ret;

    if (pModelData->checkFlag(J3DMdlDataFlag_NoAnimation)) {
        setNoUseDrawMtx();
    } else {
        u32 loadType = getMdlDataFlag_MtxLoadType(pModelData->getFlag());
        switch (loadType) {
        case J3DMdlDataFlag_ConcatView:
            ret = setNoUseDrawMtx();
            break;
        case 0:
        default:
            ret = createDoubleDrawMtx(pModelData, mtxNum);
            break;
        }
    }

    if (ret != kJ3DError_Success)
        return ret;

    if (pModelData->getFlag() & J3DMdlDataFlag_ConcatView) {
        pModelData->setBumpFlag(0);
    } else {
        ret = createBumpMtxArray(pModelData, mtxNum);

        if (ret != kJ3DError_Success)
            return ret;
    }

    return ret;
}

J3DError J3DMtxBuffer::createAnmMtx(J3DModelData* pModelData) {
    if (pModelData->getJointNum() != 0) {
        mpScaleFlagArr = new u8[pModelData->getJointNum()];
        mpAnmMtx = new Mtx[pModelData->getJointNum()];
        mpUserAnmMtx = mpAnmMtx;
    }

    if (mpScaleFlagArr == NULL)
        return kJ3DError_Alloc;

    if (mpAnmMtx == NULL) {
        return kJ3DError_Alloc;
    }

    return kJ3DError_Success;
}

s32 J3DMtxBuffer::createWeightEnvelopeMtx(J3DModelData* pModelData) {
    if (pModelData->getWEvlpMtxNum() != 0) {
        mpEvlpScaleFlagArr = new u8[pModelData->getWEvlpMtxNum()];
        mpWeightEvlpMtx = new Mtx[pModelData->getWEvlpMtxNum()];
    }

    if (pModelData->getWEvlpMtxNum() != 0 && mpEvlpScaleFlagArr == NULL)
        return kJ3DError_Alloc;
    if (pModelData->getWEvlpMtxNum() != 0 && mpWeightEvlpMtx == NULL)
        return kJ3DError_Alloc;

    return kJ3DError_Success;
}

s32 J3DMtxBuffer::setNoUseDrawMtx() {
    mpDrawMtxArr[0] = mpDrawMtxArr[1] = &sNoUseDrawMtxPtr;
    mpNrmMtxArr[0] = mpNrmMtxArr[1] = &sNoUseNrmMtxPtr;
    mpBumpMtxArr[0] = mpBumpMtxArr[1] = NULL;
    return kJ3DError_Success;
}

s32 J3DMtxBuffer::createDoubleDrawMtx(J3DModelData* pModelData, u32 mtxNum) {
    if (mtxNum != 0) {
        for (s32 i = 0; i < 2; i++) {
            mpDrawMtxArr[i] = new Mtx*[mtxNum];
            mpNrmMtxArr[i] = new Mtx33*[mtxNum];
            mpBumpMtxArr[i] = NULL;
        }
    }

    if (mtxNum != 0) {
        for (s32 i = 0; i < 2; i++) {
            if (mpDrawMtxArr[i] == NULL)
                return kJ3DError_Alloc;
            if (mpNrmMtxArr[i] == NULL)
                return kJ3DError_Alloc;
        }
    }

    for (s32 i = 0; i < 2; i++) {
        for (u32 j = 0; j < mtxNum; j++) {
            if (pModelData->getDrawMtxNum() != 0) {
                mpDrawMtxArr[i][j] = new (JKRHeap::getCurrentHeap(), 0x20) Mtx[pModelData->getDrawMtxNum()];
                mpNrmMtxArr[i][j] = new (JKRHeap::getCurrentHeap(), 0x20) Mtx33[pModelData->getDrawMtxNum()];
            }
        }
    }

    for (s32 i = 0; i < 2; i++) {
        for (u32 j = 0; j < mtxNum; j++) {
            if (pModelData->getDrawMtxNum() != 0) {
                if (mpDrawMtxArr[i][j] == NULL)
                    return kJ3DError_Alloc;
                if (mpNrmMtxArr[i][j] == NULL)
                    return kJ3DError_Alloc;
            }
        }
    }

    return kJ3DError_Success;
}

s32 J3DMtxBuffer::createBumpMtxArray(J3DModelData* i_modelData, u32 mtxNum) {
    if (i_modelData->getModelDataType() == 0) {
        u16 bumpMtxNum = 0;
        u16 materialCount = 0;
        u16 materialNum = i_modelData->getMaterialNum();
        for (u16 j = 0; j < materialNum; j++) {
            J3DMaterial* material = i_modelData->getMaterialNodePointer(j);
            if (material->getNBTScale()->mbHasScale == true) {
                bumpMtxNum += material->getShape()->countBumpMtxNum();
                materialCount++;
            }
        }

        if (bumpMtxNum != 0 && mtxNum != 0) {
            for (int i = 0; i < 2; i++) {
                mpBumpMtxArr[i] = new Mtx33**[(u16)materialCount];
                if (mpBumpMtxArr[i] == NULL) {
                    return kJ3DError_Alloc;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            u32 offset = 0;
            u16 materialNum = i_modelData->getMaterialNum();
            for (u16 j = 0; j < materialNum; j++) {
                J3DMaterial* material = i_modelData->getMaterialNodePointer(j);
                if (material->getNBTScale()->mbHasScale == true) {
                    mpBumpMtxArr[i][offset] = new Mtx33*[mtxNum];
                    if (mpBumpMtxArr[i][offset] == NULL) {
                        return kJ3DError_Alloc;
                    }
                    material->getShape()->setBumpMtxOffset(offset);
                    offset++;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            u32 offset = 0;
            u16 materialNum = i_modelData->getMaterialNum();
            for (u16 j = 0; j < materialNum; j++) {
                J3DMaterial* material = i_modelData->getMaterialNodePointer((u16)j);
                if (material->getNBTScale()->mbHasScale == true) {
                    for (int k = 0; k < mtxNum; k++) {
                        mpBumpMtxArr[i][offset][k] = new (JKRHeap::getCurrentHeap(), 0x20) Mtx33[i_modelData->getDrawMtxNum()];
                        if (mpBumpMtxArr[i][offset][k] == NULL) {
                            return kJ3DError_Alloc;
                        }
                    }
                    offset++;
                }
            }
        }

        if (materialCount != 0) {
            i_modelData->setBumpFlag(1);
        }
    }

    return kJ3DError_Success;
}

void J3DMtxBuffer::calcWeightEnvelopeMtx() {
    MtxPtr weightAnmMtx;
    Mtx* worldMtx;
    Mtx* invMtx;
    f32 weight;
    int idx;
    int j;
    int mixNum;
    int i;
    int max;
    u16* indices;
    f32* weights;
    u8* pScale;
    Mtx mtx;

    i = -1;
    max = mJointTree->getWEvlpMtxNum();
    indices = mJointTree->getWEvlpMixMtxIndex() - 1;
    weights = mJointTree->getWEvlpMixWeight() - 1;

    while (++i < max) {
        pScale = &mpEvlpScaleFlagArr[i];
        *pScale = 1;
        weightAnmMtx = mpWeightEvlpMtx[i];

        weightAnmMtx[0][0] = weightAnmMtx[0][1] = weightAnmMtx[0][2] = weightAnmMtx[0][3] =
        weightAnmMtx[1][0] = weightAnmMtx[1][1] = weightAnmMtx[1][2] = weightAnmMtx[1][3] =
        weightAnmMtx[2][0] = weightAnmMtx[2][1] = weightAnmMtx[2][2] = weightAnmMtx[2][3] = 0.0f;

        j = 0;
        mixNum = mJointTree->getWEvlpMixMtxNum(i);
        do {
            idx = *++indices;
            worldMtx = &mpAnmMtx[idx];
            invMtx = &mJointTree->getInvJointMtx((u16)idx);

            MTXConcat(*worldMtx, *invMtx, mtx);

            weight = *++weights;

            weightAnmMtx[0][0] += mtx[0][0] * weight;
            weightAnmMtx[0][1] += mtx[0][1] * weight;
            weightAnmMtx[0][2] += mtx[0][2] * weight;
            weightAnmMtx[0][3] += mtx[0][3] * weight;
            weightAnmMtx[1][0] += mtx[1][0] * weight;
            weightAnmMtx[1][1] += mtx[1][1] * weight;
            weightAnmMtx[1][2] += mtx[1][2] * weight;
            weightAnmMtx[1][3] += mtx[1][3] * weight;
            weightAnmMtx[2][0] += mtx[2][0] * weight;
            weightAnmMtx[2][1] += mtx[2][1] * weight;
            weightAnmMtx[2][2] += mtx[2][2] * weight;
            weightAnmMtx[2][3] += mtx[2][3] * weight;

            *pScale &= mpScaleFlagArr[idx];
        } while (++j < mixNum);
    }
}

void J3DMtxBuffer::calcDrawMtx(u32 mdlFlag, Vec const& param_1, Mtx const& param_2) {
    Mtx* sp24, *sp20;
    int sp1C = 0;
    sp20 = mpAnmMtx;
    sp24 = mpWeightEvlpMtx;

    MtxPtr viewMtx;
    Mtx viewBaseMtx;
    u16 fullWgtNum; // r25
    u16 local_68;
    u16 local_6a;
    u16 local_6c;

    switch (mdlFlag) {
    case 0:
        viewMtx = j3dSys.getViewMtx();
        fullWgtNum = mJointTree->getDrawFullWgtMtxNum();
        for (u16 i = 0; i < fullWgtNum; i++) {
            MTXConcat(viewMtx, getAnmMtx(mJointTree->getDrawMtxIndex(i)), *getDrawMtx(i));
        }
        if (mJointTree->getDrawMtxNum() > fullWgtNum) {
            J3DPSMtxArrayConcat(viewMtx, *mpWeightEvlpMtx, *getDrawMtx(fullWgtNum), mJointTree->getWEvlpMtxNum());
        }
        return;
    case 1:
        local_68 = mJointTree->getDrawFullWgtMtxNum();
        for (u16 i = 0; i < local_68; i++) {
            MTXCopy(getAnmMtx(mJointTree->getDrawMtxIndex(i)), *getDrawMtx(i));
        }
        local_6a = mJointTree->getDrawFullWgtMtxNum();
        for (u16 i = 0; i < local_6a; i++) {
            MTXCopy(getWeightAnmMtx(i), *getDrawMtx(mJointTree->getDrawFullWgtMtxNum() + i));
        }
        break;
    case 2:
        J3DCalcViewBaseMtx(j3dSys.getViewMtx(), param_1, param_2, viewBaseMtx);
        local_6c = mJointTree->getDrawFullWgtMtxNum();
        for (u16 i = 0; i < local_6c; i++) {
            MTXConcat(viewBaseMtx, getAnmMtx(mJointTree->getDrawMtxIndex(i)), *getDrawMtx(i));
        }
        if (mJointTree->getDrawMtxNum() > mJointTree->getDrawFullWgtMtxNum()) {
            J3DPSMtxArrayConcat(viewBaseMtx, *mpWeightEvlpMtx, *getDrawMtx(mJointTree->getDrawFullWgtMtxNum()), mJointTree->getWEvlpMtxNum());
        }
        return;
    default:
        break;
    }
}

void J3DMtxBuffer::calcNrmMtx() {
    u16 drawMtxNum = mJointTree->getDrawMtxNum();
    for (u16 i = 0; i < drawMtxNum; i++) {
        if (mJointTree->getDrawMtxFlag(i) == 0) {
            if (getScaleFlag(mJointTree->getDrawMtxIndex(i)) == 1) {
                setNrmMtx(i, *getDrawMtx(i));
            } else {
                J3DPSCalcInverseTranspose(*getDrawMtx(i), *getNrmMtx(i));
            }
        } else {
            if (getEnvScaleFlag(mJointTree->getDrawMtxIndex(i)) == 1) {
                setNrmMtx(i, *getDrawMtx(i));
            } else {
                J3DPSCalcInverseTranspose(*getDrawMtx(i), *getNrmMtx(i));
            }
        }
    }
}

void J3DMtxBuffer::calcBBoardMtx() {
    u16 drawMtxNum = mJointTree->getDrawMtxNum();
    for (u16 i = 0; i < drawMtxNum; i++) {
        if (mJointTree->getDrawMtxFlag(i) == 0) {
            u16 index = mJointTree->getDrawMtxIndex(i);
            if (mJointTree->getJointNodePointer(index)->getMtxType() == 1) {
                MtxPtr drawMtx = *getDrawMtx(i);
                J3DCalcBBoardMtx(drawMtx);

                Mtx33* nrmMtx = getNrmMtx(i);
                (*nrmMtx)[0][0] = 1.0f / drawMtx[0][0];
                (*nrmMtx)[0][1] = 0.0f;
                (*nrmMtx)[0][2] = 0.0f;
                (*nrmMtx)[1][0] = 0.0f;
                (*nrmMtx)[1][1] = 1.0f / drawMtx[1][1];
                (*nrmMtx)[1][2] = 0.0f;
                (*nrmMtx)[2][0] = 0.0f;
                (*nrmMtx)[2][1] = 0.0f;
                (*nrmMtx)[2][2] = 1.0f / drawMtx[2][2];
            } else if (mJointTree->getJointNodePointer(index)->getMtxType() == 2) {
                MtxPtr drawMtx = *getDrawMtx(i);
                J3DCalcYBBoardMtx(drawMtx);
                Mtx33* nrmMtx = getNrmMtx(i);
                J3DPSCalcInverseTranspose(drawMtx, *nrmMtx);
            }
        }
    }
}

void J3DCalcViewBaseMtx(Mtx view, Vec const& scale, const Mtx& base, Mtx dst) {
    Mtx m;

    m[0][0] = base[0][0] * scale.x;
    m[0][1] = base[0][1] * scale.y;
    m[0][2] = base[0][2] * scale.z;
    m[0][3] = base[0][3];

    m[1][0] = base[1][0] * scale.x;
    m[1][1] = base[1][1] * scale.y;
    m[1][2] = base[1][2] * scale.z;
    m[1][3] = base[1][3];

    m[2][0] = base[2][0] * scale.x;
    m[2][1] = base[2][1] * scale.y;
    m[2][2] = base[2][2] * scale.z;
    m[2][3] = base[2][3];

    MTXConcat(view, m, dst);
}
