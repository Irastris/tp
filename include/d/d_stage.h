// TODO: To be progressively uncommented as necessary

#include "global.h"
#include "SSystem/SComponent/c_lib.h"

// TODO: Used by this header, but not included directly
// Adding directly for now
#include <dolphin/gx.h>
#include <dolphin/mtx.h> // Resolves Vec, might be overkill?
#include <dolphin/types.h>
#include "JSystem/JKernel/JKRExpHeap.h"

struct stage_vrboxcol_info_class {
    /* color_RGB_class sky_col;
    color_RGB_class kumo_top_col;
    color_RGB_class kumo_bottom_col; */
    GXColor kumo_shadow_col;
    GXColor kasumi_outer_col;
    GXColor kasumi_inner_col;
};

struct stage_vrbox_info_class { // Virt
    /* color_RGB_class field_0x0;
    color_RGB_class field_0x3;
    color_RGB_class field_0x6; */
    GXColor field_0x9;
    GXColor field_0xd;
    GXColor field_0x11;
};

struct stage_tresure_data_class { // TRES
    char name[8];
    // fopAcM_prmBase_class base;
};

struct stage_tresure_class {
    int num;
    stage_tresure_data_class* m_entries;
};

struct stage_stag_info_class { // STAG
    f32 mNear;
    f32 mFar;
    u8 mCameraType;
    u8 field_0x09;
    u16 field_0x0a;
    u32 field_0x0c;
    u32 field_0x10;
    u8 field_0x14[6];  // usually all 0xFF
    s16 mGapLevel;
    s16 mRangeUp;
    s16 mRangeDown;
    f32 field_0x20;
    f32 field_0x24;
    u8 mMsgGroup;
    u16 mStageTitleNo;
    u8 mParticleNo[16];
};

struct stage_scls_info_class { // SCLS
    char mStage[8];
    u8 mStart;
    s8 mRoom;
    u8 field_0xa;
    u8 field_0xb;
    u8 mWipe;

    char* getStage() { return mStage; }

    int getRoom() { return mRoom; }
};

struct stage_scls_info_dummy_class {
    int num;
    stage_scls_info_class* m_entries;
};

struct stage_pure_lightvec_info_class { // LGT
    Vec position;
    f32 radius;
    f32 directionX;
    f32 directionY;
    f32 spotCutoff;
    u8 spot_type;
    u8 dist_atten_type;
    u8 flags;
    u8 switch_no;
};

struct stage_pselect_info_class { // COLO
    u8 palette_id[8];
    f32 change_rate;
};

struct stage_plight_info_class { // LGHT
    Vec position;
    f32 power;
    u8 field_0x10[0x18 - 0x10];
    // color_RGB_class color;
    u8 fluctuation;
};

struct stage_palette_info_class { // PAL
    /* color_RGB_class actor_amb_col;
    color_RGB_class bg_amb_col[4];
    color_RGB_class plight_col[6];
    color_RGB_class fog_col; */
    f32 fog_start_z;
    f32 fog_end_z;
    u8 vrboxcol_id;
    u8 bg_light_influence;
    u8 cloud_shadow_density;
    u8 unk_0x2f;
    u8 bloom_tbl_id;
    u8 BG1_amb_alpha;
    u8 BG2_amb_alpha;
    u8 BG3_amb_alpha;
};

struct stage_map_info_class {
    u8 field_0x0[0x35];
    u8 field_0x35;
    u8 field_0x36[2];
};

struct stage_map_info_dummy_class {
    int num;
    stage_map_info_class* m_entries;
};

struct stage_envr_info_class { // Env
    u8 pselect_id[65];
};

struct stage_camera2_data_class { // CAMR / RCAM
    char m_cam_type[16];
    u8 m_arrow_idx;
    u8 field_0x11;
    u8 field_0x12;
    u8 field_0x13;
    u16 field_0x14;
    u16 field_0x16;
};

struct stage_camera_class {
    int num;
    stage_camera2_data_class* m_entries;
};

struct stage_arrow_data_class { // AROB / RARO
    f32 posX;
    f32 posY;
    f32 posZ;
    s16 angleX;
    s16 angleY;
    s16 angleZ;
    s16 field_0x12;
};

struct stage_arrow_class {
    int num;
    stage_arrow_data_class* m_entries;
};

struct stage_actor_data_class { // ACT
    char name[8];
    // fopAcM_prmBase_class base;
};

struct stage_actor_class {
    int num;
    stage_actor_data_class* m_entries;
};

struct stage_tgsc_data_class { // TGSC / SCOB / TGDR / Door
    char name[8];
    /* fopAcM_prmBase_class base;
    fopAcM_prmScale_class scale; */
};

struct stage_tgsc_class {
    int num;
    stage_tgsc_data_class* m_entries;
};

struct roomRead_data_class { // RTBL
    u8 num;
    u8 field_0x1;
    u8 field_0x2;
    u8* m_rooms;
};

struct roomRead_class {
    int num;
    roomRead_data_class** m_entries;
};

struct dStage_MemoryMap_c { // MEM
    int m_num;
    u32* field_0x4;
};

struct dStage_MemoryConfig_data { // MEC
    u8 m_roomNo;
    u8 m_blockID;
};

struct dStage_MemoryConfig_c {
    int m_num;
    dStage_MemoryConfig_data* field_0x4;
};

struct dPath;
struct dStage_dPath_c { // PATH / RPAT
    int m_num;
    dPath* m_path;
};

struct dStage_dPnt_c { // PPNT / RPPN
    int num;
    u32 m_pnt_offset;
};

struct dStage_Mult_info { // MULT
    f32 mTransX;
    f32 mTransY;
    s16 mAngle;
    u8 mRoomNo;
};

class dStage_Multi_c {
public:
    int num;
    dStage_Mult_info* m_entries;
};

struct stage_sound_data { // SOND
    char field_0x0[8];
    Vec field_0x8;
    u8 field_0x14;
    u8 field_0x15;
    u8 field_0x16;
    u8 field_0x17;
    u8 field_0x18;
    u8 field_0x19;
    u8 field_0x1a;
};

struct dStage_SoundInfo_c {
    int num;
    stage_sound_data* entries;
};

class dStage_FileList_dt_c { // FILI
public:
    u32 mParameters;
    f32 mSeaLevel;
    f32 field_0x8;
    f32 field_0xc;
    u8 field_0x10[10];
    u8 mDefaultCamera;
    u8 mBitSw;
    u16 mMsg;
};

class dStage_FileList2_dt_c { // FILI
public:
    f32 mLeftRmX;
    f32 mInnerRmZ;
    f32 mRightRmX;
    f32 mFrontRmZ;
    u8 mMinFloorNo;
    u8 mMaxFloorNo;
    u8 field_0x12;
    u8 field_0x13;
    f32 field_0x14;
    f32 field_0x18;
    s16 field_0x1c;
};

struct dStage_FileList2_c {
    int num;
    dStage_FileList2_dt_c* entries;
};

struct dStage_FloorInfo_dt_c { // FLOR
    int field_0x00;
    u8 floorNo;
    s8 field_0x05[14];
};

struct dStage_FloorInfo_c {
    int num;
    dStage_FloorInfo_dt_c* m_entries;
};

class dStage_Lbnk_dt_c { // LBNK
public:
    u8 bank;
    u8 bank2;
    u8 field_0x2;
};

struct dStage_Lbnk_c {
    int num;
    dStage_Lbnk_dt_c* entries;
};

struct dStage_Elst_dt_c {
    u8 m_layerTable[15];
};

struct dStage_Elst_c {
    int m_entryNum;
    dStage_Elst_dt_c* m_entries;
};

struct dStage_DMap_dt_c { // DMAP
    int field_0x00;
    int field_0x04;
    int field_0x08;
    f32 offsetY;
};

struct dStage_DMap_c {
    int num;
    dStage_DMap_dt_c* entries;
};

struct dStage_MapEvent_dt_c { // REVT
    u8 type;
    u8 field_0x1;
    u8 field_0x2;
    u8 field_0x3;
    u8 field_0x4;
    u8 field_0x5;
    u8 priority;
    u8 field_0x7;
    u8 field_0x8;
    u8 field_0x9;
    u8 field_0xA;
    u8 field_0xB;
    u8 field_0xC;
    union {
        char event_name[13];
        struct {
            u8 field_0xd[0x14 - 0xD];
            u16 field_0x14;
            u8 field_0x16;
            u8 field_0x17;
            u8 sound_type;
            u8 field_0x19;
        } maptool;
    } data;

    u8 field_0x1a;
    u8 switch_no;
};

enum dStage_MapEvent_dt_type {
    dStage_MapEvent_dt_TYPE_MAPTOOLCAMERA,
    dStage_MapEvent_dt_TYPE_ZEV,
    dStage_MapEvent_dt_TYPE_STB,
};

struct dStage_MapEventInfo_c {
    int num;
    dStage_MapEvent_dt_c* m_entries;
};

class dStage_dt_c {
public:
    dStage_dt_c() {}
    void setRoomNo(s8 roomNo) { mRoomNo = roomNo; }
    s8 getRoomNo() { return mRoomNo; }

    virtual void init(void) = 0;
    virtual void setCamera(stage_camera_class*) = 0;
    virtual stage_camera_class* getCamera(void) const = 0;
    virtual void setArrow(stage_arrow_class*) = 0;
    virtual stage_arrow_class* getArrow(void) const = 0;
    virtual void setPlayer(stage_actor_class*) = 0;
    virtual stage_actor_class* getPlayer(void) const = 0;
    virtual void setPlayerNum(u16) = 0;
    virtual u16 getPlayerNum(void) const = 0;
    /* virtual void setRoom(roomRead_class*) = 0;
    virtual roomRead_class* getRoom(void) const = 0; */
    virtual void setMapInfo(stage_map_info_class*) = 0;
    virtual stage_map_info_class* getMapInfo(void) const = 0;
    virtual stage_map_info_class* getMapInfo2(int) const = 0;
    virtual void setMapInfoBase(stage_map_info_dummy_class*) = 0;
    virtual stage_map_info_dummy_class* getMapInfoBase(void) const = 0;
    virtual void setPaletteInfo(stage_palette_info_class*) = 0;
    virtual stage_palette_info_class* getPaletteInfo(void) const = 0;
    virtual void setPselectInfo(stage_pselect_info_class*) = 0;
    virtual stage_pselect_info_class* getPselectInfo(void) const = 0;
    virtual void setEnvrInfo(stage_envr_info_class*) = 0;
    virtual stage_envr_info_class* getEnvrInfo(void) const = 0;
    virtual void setVrboxInfo(stage_vrbox_info_class*) = 0;
    virtual stage_vrbox_info_class* getVrboxInfo(void) const = 0;
    virtual void setVrboxcolInfo(stage_vrboxcol_info_class*) = 0;
    virtual stage_vrboxcol_info_class* getVrboxcolInfo(void) const = 0;
    virtual void setPlightInfo(stage_plight_info_class*) = 0;
    virtual stage_plight_info_class* getPlightInfo(void) const = 0;
    virtual void setPaletteNumInfo(int) = 0;
    virtual int getPaletteNumInfo(void) const = 0;
    virtual void setPselectNumInfo(int) = 0;
    virtual int getPselectNumInfo(void) const = 0;
    virtual void setEnvrNumInfo(int) = 0;
    virtual int getEnvrNumInfo(void) const = 0;
    virtual void setVrboxNumInfo(int) = 0;
    virtual int getVrboxNumInfo(void) const = 0;
    virtual void setVrboxcolNumInfo(int) = 0;
    virtual int getVrboxcolNumInfo(void) const = 0;
    virtual void setPlightNumInfo(int) = 0;
    virtual int getPlightNumInfo(void) const = 0;
    virtual void setLightVecInfo(stage_pure_lightvec_info_class*) = 0;
    virtual stage_pure_lightvec_info_class* getLightVecInfo(void) const = 0;
    virtual void setLightVecInfoNum(int) = 0;
    virtual int getLightVecInfoNum(void) const = 0;
    virtual void setStagInfo(stage_stag_info_class*) = 0;
    virtual stage_stag_info_class* getStagInfo(void) const = 0;
    virtual void setSclsInfo(stage_scls_info_dummy_class*) = 0;
    virtual stage_scls_info_dummy_class* getSclsInfo(void) const = 0;
    virtual void setPntInfo(dStage_dPnt_c*) = 0;
    virtual dStage_dPnt_c* getPntInf(void) const = 0;
    virtual void setPathInfo(dStage_dPath_c*) = 0;
    virtual dStage_dPath_c* getPathInf(void) const = 0;
    virtual void setPnt2Info(dStage_dPnt_c*) = 0;
    virtual dStage_dPnt_c* getPnt2Inf(void) const = 0;
    virtual void setPath2Info(dStage_dPath_c*) = 0;
    virtual dStage_dPath_c* getPath2Inf(void) const = 0;
    virtual void setSoundInf(dStage_SoundInfo_c*) = 0;
    virtual dStage_SoundInfo_c* getSoundInf(void) const = 0;
    virtual void setSoundInfCL(dStage_SoundInfo_c*) = 0;
    virtual dStage_SoundInfo_c* getSoundInfCL(void) const = 0;
    virtual void setMapEventInfo(dStage_MapEventInfo_c*) = 0;
    virtual dStage_MapEventInfo_c* getMapEventInfo(void) const = 0;
    virtual void setFileList2Info(dStage_FileList2_dt_c*) = 0;
    virtual dStage_FileList2_dt_c* getFileList2Info(void) const = 0;
    virtual void setFileListInfo(dStage_FileList_dt_c*) = 0;
    virtual dStage_FileList_dt_c* getFileListInfo(void) const = 0;
    virtual void setFloorInfo(dStage_FloorInfo_c*) = 0;
    virtual dStage_FloorInfo_c* getFloorInfo(void) const = 0;
    virtual void setMemoryConfig(dStage_MemoryConfig_c*) = 0;
    virtual dStage_MemoryConfig_c* getMemoryConfig(void) const = 0;
    virtual void setMemoryMap(dStage_MemoryMap_c*) = 0;
    virtual dStage_MemoryMap_c* getMemoryMap(void) const = 0;
    virtual void setMulti(dStage_Multi_c*) = 0;
    virtual dStage_Multi_c* getMulti(void) const = 0;
    virtual void setOldMulti(void) = 0;
    virtual void resetOldMulti(void) = 0;
    virtual dStage_Multi_c* getOldMulti(void) const = 0;
    virtual void setLbnk(dStage_Lbnk_c*) = 0;
    virtual dStage_Lbnk_c* getLbnk(void) const = 0;
    virtual void setTresure(stage_tresure_class*) = 0;
    virtual stage_tresure_class* getTresure(void) const = 0;
    virtual void setDMap(dStage_DMap_c*) = 0;
    virtual dStage_DMap_c* getDMap(void) const = 0;
    virtual void setDrTg(stage_tgsc_class*) = 0;
    virtual stage_tgsc_class* getDrTg(void) const = 0;
    virtual void setDoor(stage_tgsc_class*) = 0;
    virtual stage_tgsc_class* getDoor(void) const = 0;
    virtual void setMapPath(void*) = 0;
    virtual void* getMapPath(void) = 0;
    virtual void setElst(dStage_Elst_c*) = 0;
    virtual dStage_Elst_c* getElst(void) = 0;

private:
    s8 mRoomNo;
};

void dStage_SetErrorStage();
void dStage_SetErrorRoom();

class dStage_stageDt_c : public dStage_dt_c {
public:
    dStage_stageDt_c() {}

    virtual void init(void);
    virtual void setCamera(stage_camera_class* i_Camera) { mCamera = i_Camera; }
    virtual stage_camera_class* getCamera(void) const { return mCamera; }
    virtual void setArrow(stage_arrow_class* i_Arrow) { mArrow = i_Arrow; }
    virtual stage_arrow_class* getArrow(void) const { return mArrow; }
    virtual void setPlayer(stage_actor_class* i_Player) { mPlayer = i_Player; }
    virtual stage_actor_class* getPlayer(void) const { return mPlayer; }
    virtual void setPlayerNum(u16 i_PlayerNum) { mPlayerNum = i_PlayerNum; }
    virtual u16 getPlayerNum(void) const { return mPlayerNum; }
    virtual void setRoom(roomRead_class* i_Room) { mRoom = i_Room; }
    virtual roomRead_class* getRoom(void) const { return mRoom; }
    virtual void setMapInfo(stage_map_info_class* i_MapInfo) { mMapInfo = i_MapInfo; }
    virtual stage_map_info_class* getMapInfo(void) const { return mMapInfo; }
    virtual stage_map_info_class* getMapInfo2(int) const;
    virtual void setMapInfoBase(stage_map_info_dummy_class* i_MapInfoBase) { mMapInfoBase = i_MapInfoBase; }
    virtual stage_map_info_dummy_class* getMapInfoBase(void) const { return mMapInfoBase; }
    virtual void setPaletteInfo(stage_palette_info_class* i_PaletteInfo) { mPaletteInfo = i_PaletteInfo; }
    virtual stage_palette_info_class* getPaletteInfo(void) const { return mPaletteInfo; }
    virtual void setPselectInfo(stage_pselect_info_class* i_PselectInfo) { mPselectInfo = i_PselectInfo; }
    virtual stage_pselect_info_class* getPselectInfo(void) const { return mPselectInfo; }
    virtual void setEnvrInfo(stage_envr_info_class* i_EnvrInfo) { mEnvrInfo = i_EnvrInfo; }
    virtual stage_envr_info_class* getEnvrInfo(void) const { return mEnvrInfo; }
    virtual void setVrboxInfo(stage_vrbox_info_class* i_VrboxInfo) { mVrboxInfo = i_VrboxInfo; }
    virtual stage_vrbox_info_class* getVrboxInfo(void) const { return mVrboxInfo; }
    virtual void setVrboxcolInfo(stage_vrboxcol_info_class* i_VrboxcolInfo) { mVrboxcolInfo = i_VrboxcolInfo; }
    virtual stage_vrboxcol_info_class* getVrboxcolInfo(void) const { return mVrboxcolInfo; }
    virtual void setPlightInfo(stage_plight_info_class* i_PlightInfo) { mPlightInfo = i_PlightInfo; }
    virtual stage_plight_info_class* getPlightInfo(void) const { return mPlightInfo; }
    virtual void setPaletteNumInfo(int i_PaletteNumInfo) { mPaletteNumInfo = i_PaletteNumInfo; }
    virtual int getPaletteNumInfo(void) const { return mPaletteNumInfo; }
    virtual void setPselectNumInfo(int i_PselectNumInfo) { mPselectNumInfo = i_PselectNumInfo; }
    virtual int getPselectNumInfo(void) const { return mPselectNumInfo; }
    virtual void setEnvrNumInfo(int i_EnvrNumInfo) { mEnvrNumInfo = i_EnvrNumInfo; }
    virtual int getEnvrNumInfo(void) const { return mEnvrNumInfo; }
    virtual void setVrboxNumInfo(int i_VrboxNumInfo) { mVrboxNumInfo = i_VrboxNumInfo; }
    virtual int getVrboxNumInfo(void) const { return mVrboxNumInfo; }
    virtual void setVrboxcolNumInfo(int i_VrboxcolNumInfo) { mVrboxcolNumInfo = i_VrboxcolNumInfo; }
    virtual int getVrboxcolNumInfo(void) const { return mVrboxcolNumInfo; }
    virtual void setLightVecInfo(stage_pure_lightvec_info_class* i_LightVecInfo) { dStage_SetErrorStage(); }
    virtual stage_pure_lightvec_info_class* getLightVecInfo(void) const { return NULL; }
    virtual void setLightVecInfoNum(int i_LightVecInfoNum) {  dStage_SetErrorStage(); }
    virtual int getLightVecInfoNum(void) const { return NULL; }
    virtual void setPlightNumInfo(int i_PlightNumInfo) { mPlightNumInfo = i_PlightNumInfo; }
    virtual int getPlightNumInfo(void) const { return mPlightNumInfo; }
    virtual void setStagInfo(stage_stag_info_class* i_StagInfo) { mStagInfo = i_StagInfo; }
    virtual stage_stag_info_class* getStagInfo(void) const { return mStagInfo; }
    virtual void setSclsInfo(stage_scls_info_dummy_class* i_SclsInfo) { mSclsInfo = i_SclsInfo; }
    virtual stage_scls_info_dummy_class* getSclsInfo(void) const { return mSclsInfo; }
    virtual void setPntInfo(dStage_dPnt_c* i_PntInfo) { mPntInfo = i_PntInfo; }
    virtual dStage_dPnt_c* getPntInf(void) const { return mPntInfo; }
    virtual void setPathInfo(dStage_dPath_c* i_PathInfo) { mPathInfo = i_PathInfo; }
    virtual dStage_dPath_c* getPathInf(void) const { return mPathInfo; }
    virtual void setPnt2Info(dStage_dPnt_c* i_Pnt2Info) { mPnt2Info = i_Pnt2Info; }
    virtual dStage_dPnt_c* getPnt2Inf(void) const { return mPnt2Info; }
    virtual void setPath2Info(dStage_dPath_c* i_Path2Info) { mPath2Info = i_Path2Info; }
    virtual dStage_dPath_c* getPath2Inf(void) const { return mPath2Info; }
    virtual void setSoundInf(dStage_SoundInfo_c* i_SoundInf) { mSoundInf = i_SoundInf; }
    virtual dStage_SoundInfo_c* getSoundInf(void) const { return mSoundInf; }
    virtual void setSoundInfCL(dStage_SoundInfo_c* i_SoundInfCL) { mSoundInfCL = i_SoundInfCL; }
    virtual dStage_SoundInfo_c* getSoundInfCL(void) const { return mSoundInfCL; }
    virtual void setMapEventInfo(dStage_MapEventInfo_c* i_MapEventInfo) { mMapEventInfo = i_MapEventInfo; }
    virtual dStage_MapEventInfo_c* getMapEventInfo(void) const { return mMapEventInfo; }
    virtual void setFileList2Info(dStage_FileList2_dt_c* list) { dStage_SetErrorStage(); }
    virtual dStage_FileList2_dt_c* getFileList2Info(void) const { return NULL; }
    virtual void setFileListInfo(dStage_FileList_dt_c* list) { dStage_SetErrorStage(); }
    virtual dStage_FileList_dt_c* getFileListInfo(void) const { return NULL; }
    virtual void setFloorInfo(dStage_FloorInfo_c* i_FloorInfo) { mFloorInfo = i_FloorInfo; }
    virtual dStage_FloorInfo_c* getFloorInfo(void) const { return mFloorInfo; }
    virtual void setMemoryConfig(dStage_MemoryConfig_c* i_MemoryConfig) { mMemoryConfig = i_MemoryConfig; }
    virtual dStage_MemoryConfig_c* getMemoryConfig(void) const { return mMemoryConfig; }
    virtual void setMemoryMap(dStage_MemoryMap_c* i_MemoryMap) { mMemoryMap = i_MemoryMap; }
    virtual dStage_MemoryMap_c* getMemoryMap(void) const { return mMemoryMap; }
    virtual void setMulti(dStage_Multi_c* i_Multi) { mMulti = i_Multi; }
    virtual dStage_Multi_c* getMulti(void) const { return mMulti; }
    virtual void setOldMulti(void);
    virtual void resetOldMulti(void);
    virtual dStage_Multi_c* getOldMulti(void) const { return mOldMulti; }
    virtual void setLbnk(dStage_Lbnk_c* lbnk) { dStage_SetErrorStage(); }
    virtual dStage_Lbnk_c* getLbnk(void) const { return NULL; }
    virtual void setTresure(stage_tresure_class* i_Tresure) { mTresure = i_Tresure; }
    virtual stage_tresure_class* getTresure(void) const { return mTresure; }
    virtual void setDMap(dStage_DMap_c* i_DMap) { mDMap = i_DMap; }
    virtual dStage_DMap_c* getDMap(void) const { return mDMap; }
    virtual void setDrTg(stage_tgsc_class* i_DrTg) { mDrTg = i_DrTg; }
    virtual stage_tgsc_class* getDrTg(void) const { return mDrTg; }
    virtual void setDoor(stage_tgsc_class* i_Door) { mDoor = i_Door; }
    virtual stage_tgsc_class* getDoor(void) const { return mDoor; }
    virtual void setMapPath(void* i_MapPath) { return; }
    virtual void* getMapPath(void) { return NULL; }
    virtual void setElst(dStage_Elst_c* i_Elst) { mElst = i_Elst; }
    virtual dStage_Elst_c* getElst(void);

    s16 getWorldRollAngleX() const { return (s16)mWorldRollAngleX; }
    s16 getWorldRollDirAngleY() const { return mWorldRollDirAngleY; }

public:
    stage_camera_class* mCamera;
    stage_arrow_class* mArrow;
    stage_actor_class* mPlayer;
    roomRead_class* mRoom;
    stage_map_info_class* mMapInfo;
    stage_map_info_dummy_class* mMapInfoBase;
    stage_palette_info_class* mPaletteInfo;
    stage_pselect_info_class* mPselectInfo;
    stage_envr_info_class* mEnvrInfo;
    stage_vrbox_info_class* mVrboxInfo;
    stage_vrboxcol_info_class* mVrboxcolInfo;
    stage_plight_info_class* mPlightInfo;
    dStage_MapEventInfo_c* mMapEventInfo;
    u32 mPaletteNumInfo;
    u32 mPselectNumInfo;
    u32 mEnvrNumInfo;
    u32 mVrboxNumInfo;
    int mVrboxcolNumInfo;
    u32 mPlightNumInfo;
    u16 mPlayerNum;
    s16 mWorldRollAngleX;
    s16 mWorldRollDirAngleY;
    u16 field_0x5a;
    stage_stag_info_class* mStagInfo;
    stage_scls_info_dummy_class* mSclsInfo;
    dStage_dPnt_c* mPntInfo;
    dStage_dPath_c* mPathInfo;
    dStage_dPnt_c* mPnt2Info;
    dStage_dPath_c* mPath2Info;
    dStage_SoundInfo_c* mSoundInf;
    dStage_SoundInfo_c* mSoundInfCL;
    dStage_FloorInfo_c* mFloorInfo;
    dStage_MemoryConfig_c* mMemoryConfig;
    dStage_MemoryMap_c* mMemoryMap;
    dStage_Multi_c* mMulti;
    dStage_Multi_c* mOldMulti;
    stage_tresure_class* mTresure;
    dStage_DMap_c* mDMap;
    stage_tgsc_class* mDrTg;
    stage_tgsc_class* mDoor;
    dStage_Elst_c* mElst;
};

class dStage_roomDt_c : public dStage_dt_c {
public:
    dStage_roomDt_c() {}
    void initFileList2(void);

    virtual void init(void);
    virtual void setCamera(stage_camera_class* i_Camera) { mCamera = i_Camera; }
    virtual stage_camera_class* getCamera(void) const { return mCamera; }
    virtual void setArrow(stage_arrow_class* i_Arrow) { mArrow = i_Arrow; }
    virtual stage_arrow_class* getArrow(void) const { return mArrow; }
    virtual void setPlayer(stage_actor_class* i_Player) { mPlayer = i_Player; }
    virtual stage_actor_class* getPlayer(void) const { return mPlayer; }
    virtual void setPlayerNum(u16 i_PlayerNum) { mPlayerNum = i_PlayerNum; }
    virtual u16 getPlayerNum(void) const { return mPlayerNum; }
    /* virtual void setRoom(roomRead_class* i_Room) { dStage_SetErrorRoom(); }
    virtual roomRead_class* getRoom(void) const { return NULL; } */
    virtual void setMapInfo(stage_map_info_class* i_MapInfo) { mMapInfo = i_MapInfo; }
    virtual stage_map_info_class* getMapInfo(void) const { return mMapInfo; }
    virtual stage_map_info_class* getMapInfo2(int) const;
    virtual void setMapInfoBase(stage_map_info_dummy_class* i_MapInfoBase) { mMapInfoBase = i_MapInfoBase; }
    virtual stage_map_info_dummy_class* getMapInfoBase(void) const { return mMapInfoBase; }
    virtual void setPaletteInfo(stage_palette_info_class* i_PaletteInfo) { dStage_SetErrorRoom(); }
    virtual stage_palette_info_class* getPaletteInfo(void) const { return NULL; }
    virtual void setPselectInfo(stage_pselect_info_class* i_PselectInfo) { dStage_SetErrorRoom(); }
    virtual stage_pselect_info_class* getPselectInfo(void) const { return NULL; }
    virtual void setEnvrInfo(stage_envr_info_class* i_EnvrInfo) { dStage_SetErrorRoom(); }
    virtual stage_envr_info_class* getEnvrInfo(void) const { return NULL; }
    virtual void setVrboxInfo(stage_vrbox_info_class* i_VrboxInfo) { mVrboxInfo = i_VrboxInfo; }
    virtual stage_vrbox_info_class* getVrboxInfo(void) const { return mVrboxInfo; }
    virtual void setVrboxcolInfo(stage_vrboxcol_info_class* i_VrboxcolInfo) { mVrboxcolInfo = i_VrboxcolInfo; }
    virtual stage_vrboxcol_info_class* getVrboxcolInfo(void) const { return mVrboxcolInfo; }
    virtual void setPlightInfo(stage_plight_info_class* i_PlightInfo) { dStage_SetErrorRoom(); }
    virtual stage_plight_info_class* getPlightInfo(void) const { return NULL; }
    virtual void setPaletteNumInfo(int i_PaletteNumInfo) { dStage_SetErrorRoom(); }
    virtual int getPaletteNumInfo(void) const { return NULL; }
    virtual void setPselectNumInfo(int i_PselectNumInfo) { dStage_SetErrorRoom(); }
    virtual int getPselectNumInfo(void) const { return NULL; }
    virtual void setEnvrNumInfo(int i_EnvrNumInfo) { dStage_SetErrorRoom(); }
    virtual int getEnvrNumInfo(void) const { return NULL; }
    virtual void setVrboxNumInfo(int i_VrboxNumInfo) { mVrboxNumInfo = i_VrboxNumInfo; }
    virtual int getVrboxNumInfo(void) const { return mVrboxNumInfo; }
    virtual void setVrboxcolNumInfo(int i_VrboxcolNumInfo) { mVrboxcolNumInfo = i_VrboxcolNumInfo; }
    virtual int getVrboxcolNumInfo(void) const { return mVrboxcolNumInfo; }
    virtual void setPlightNumInfo(int i_PlightNumInfo) { dStage_SetErrorRoom(); }
    virtual int getPlightNumInfo(void) const { return NULL; }
    virtual void setLightVecInfo(stage_pure_lightvec_info_class* i_LightVecInfo) { mLightVecInfo = i_LightVecInfo; }
    virtual stage_pure_lightvec_info_class* getLightVecInfo(void) const { return mLightVecInfo; }
    virtual void setLightVecInfoNum(int i_LightVecInfoNum) { mLightVecInfoNum = i_LightVecInfoNum; }
    virtual int getLightVecInfoNum(void) const { return mLightVecInfoNum; }
    virtual void setStagInfo(stage_stag_info_class* i_StagInfo) { dStage_SetErrorRoom(); }
    virtual stage_stag_info_class* getStagInfo(void) const { return NULL; }
    virtual void setSclsInfo(stage_scls_info_dummy_class* i_SclsInfo) { mSclsInfo = i_SclsInfo; }
    virtual stage_scls_info_dummy_class* getSclsInfo(void) const { return mSclsInfo; }
    virtual void setPntInfo(dStage_dPnt_c* i_PntInfo) { dStage_SetErrorRoom(); }
    virtual dStage_dPnt_c* getPntInf(void) const { return NULL; }
    virtual void setPathInfo(dStage_dPath_c* i_PathInfo) { dStage_SetErrorRoom(); }
    virtual dStage_dPath_c* getPathInf(void) const { return NULL; }
    virtual void setPnt2Info(dStage_dPnt_c* i_Pnt2Info) { mPnt2Info = i_Pnt2Info; }
    virtual dStage_dPnt_c* getPnt2Inf(void) const { return mPnt2Info; }
    virtual void setPath2Info(dStage_dPath_c* i_Path2Info) { mPath2Info = i_Path2Info; }
    virtual dStage_dPath_c* getPath2Inf(void) const { return mPath2Info; }
    virtual void setSoundInf(dStage_SoundInfo_c* i_SoundInf) { mSoundInf = i_SoundInf; }
    virtual dStage_SoundInfo_c* getSoundInf(void) const { return mSoundInf; }
    virtual void setSoundInfCL(dStage_SoundInfo_c* i_SoundInfCL) { mSoundInfCL = i_SoundInfCL; }
    virtual dStage_SoundInfo_c* getSoundInfCL(void) const { return mSoundInfCL; }
    virtual void setMapEventInfo(dStage_MapEventInfo_c* i_MapEventInfo) { mMapEventInfo = i_MapEventInfo; }
    virtual dStage_MapEventInfo_c* getMapEventInfo(void) const { return mMapEventInfo; }
    virtual void setFileList2Info(dStage_FileList2_dt_c* i_FileList2Info) { mFileList2Info = i_FileList2Info; }
    virtual dStage_FileList2_dt_c* getFileList2Info(void) const { return mFileList2Info; }
    virtual void setFileListInfo(dStage_FileList_dt_c* i_FileListInfo) { mFileListInfo = i_FileListInfo; }
    virtual dStage_FileList_dt_c* getFileListInfo(void) const { return mFileListInfo; }
    virtual void setFloorInfo(dStage_FloorInfo_c* i_FloorInfo) { mFloorInfo = i_FloorInfo; }
    virtual dStage_FloorInfo_c* getFloorInfo(void) const { return mFloorInfo; }
    virtual void setMemoryConfig(dStage_MemoryConfig_c* i_MemoryConfig) {}
    virtual dStage_MemoryConfig_c* getMemoryConfig(void) const { return NULL; }
    virtual void setMemoryMap(dStage_MemoryMap_c* i_MemoryMap) {}
    virtual dStage_MemoryMap_c* getMemoryMap(void) const { return NULL; }
    virtual void setMulti(dStage_Multi_c* i_Multi) {}
    virtual dStage_Multi_c* getMulti(void) const { return NULL; }
    virtual void setOldMulti(void) {}
    virtual void resetOldMulti(void) {}
    virtual dStage_Multi_c* getOldMulti(void) const { return NULL; }
    virtual void setLbnk(dStage_Lbnk_c* i_Lbnk) { mLbnk = i_Lbnk; }
    virtual dStage_Lbnk_c* getLbnk(void) const { return mLbnk; }
    virtual void setTresure(stage_tresure_class* i_Tresure) { mTresure = i_Tresure; }
    virtual stage_tresure_class* getTresure(void) const { return mTresure; }
    virtual void setDMap(dStage_DMap_c* i_DMap) {}
    virtual dStage_DMap_c* getDMap(void) const { return NULL; }
    virtual void setDrTg(stage_tgsc_class* i_DrTg) { mDrTg = i_DrTg; }
    virtual stage_tgsc_class* getDrTg(void) const { return mDrTg; }
    virtual void setDoor(stage_tgsc_class* i_Door) { mDoor = i_Door; }
    virtual stage_tgsc_class* getDoor(void) const { return mDoor; }
    virtual void setMapPath(void* i_MapPath) {}
    virtual void* getMapPath(void) { return NULL; }
    virtual void setElst(dStage_Elst_c* i_Elst) { dStage_SetErrorRoom(); }
    virtual dStage_Elst_c* getElst(void) { dStage_SetErrorRoom(); return NULL; }

public:
    stage_pure_lightvec_info_class* mLightVecInfo;
    int mLightVecInfoNum;
    stage_map_info_class* mMapInfo;
    stage_map_info_dummy_class* mMapInfoBase;
    stage_vrbox_info_class* mVrboxInfo;
    stage_vrboxcol_info_class* mVrboxcolInfo;
    dStage_FileList2_dt_c* mFileList2Info;
    dStage_FileList_dt_c* mFileListInfo;
    stage_actor_class* mPlayer;
    dStage_dPnt_c* mPnt2Info;
    dStage_dPath_c* mPath2Info;
    stage_camera_class* mCamera;
    stage_arrow_class* mArrow;
    dStage_MapEventInfo_c* mMapEventInfo;
    dStage_SoundInfo_c* mSoundInf;
    dStage_SoundInfo_c* mSoundInfCL;
    stage_scls_info_dummy_class* mSclsInfo;
    dStage_Lbnk_c* mLbnk;
    stage_tresure_class* mTresure;
    stage_tgsc_class* mDrTg;
    stage_tgsc_class* mDoor;
    dStage_FloorInfo_c* mFloorInfo;
    u16 mPlayerNum;
    u16 field_0x62;
    int mVrboxNumInfo;
    int mVrboxcolNumInfo;
};

class dStage_roomStatus_c {
public:
    dStage_roomDt_c mRoomDt;
    // dKy_tevstr_c mKyTevStr;
    u8 mFlag;
    bool mDraw;
    s8 mZoneCount;
    s8 mZoneNo;
    s8 mMemBlockID;
    u8 mRegionNo;
    int mProcID;
    // dBgW_Base* mpBgW;

    int getZoneNo() const { return mZoneNo; }
};

class dStage_roomControl_c {
public:
    class roomDzs_c {
    public:
        roomDzs_c() { m_num = 0; }
        void create(u8);
        void remove();
        void* add(u8, u8);

        u8 m_num;
        void** m_dzs;
    };

    struct nameData {
        s8 m_num;
        char m_names[32][10];
    };

    struct bankDataEntry {
        u8 field_0x0;
        u8 mLayerNo;
        u8 field_0x2[0x20];
    };

    struct bankData {
        u8 m_num;
        bankDataEntry m_entries[32];
    };

    static void createRoomDzs(u8 i_num) { m_roomDzs.create(i_num); }
    static void* addRoomDzs(u8 i_num, u8 roomNo) { return m_roomDzs.add(i_num, roomNo); }
    static void removeRoomDzs() { m_roomDzs.remove(); }

    dStage_roomControl_c() {}
    void init(void);
    static int getZoneNo(int i_roomNo) { return mStatus[i_roomNo].getZoneNo(); }
    void initZone();
    dStage_roomDt_c* getStatusRoomDt(int);
    static JKRExpHeap* getMemoryBlock(int);
    static void setStayNo(int);
    static void setNextStayNo(int);
    BOOL checkRoomDisp(int) const;
    int loadRoom(int, u8*, bool);
    void zoneCountCheck(int) const;
    static JKRExpHeap* createMemoryBlock(int, u32);
    static void destroyMemoryBlock();
    static void setArcBank(int, char const*);
    static char* getArcBank(int);
    static bool resetArchiveBank(int);
    static void SetTimePass(int i_TimePass) { m_time_pass = i_TimePass; }
    static void setZoneNo(int, int);
    // static dBgp_c* getBgp(int i_roomNo) { return NULL; }
    static BOOL GetTimePass() { return m_time_pass; }

    static int getStayNo() { return mStayNo; }
    static u8 getRegionNo(int i_roomNo) { return mStatus[i_roomNo].mRegionNo; }
    static s8 getMemoryBlockID(int i_roomNo) { return mStatus[i_roomNo].mMemBlockID; }
    // dKy_tevstr_c* getTevStr(int i_roomNo) { return &mStatus[i_roomNo].mKyTevStr; }
    void setStatusFlag(int i_roomNo, u8 flag) { mStatus[i_roomNo].mFlag = flag; }
    static void onStatusDraw(int i_roomNo) { mStatus[i_roomNo].mDraw = true; }
    static dStage_FileList2_dt_c* getFileList2(int i_roomNo) { return mStatus[i_roomNo].mRoomDt.mFileList2Info; }
    static char* getDemoArcName() { return mDemoArcName; }
    static nameData* getArcBankName() { return mArcBankName; }
    static bankData* getArcBankData() { return mArcBankData; }
    static void setRoomReadId(s8 id) { mRoomReadId = id; }
    static s8 getRoomReadId() { return mRoomReadId; }
    static void offNoChangeRoom() { mNoChangeRoom = false; }
    static void onNoChangeRoom() { mNoChangeRoom = true; }
    static int getNextStayNo() { return mNextStayNo; }
    static void setProcID(u32 id) { mProcID = id; }
    static u32 getProcID() { return mProcID; }
    // static void setStatusProcID(int i_roomNo, fpc_ProcID i_id) { mStatus[i_roomNo].mProcID = i_id; }
    static int getStatusProcID(int i_roomNo) { return mStatus[i_roomNo].mProcID; }
    static void setRegionNo(int i_roomNo, u8 i_regionNo) { mStatus[i_roomNo].mRegionNo = i_regionNo; }
    u8 checkStatusFlag(int i_roomNo, u8 flag) const { return cLib_checkBit((u8) mStatus[i_roomNo].mFlag, flag); }
    void onStatusFlag(int i_roomNo, u8 flag) { return cLib_onBit(mStatus[i_roomNo].mFlag, flag); }
    void offStatusFlag(int i_roomNo, u8 flag) { return cLib_offBit(mStatus[i_roomNo].mFlag, flag); }
    static void setFileList2(int i_roomNo, dStage_FileList2_dt_c* list) { mStatus[i_roomNo].mRoomDt.setFileList2Info(list); }
    static void setZoneCount(int i_roomNo, int count) { mStatus[i_roomNo].mZoneCount = count; }
    static void setMemoryBlockID(int i_roomNo, int i_blockID) { mStatus[i_roomNo].mMemBlockID = i_blockID; }
    // static void setBgW(int i_roomNo, dBgW_Base* i_bgw) { mStatus[i_roomNo].mpBgW = i_bgw; }
    static JKRExpHeap* getMemoryBlockHeap(int i_no) { return mMemoryBlock[i_no]; }
    static const int MEMORY_BLOCK_MAX = 19;

    static JKRExpHeap* mMemoryBlock[MEMORY_BLOCK_MAX];
    static char mArcBank[32][10];
    static dStage_roomStatus_c mStatus[0x40];
    static char mDemoArcName[10];
    static u32 mProcID;
    static nameData* mArcBankName;
    static bankData* mArcBankData;
    static roomDzs_c m_roomDzs;
    static s8 mStayNo;
    static s8 mOldStayNo;
    static s8 mNextStayNo;
    static u8 m_time_pass;
    static u8 mNoChangeRoom;
    static s8 mRoomReadId;

private:
    u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    void set(const char*, s8, s16, s8);
    const char* getName() const { return mName; }
    s16 getPoint() const { return mPoint; }
    s8 getRoomNo() const { return mRoomNo; }
    s8 getLayer() const { return mLayer; }
    void setLayer(s8 layer) { mLayer = layer; }
    s8 getDarkArea() const { return mDarkArea; }
    void setDarkArea(s8 darkArea) { mDarkArea = darkArea; }

private:
    char mName[8];
    s16 mPoint;
    s8 mRoomNo;
    s8 mLayer;
    s8 mDarkArea;
};

class dStage_nextStage_c : public dStage_startStage_c {
public:
    dStage_nextStage_c() {
        enabled = 0;
    }
    void set(const char*, s8, s16, s8, s8, u8);
    void offEnable() { enabled = 0; }
    BOOL isEnable() const { return enabled; }
    s8 getWipe() const { return wipe; }
    u8 getWipeSpeed() const { return wipe_speed; }
    dStage_startStage_c* getStartStage() { return this; }

private:
    s8 enabled;
    s8 wipe;
    u8 wipe_speed;
};