#include "d/d_stage.h"

void dStage_SetErrorRoom() {
    // No-op
}

void dStage_SetErrorStage() {
    // No-op
}

dStage_roomStatus_c dStage_roomControl_c::mStatus[0x40];

void dStage_stageDt_c::init() {
    mCamera = NULL;
    mArrow = NULL;
    mPlayer = NULL;
    mRoom = NULL;
    mMapInfo = NULL;
    mMapInfoBase = NULL;
    mPaletteInfo = NULL;
    mPselectInfo = NULL;
    mEnvrInfo = NULL;
    mVrboxInfo = NULL;
    mVrboxcolInfo = NULL;
    mPlightInfo = NULL;
    mPlightNumInfo = 0;
    mMapEventInfo = NULL;
    mStagInfo = NULL;
    mSclsInfo = NULL;
    mPntInfo = NULL;
    mPathInfo = NULL;
    mPnt2Info = NULL;
    mPath2Info = NULL;
    mSoundInf = NULL;
    mSoundInfCL = NULL;
    mFloorInfo = NULL;
    mMemoryConfig = NULL;
    mMemoryMap = NULL;
    mMulti = NULL;
    mTresure = NULL;
    mDMap = NULL;
    mDrTg = NULL;
    mDoor = NULL;
    mElst = NULL;
    mWorldRollAngleX = 0;
    mWorldRollDirAngleY = 0;
}

void dStage_roomDt_c::init() {
    mLightVecInfo = NULL;
    mLightVecInfoNum = 0;
    mMapInfo = NULL;
    mMapInfoBase = NULL;
    mVrboxInfo = NULL;
    mVrboxcolInfo = NULL;
    mFileListInfo = NULL;
    mPlayer = NULL;
    mPnt2Info = NULL;
    mPath2Info = NULL;
    mCamera = NULL;
    mArrow = NULL;
    mMapEventInfo = NULL;
    mSoundInf = NULL;
    mSoundInfCL = NULL;
    mSclsInfo = NULL;
    mLbnk = NULL;
    mTresure = NULL;
    mDrTg = NULL;
    mDoor = NULL;
    mFloorInfo = NULL;
}

s8 dStage_roomControl_c::mStayNo;

stage_map_info_class* dStage_roomDt_c::getMapInfo2(int param_0) const {
    stage_map_info_dummy_class* map_info_p = getMapInfoBase();

    if (map_info_p == NULL || map_info_p->num == 0 || map_info_p->m_entries == NULL) {
        return NULL;
    }

    stage_map_info_class* data_p = map_info_p->m_entries;

    for (int i = 0; i < map_info_p->num; i++) {
        if (param_0 == data_p->field_0x35) {
            return data_p;
        }

        data_p++;
    }

    return NULL;
}

stage_map_info_class* dStage_stageDt_c::getMapInfo2(int param_0) const {
    stage_map_info_dummy_class* map_info_p = getMapInfoBase();

    if (map_info_p == NULL || map_info_p->num == 0 || map_info_p->m_entries == NULL) {
        return NULL;
    }

    stage_map_info_class* data_p = map_info_p->m_entries;

    for (int i = 0; i < map_info_p->num; i++) {
        if (param_0 == data_p->field_0x35) {
            return data_p;
        }

        data_p++;
    }

    return NULL;
}

dStage_Elst_c* dStage_stageDt_c::getElst(void) { return mElst; }

void dStage_stageDt_c::resetOldMulti() {
    mOldMulti = NULL;
}

void dStage_stageDt_c::setOldMulti() {
    mOldMulti = mMulti;
}