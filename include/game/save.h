#include <cstring>

#include "ssystem/scomponent/c_xyz.h"

// TODO: Used by header but not originally included directly
#include <dolphin/types.h>

static const int MAX_SELECT_ITEM = 4;
static const int MAX_EQUIPMENT = 6;

enum CollectItem {
    /* 0x0 */ COLLECT_CLOTHING,
    /* 0x1 */ COLLECT_SWORD,
    /* 0x2 */ COLLECT_SHIELD,
    /* 0x3 */ COLLECT_SMELL,
    /* 0x4 */ B_BUTTON_ITEM
};

enum Swords {
    /* 0x0 */ COLLECT_ORDON_SWORD,
    /* 0x1 */ COLLECT_MASTER_SWORD,
    /* 0x2 */ COLLECT_WOODEN_SWORD,
    /* 0x3 */ COLLECT_LIGHT_SWORD
};

enum Shields {
    /* 0x0 */ COLLECT_WOODEN_SHIELD,
    /* 0x1 */ COLLECT_ORDON_SHIELD,
    /* 0x2 */ COLLECT_HYLIAN_SHIELD
};

enum ItemMax {
    /* 0x0 */ ARROW_MAX,
    /* 0x1 */ NORMAL_BOMB_MAX,
    /* 0x2 */ WATER_BOMB_MAX,
    /* 0x6 */ POKE_BOMB_MAX = 6
};

class dSv_player_status_a_c {
public:
    void init();
    void setSelectItemIndex(int i_no, u8 i_slotNo);
    u8 getSelectItemIndex(int i_no) const;
    void setMixItemIndex(int i_no, u8 i_slotNo);
    u8 getMixItemIndex(int i_no) const;
    u16 getRupeeMax() const;
    void onMagicFlag(u8 i_magic);
    void offMagicFlag(u8 i_magic);
    int isMagicFlag(u8 i_magic) const;

    u16 getMaxLife() const { return mMaxLife; }
    u16 getLife() const { return mLife; }
    u16 getRupee() const { return mRupee; }
    u16 getOil() const { return mOil; }
    u16 getMaxOil() const { return mMaxOil; }
    u8 getMagic() const { return mMagic; }
    u8 getMaxMagic() const { return mMaxMagic; }
    u8 getSelectEquip(int item) const { return mSelectEquip[item]; }
    u8 getTransformStatus() const { return mTransformStatus; }
    u8 getWalletSize() const { return mWalletSize; }
    void setOil(u16 i_oil) { mOil = i_oil; }
    void setMaxOil(u16 i_maxOil) { mMaxOil = i_maxOil; }
    void setWalletSize(u8 i_size) { mWalletSize = i_size; }
    void setMagic(u8 i_magic) { mMagic = i_magic; }
    void setMaxMagic(u8 i_maxMagic) { mMaxMagic = i_maxMagic; }
    void setRupee(u16 i_rupees) { mRupee = i_rupees; }
    void setLife(u16 i_life) { mLife = i_life; }
    void setMaxLife(u8 i_maxLife) { mMaxLife = i_maxLife; }
    void setSelectEquip(int i_equipId, u8 i_itemNo) { mSelectEquip[i_equipId] = i_itemNo; }
    void setTransformStatus(u8 i_status) { mTransformStatus = i_status; }

private:
    u16 mMaxLife;
    u16 mLife;
    u16 mRupee;
    u16 mMaxOil;
    u16 mOil;
    u8 unk10;
    u8 mSelectItem[MAX_SELECT_ITEM];
    u8 mMixItem[MAX_SELECT_ITEM];
    u8 mSelectEquip[MAX_EQUIPMENT];
    u8 mWalletSize;
    u8 mMaxMagic;
    u8 mMagic;
    u8 mMagicFlag;
    u8 unk29;
    u8 mTransformStatus;
    u8 unk31[3];
};

class dSv_player_status_b_c {
public:
    void init();
    void onDarkClearLV(int i_no);
    void offDarkClearLV(int i_no);
    BOOL isDarkClearLV(int i_no) const;
    void onTransformLV(int i_no);
    void offTransformLV(int i_no);
    BOOL isTransformLV(int i_no) const;

    // void setDateIpl(s64 i_time) { mDateIpl = i_time; }
    u16 getDate() const { return mDate; }
    f32 getTime() const { return mTime; }
    void setDate(u16 i_date) { mDate = i_date; }
    void setTime(f32 i_time) { mTime = i_time; }
    // OSTime getDateIpl() const { return mDateIpl; }

private:
    // OSTime mDateIpl;
    u8 mTransformLevelFlag;
    u8 mDarkClearLevelFlag;
    u8 unk10;
    u8 unk11;
    f32 mTime;
    u16 mDate;
    u8 unk18[3];
};

class dSv_player_return_place_c {
public:
    void init();
    void set(const char* i_name, s8 i_roomNo, u8 i_status);
    s8 getRoomNo() const { return mRoomNo; }
    u8 getPlayerStatus() const { return mPlayerStatus; }
    char* getName() { return mName; }

private:
    char mName[8];
    u8 mPlayerStatus;
    s8 mRoomNo;
    u8 unk10;
    u8 unk11;
};

class dSv_player_field_last_stay_info_c {
public:
    dSv_player_field_last_stay_info_c() {}

    void init();
    BOOL isRegionBit(int i_region) const;
    void onRegionBit(int i_region);
    void set(const char* i_name, const cXyz& i_pos, s16 i_angle, s8 i_spawn, u8 i_regionNo);

    bool isFieldDataExistFlag() const { return mFieldDataExistFlag; }
    void offFieldDataExistFlag() { mFieldDataExistFlag = false; }
    void onFieldDataExistFlag() { mFieldDataExistFlag = true; }
    cXyz& getPos() { return mPos; }
    u8 getRegionNo() const { return mRegionNo; }
    char* getName() { return mName; }
    s16 getAngleY() { return mAngleY; }

private:
    cXyz mPos;
    s16 mAngleY;
    char mName[8];
    s8 mLastSpawnId;
    u8 mRegionNo;
    bool mFieldDataExistFlag;
    u8 mRegion;
    u8 unk26[2];
};

class dSv_player_last_mark_info_c {
public:
    dSv_player_last_mark_info_c() {}

    void init();
    void setWarpItemData(const char* i_name, const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u8, u8);

    const char* getName() { return mName; }
    cXyz& getPos() { return mPos; }
    s16 getAngleY() { return mAngleY; }
    s8 getRoomNo() { return mRoomNo; }
    s8 getWarpAcceptStage() { return mWarpAcceptStage; }
    void resetWarpAcceptStage() { mWarpAcceptStage = -1; }
    void setWarpAcceptStage(s8 accept) { mWarpAcceptStage = accept; }

private:
    cXyz mPos;
    s16 mAngleY;
    char mName[8];
    u8 mSpawnId;
    s8 mRoomNo;
    s8 mWarpAcceptStage;
    u8 unk25[3];
};

class dSv_player_item_c {
public:
    void init();
    void setItem(int i_slotNo, u8 i_itemNo);
    u8 getItem(int i_slotNo, bool i_checkCombo) const;
    void setLineUpItem();
    u8 getLineUpItem(int i_slotNo) const;
    void setBottleItemIn(u8 curItemIn, u8 newItemIn);
    void setEmptyBottleItemIn(u8 i_itemNo);
    void setEmptyBottle();
    void setEmptyBottle(u8 i_itemNo);
    void setEquipBottleItemIn(u8 curItemIn, u8 newItemIn);
    void setEquipBottleItemEmpty(u8 curItemIn);
    u8 checkBottle(u8 i_itemNo);
    int checkInsectBottle();
    u8 checkEmptyBottle();
    void setBombBagItemIn(u8 i_curBomb, u8 i_newBomb, bool i_setNum);
    void setBombBagItemIn(u8 i_curBomb, u8 i_newBomb, u8 i_bombNum, bool i_setNum);
    void setEmptyBombBagItemIn(u8 i_newBomb, bool i_setNum);
    void setEmptyBombBagItemIn(u8 i_newBomb, u8 i_bombNum, bool i_setNum);
    void setEmptyBombBag();
    void setEmptyBombBag(u8 i_newBomb, u8 i_bombNum);
    u8 checkBombBag(u8 i_itemNo);
    void setWarashibeItem(u8 i_itemNo);
    void setRodTypeLevelUp();
    void setBaitItem(u8 i_itemNo);

    static const int BOMB_BAG_MAX = 3;
    static const int BOTTLE_MAX = 4;

private:
    u8 mItems[24];
    u8 mItemSlots[24];
};

class dSv_player_get_item_c {
public:
    void init();
    void onFirstBit(u8 i_itemNo);
    void offFirstBit(u8 i_itemNo);
    int isFirstBit(u8 i_itemNo) const;

private:
    u32 mItemFlags[8];
};

class dSv_player_item_record_c {
public:
    void init();
    void setBombNum(u8 i_bagIdx, u8 i_bombNum);
    u8 getBombNum(u8 i_bagIdx) const;
    void setBottleNum(u8 i_bottleIdx, u8 i_bottleNum);
    u8 addBottleNum(u8 i_bottleIdx, s16 i_num);
    u8 getBottleNum(u8 i_bottleIdx) const;

    u8 getArrowNum() const { return mArrowNum; }
    void setArrowNum(u8 i_num) { mArrowNum = i_num; }
    u8 getPachinkoNum() const { return mPachinkoNum; }
    void setPachinkoNum(u8 i_num) { mPachinkoNum = i_num; }

private:
    u8 mArrowNum;
    u8 mBombNum[3];
    u8 mBottleNum[4];
    u8 mPachinkoNum;
    u8 unk5[3];
};

class dSv_player_item_max_c {
public:
    void init();
    void setBombNum(u8 i_bombType, u8 i_maxNum);
    u8 getBombNum(u8 i_bombType) const;

    void setArrowNum(u8 i_maxNum) { mItemMax[ARROW_MAX] = i_maxNum; }
    u8 getArrowNum() const { return mItemMax[ARROW_MAX]; }

private:
    u8 mItemMax[8];
};

class dSv_player_collect_c {
public:
    void init();
    void setCollect(int i_item_type, u8 i_item);
    void offCollect(int i_item_type, u8 i_item);
    BOOL isCollect(int i_item_type, u8 i_item) const;
    void onCollectCrystal(u8 i_item);
    void offCollectCrystal(u8 i_item);
    BOOL isCollectCrystal(u8 i_item) const;
    void onCollectMirror(u8 i_item);
    void offCollectMirror(u8 i_item);
    BOOL isCollectMirror(u8 i_item) const;

    u8 getPohNum() const { return mPohNum; }
    void addPohNum() {
        if (mPohNum < 0xFF) {
            mPohNum += 1;
        }
    };

private:
    u8 mItem[8];
    u8 unk8;
    u8 mCrystal;
    u8 mMirror;
    u8 unk11;
    u8 mPohNum;
    u8 padding[3];
};

class dSv_player_wolf_c {
public:
    void init();

private:
    u8 unk0[3];
    u8 unk3;
};

class dSv_light_drop_c {
public:
    void init();
    void setLightDropNum(u8 i_nowLevel, u8 i_dropNum);
    u8 getLightDropNum(u8 i_nowLevel) const;
    void onLightDropGetFlag(u8 i_nowLevel);
    void offLightDropGetFlag(u8 i_nowLevel);
    BOOL isLightDropGetFlag(u8 i_nowLevel) const;

private:
    u8 mLightDropNum[4];
    u8 mLightDropGetFlag;
    u8 unk5[3];
};

class dSv_letter_info_c {
public:
    void init();
    void onLetterGetFlag(int i_no);
    BOOL isLetterGetFlag(int i_no) const;
    void onLetterReadFlag(int i_no);
    int isLetterReadFlag(int i_no) const;
    u8 getGetNumber(int i_no) { return mGetNumber[i_no]; }
    void setGetNumber(int i_no, u8 i_value) { mGetNumber[i_no] = i_value; }

private:
    u32 mLetterGetFlags[2];
    u32 mLetterReadFlags[2];
    u8 mGetNumber[64];
};

class dSv_fishing_info_c {
public:
    void init();
    void addFishCount(u8 i_fishIndex);
    u16 getFishCount(u8 i_fishIndex) const { return mFishCount[i_fishIndex]; }
    u8 getMaxSize(int i_sizeIndex) const { return mMaxSize[i_sizeIndex]; }
    void setMaxSize(int i_sizeIndex, u8 i_size) { mMaxSize[i_sizeIndex] = i_size; }

private:
    u16 mFishCount[16];
    u8 mMaxSize[16];
};

class dSv_player_info_c {
public:
    void init();
    char* getLinkName() { return mPlayerName; }
    const char* getPlayerName() const { return mPlayerName; }
    char* getHorseName() { return mHorseName; }
    void setPlayerName(const char* i_name) { strcpy((char*)mPlayerName, i_name); }
    void setHorseName(const char* i_name) { strcpy((char*)mHorseName, i_name); }
    void setTotalTime(s64 i_time) { mTotalTime = i_time; }
    s64 getTotalTime() const { return mTotalTime; }
    u8 getClearCount() const { return mClearCount; }

    void addDeathCount() {
        if (mDeathCount < 0xFFFF) {
            mDeathCount++;
        }
    }

private:
    u64 unk0;
    s64 mTotalTime;
    u16 unk16;
    u16 mDeathCount;
    char mPlayerName[16];
    u8 unk36;
    char mHorseName[16];
    u8 unk53;
    u8 mClearCount;
    u8 unk55[5];
};

class dSv_player_config_c {
public:
    void init();
    u32 checkVibration() const;
    u8 getSound();
    void setSound(u8 i_mode);
    u8 getVibration();
    void setVibration(u8 i_status);
    u8 getPalLanguage() const;

    u8 getRuby() { return mRuby; }
    void setRuby(u8 i_ruby) { mRuby = i_ruby; }
    u8 getAttentionType() { return mAttentionType; }
    void setAttentionType(u8 i_mAttentionType) { mAttentionType = i_mAttentionType; }
    u16 getCalibrateDist() { return mCalibrateDist; }
    void setCalibrateDist(u16 i_mCalibrateDist) { mCalibrateDist = i_mCalibrateDist; }
    u8 getCalValue() { return mCalValue; }
    void setCalValue(u8 i_mCalValue) { mCalValue = i_mCalValue; }
    bool getShortCut() { return mShortCut; }
    void setShortCut(bool i_mShortCut) { mShortCut = i_mShortCut; }
    u8 getCameraControl() { return mCameraControl; }
    void setCameraControl(u8 i_mCameraControl) { mCameraControl = i_mCameraControl; }
    bool getPointer() { return mPointer; }
    void setPointer(bool i_mPointer) { mPointer = i_mPointer; }

    enum dSv_config_language {
        LANGUAGE_ENGLISH,
        LANGUAGE_GERMAN,
        LANGUAGE_FRENCH,
        LANGUAGE_SPANISH,
        LANGUAGE_ITALIAN,
    };

private:
    u8 mRuby;
    u8 mSoundMode;
    u8 mAttentionType;
    u8 mVibration;
    u8 mLanguage;
    u8 unk5;
    u16 mCalibrateDist;
    u8 mCalValue;
    bool mShortCut;
    u8 mCameraControl;
    bool mPointer;
};

class dSv_player_c {
public:
    dSv_player_c() {}
    void init();

    dSv_player_info_c& getPlayerInfo() { return mPlayerInfo; }
    dSv_player_status_a_c& getPlayerStatusA() { return mPlayerStatusA; }
    dSv_player_status_b_c& getPlayerStatusB() { return mPlayerStatusB; }
    /* dSv_horse_place_c& getHorsePlace() { return mHorsePlace; }
    dSv_player_item_c& getItem() { return mItem; } */
    dSv_player_collect_c& getCollect() { return mCollect; }
    dSv_player_item_record_c& getItemRecord() { return mItemRecord; }
    dSv_player_item_max_c& getItemMax() { return mItemMax; }
    dSv_player_last_mark_info_c& getPlayerLastMarkInfo() { return mPlayerLastMarkInfo; }
    dSv_player_return_place_c& getPlayerReturnPlace() { return mPlayerReturnPlace; }
    dSv_light_drop_c& getLightDrop() { return mLightDrop; }
    dSv_player_get_item_c& getGetItem() { return mGetItem; }
    dSv_player_config_c& getConfig() { return mConfig; }
    dSv_letter_info_c& getLetterInfo() { return mLetterInfo; }
    dSv_fishing_info_c& getFishingInfo() { return mFishingInfo; }
    dSv_player_field_last_stay_info_c& getPlayerFieldLastStayInfo() {
        return mPlayerFieldLastStayInfo;
    }

private:
    dSv_player_status_a_c mPlayerStatusA;
    dSv_player_status_b_c mPlayerStatusB;
    // dSv_horse_place_c mHorsePlace;
    dSv_player_return_place_c mPlayerReturnPlace;
    dSv_player_field_last_stay_info_c mPlayerFieldLastStayInfo;
    dSv_player_last_mark_info_c mPlayerLastMarkInfo;
    dSv_player_item_c mItem;
    dSv_player_get_item_c mGetItem;
    dSv_player_item_record_c mItemRecord;
    dSv_player_item_max_c mItemMax;
    dSv_player_collect_c mCollect;
    dSv_player_wolf_c mWolf;
    dSv_light_drop_c mLightDrop;
    dSv_letter_info_c mLetterInfo;
    dSv_fishing_info_c mFishingInfo;
    dSv_player_info_c mPlayerInfo;
    dSv_player_config_c mConfig;
};

class dSv_memBit_c {
public:
    class WarpItemData_c {
    public:
        char mWarpItemStage[8];
        cXyz mWarpItemPos;
        s16 mWarpItemAngle;
        s8 mWarpItemRoom;
        u8 field_0x4fab; // related to setWarpItemData
        u8 field_0x4fac; // related to setWarpItemData
        u8 field_0x4fad[3];
    };

    enum {
        MAP,
        COMPASS,
        BOSS_KEY,
        STAGE_BOSS_ENEMY,
        STAGE_LIFE,
        STAGE_BOSS_DEMO,
        OOCCOO_NOTE,
        STAGE_BOSS_ENEMY_2
    };

    void init();
    void onTbox(int i_no);
    void offTbox(int i_no);
    BOOL isTbox(int i_no) const;
    void onSwitch(int i_no);
    void offSwitch(int i_no);
    BOOL isSwitch(int i_no) const;
    BOOL revSwitch(int i_no);
    void onItem(int i_no);
    void offItem(int i_no);
    BOOL isItem(int i_no) const;
    void onDungeonItem(int i_no);
    void offDungeonItem(int i_no);
    s32 isDungeonItem(int i_no) const;

    u8 getKeyNum() { return mKeyNum; }
    void setKeyNum(u8 i_keyNum) { mKeyNum = i_keyNum; }
    void onDungeonItemMap() { onDungeonItem(MAP); }
    s32 isDungeonItemMap() const { return isDungeonItem(MAP); }
    void onDungeonItemCompass() { onDungeonItem(COMPASS); }
    s32 isDungeonItemCompass() const { return isDungeonItem(COMPASS); }
    void onDungeonItemWarp() { onDungeonItem(OOCCOO_NOTE); }
    void onDungeonItemBossKey() { onDungeonItem(BOSS_KEY); }
    s32 isDungeonItemBossKey() const { return isDungeonItem(BOSS_KEY); }
    void onStageBossEnemy() {
        onDungeonItem(STAGE_BOSS_ENEMY);
        onDungeonItem(OOCCOO_NOTE);
    }
    void onStageBossEnemy2() { onDungeonItem(STAGE_BOSS_ENEMY_2); }
    s32 isStageBossEnemy() const { return isDungeonItem(STAGE_BOSS_ENEMY); }
    s32 isStageBossEnemy2() const { return isDungeonItem(STAGE_BOSS_ENEMY_2); }
    s32 isStageLife() const { return isDungeonItem(STAGE_LIFE); }
    s32 isDungeonItemWarp() const { return isDungeonItem(OOCCOO_NOTE); }
    void onStageLife() { onDungeonItem(STAGE_LIFE); }

private:
    u32 mTbox[2];
    u32 mSwitch[4];
    u32 mItem[1];
    u8 mKeyNum;
    u8 mDungeonItem;
};

class dSv_event_c {
public:
    void init();
    void onEventBit(const u16 i_no);
    void offEventBit(const u16 i_no);
    int isEventBit(const u16 i_no) const;
    void setEventReg(u16 i_reg, u8 i_no);
    u8 getEventReg(u16 i_reg) const;

    void* getPEventBit() { return (void*)mEvent; }

private:
    u8 mEvent[256];
};

class dSv_MiniGame_c {
public:
    void init();

    void setBalloonScore(u32 i_score) { mBalloonScore = i_score; }
    void setRaceGameTime(u32 i_time) { mRaceGameTime = i_time; }
    void setHookGameTime(u32 i_time) { mHookGameTime = i_time; }

    u32 getRaceGameTime() const { return mRaceGameTime; }
    u32 getBalloonScore() const { return mBalloonScore; }
    u32 getHookGameTime() const { return mHookGameTime; }

private:
    u8 unk0[1][4];
    u32 mHookGameTime;
    u32 mBalloonScore;
    u32 mRaceGameTime;
    u32 unk16;
    u32 unk20;
};

class dSv_memory_c {
public:
    dSv_memory_c() { this->init(); }
    void init();
    dSv_memBit_c& getBit() { return mBit; }
    const dSv_memBit_c& getBit() const { return mBit; }

private:
    dSv_memBit_c mBit;
};

class dSv_memory2_c {
public:
    dSv_memory2_c() { this->init(); }
    void init();
    void onVisitedRoom(int i_no);
    void offVisitedRoom(int i_no);
    BOOL isVisitedRoom(int i_no);

private:
    u32 mVisitedRoom[2];
};

class dSv_danBit_c {
public:
    bool init(s8 i_stageNo);
    void onSwitch(int i_no);
    void offSwitch(int i_no);
    BOOL isSwitch(int i_no) const;
    BOOL revSwitch(int i_no);
    void onItem(int i_no);
    void offItem(int i_no);
    BOOL isItem(int i_no) const;

    void reset() { mStageNo = -1; }

private:
    s8 mStageNo;
    u8 unk1;
    u8 unk2[2];
    u32 mSwitch[2];
    u32 mItem[4];
    s16 unk28[16];
};

class dSv_zoneBit_c {
public:
    void init();
    void clearRoomSwitch();
    void clearRoomItem();
    void onSwitch(int i_no);
    void offSwitch(int i_no);
    BOOL isSwitch(int i_no) const;
    BOOL revSwitch(int i_no);
    void onOneSwitch(int i_no);
    void offOneSwitch(int i_no);
    BOOL isOneSwitch(int i_no) const;
    BOOL revOneSwitch(int i_no);
    void onItem(int i_no);
    void offItem(int i_no);
    BOOL isItem(int i_no) const;
    void onOneItem(int i_no);
    void offOneItem(int i_no);
    BOOL isOneItem(int i_no) const;

private:
    u16 mSwitch[2];
    u16 mRoomSwitch;
    u16 mItem[2];
    u16 mRoomItem;
    u16 unk12;
};

class dSv_zoneActor_c {
public:
    void init();
    void on(int i_id);
    void off(int i_id);
    BOOL is(int i_id) const;

    static const int ACTOR_MAX = 0x80;

private:
    u32 mActorFlags[4];
};

class dSv_zone_c {
public:
    dSv_zone_c() { mRoomNo = -1; }
    void init(int i_roomNo);

    dSv_zoneBit_c& getBit() { return mBit; }
    const dSv_zoneBit_c& getBit() const { return mBit; }
    dSv_zoneActor_c& getActor() { return mActor; }
    const dSv_zoneActor_c& getActor() const { return mActor; }

    int getRoomNo() const { return mRoomNo; }
    void reset() { mRoomNo = -1; }

private:
    s8 mRoomNo;
    u8 unk1;
    dSv_zoneBit_c mBit;
    dSv_zoneActor_c mActor;
};

class dSv_restart_c {
public:
    void setRoom(const cXyz& i_position, s16 i_angleY, s8 i_roomNo);

    void setRoomParam(u32 param) { mRoomParam = param; }
    void setStartPoint(s16 point) { mStartPoint = point; }
    void setLastSceneInfo(f32 speed, u32 mode, s16 angle) {
        mLastSpeedF = speed;
        mLastMode = mode;
        mLastAngleY = angle;
    }

    s16 getStartPoint() const { return mStartPoint; }
    u32 getLastMode() const { return mLastMode; }
    s8 getRoomNo() const { return mRoomNo; }
    u32 getRoomParam() const { return mRoomParam; }
    cXyz& getRoomPos() { return mRoomPos; }
    s16 getRoomAngleY() const { return mRoomAngleY; }
    s16 getLastAngleY() const { return mLastAngleY; }
    f32 getLastSpeedF() const { return mLastSpeedF; }

private:
    s8 mRoomNo;
    u8 field_0x01[3];
    s16 mStartPoint;
    s16 mRoomAngleY;
    cXyz mRoomPos;
    u32 mRoomParam;
    f32 mLastSpeedF;
    u32 mLastMode;
    s16 mLastAngleY;
};

class dSv_turnRestart_c {
public:
    class dSv_turnRestart_camera_c {
    public:
        cXyz mCameraCtr;
        cXyz mCameraEye;
        cXyz mCameraUp;
    };

    void set(const cXyz& i_position, s16 i_angleY, s8, u32 i_param);

    u32 getParam() const { return mParam; }
    cXyz& getPos() { return mPosition; }
    s16 getAngleY() const { return mAngleY; }
    s8 getRoomNo() const { return unk18; }

    f32 getCameraFvy() const { return mCameraFvy; }
    void setCameraFvy(f32 i_fvy) { mCameraFvy = i_fvy; }

    const cXyz& getCameraUp() const { return mCamera.mCameraUp; }
    const cXyz& getCameraEye() const { return mCamera.mCameraEye; }
    const cXyz& getCameraCtr() const { return mCamera.mCameraCtr; }

    void setCameraUp(const cXyz& i_up) { mCamera.mCameraUp = i_up; }
    void setCameraEye(const cXyz& i_eye) { mCamera.mCameraEye = i_eye; }
    void setCameraCtr(const cXyz& i_ctr) { mCamera.mCameraCtr = i_ctr; }

private:
    cXyz mPosition;
    u32 mParam;
    s16 mAngleY;
    s8 unk18;
    dSv_turnRestart_camera_c mCamera;
    f32 mCameraFvy;
};

class dSv_reserve_c {
public:
private:
    u8 unk[80];
};

class dSv_save_c {
public:
    dSv_save_c() {}

    void init();
    dSv_memory2_c* getSave2(int i_stage2No);

    dSv_player_c& getPlayer() { return mPlayer; } 
    dSv_event_c& getEvent() { return mEvent; }
    dSv_MiniGame_c& getMiniGame() { return mMiniGame; }

    dSv_memory_c& getSave(int i_stageNo) { return mSave[i_stageNo]; }

    void putSave(int i_stageNo, dSv_memory_c mem) { mSave[i_stageNo] = mem; }

    static const int STAGE_MAX = 32;
    static const int STAGE2_MAX = 64;

    // private:
    dSv_player_c mPlayer;
    dSv_memory_c mSave[STAGE_MAX];
    dSv_memory2_c mSave2[STAGE2_MAX];
    dSv_event_c mEvent;
    dSv_reserve_c reserve;
    dSv_MiniGame_c mMiniGame;
};

class dSv_info_c {
public:
    void init();
    void getSave(int i_stageNo);
    void putSave(int i_stageNo);
    void initZone();
    u32 createZone(int i_roomNo);
    void onSwitch(int i_no, int i_roomNo);
    void offSwitch(int i_no, int i_roomNo);
    BOOL isSwitch(int i_no, int i_roomNo) const;
    BOOL revSwitch(int i_no, int i_roomNo);
    void onItem(int i_no, int i_roomNo);
    BOOL isItem(int i_no, int i_roomNo) const;
    void onActor(int i_no, int i_roomNo);
    void offActor(int i_no, int i_roomNo);
    BOOL isActor(int i_no, int i_roomNo) const;
    int memory_to_card(char* card_ptr, int dataNum);
    int card_to_memory(char* card_ptr, int dataNum);
    int initdata_to_card(char* card_ptr, int dataNum);

    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_zone_c* getZones() { return mZone; }
    dSv_zone_c& getZone(int id) { return mZone[id]; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_event_c& getTmp() { return mTmp; }
    dSv_restart_c& getRestart() { return mRestart; }
    dSv_turnRestart_c& getTurnRestart() { return mTurnRestart; }
    dSv_event_c& getEvent() { return mSavedata.getEvent(); }
    dSv_danBit_c& getDan() { return mDan; }
    dSv_MiniGame_c& getMiniGame() { return mSavedata.getMiniGame(); }
    s64 getStartTime() const { return mStartTime; }
    s64 getSaveTotalTime() const { return mSaveTotalTime; }
    void setStartTime(s64 time) { mStartTime = time; }
    void setSaveTotalTime(s64 time) { mSaveTotalTime = time; }
    void initDan(s8 i_stage) { mDan.init(i_stage); }
    void resetDan() { mDan.reset(); }
    u8 getDataNum() const { return mDataNum; }
    void setDataNum(u8 num) { mDataNum = num; }
    void removeZone(int zoneNo) { mZone[zoneNo].reset(); }
    u8 getNoFile() const { return mNoFile; }
    void setNoFile(u8 file) { mNoFile = file; }
    u8 getNewFile() const { return mNewFile; }
    void setNewFile(u8 file) { mNewFile = file; }

    void setSavedata(dSv_save_c& i_save) { mSavedata = i_save; }
    void setMemory(dSv_memory_c& i_memory) { mMemory = i_memory; }
    void setDan(dSv_danBit_c& i_dan) { mDan = i_dan; }

    static const int MEMORY_SWITCH = 0x80;
    static const int DAN_SWITCH = 0x40;
    static const int ZONE_SWITCH = 0x20;
    static const int ONEZONE_SWITCH = 0x10;

    static const int MEMORY_ITEM = 0x80;
    static const int DAN_ITEM = 0x20;
    static const int ZONE_ITEM = 0x20;
    static const int ONEZONE_ITEM = 0x10;

    static const int ZONE_MAX = 0x20;

    dSv_save_c mSavedata;
    dSv_memory_c mMemory;
    dSv_danBit_c mDan;
    dSv_zone_c mZone[ZONE_MAX];
    dSv_restart_c mRestart;
    dSv_event_c mTmp;
    dSv_turnRestart_c mTurnRestart;
    u8 field_0xf14[4];
    u8 mDataNum;
    u8 mNewFile;
    u8 mNoFile;
    u8 field_0xf1b[13];
    s64 mStartTime;
    s64 mSaveTotalTime;
};