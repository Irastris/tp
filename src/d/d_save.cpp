#include "d/d_com_inf_game.h"
#include "d/d_save.h"

void dSv_player_status_a_c::init() {
    mMaxLife = 15;
    mLife = 12;
    mRupee = 0;
    mMaxOil = 0;
    mOil = 0;
    unk10 = 0;

    for (int i = 0; i < MAX_SELECT_ITEM; i++) {
        mSelectItem[i] = 0xFF;
        mMixItem[i] = 0xFF;
        dComIfGp_setSelectItem(i);
    }

    for (int i = 0; i < MAX_EQUIPMENT; i++) {
        mSelectEquip[i] = 0;
    }

    /* mSelectEquip[COLLECT_CLOTHING] = fpcNm_ITEM_WEAR_CASUAL;
    mSelectEquip[COLLECT_SWORD] = fpcNm_ITEM_NONE;
    mSelectEquip[COLLECT_SHIELD] = fpcNm_ITEM_NONE;
    mSelectEquip[COLLECT_SMELL] = fpcNm_ITEM_NONE;
    mSelectEquip[B_BUTTON_ITEM] = fpcNm_ITEM_NONE; */
    mWalletSize = WALLET;
    mMaxMagic = 0;
    mMagic = 0;
    mMagicFlag = 0;
    unk29 = 0;
    mTransformStatus = TF_STATUS_HUMAN;

    for (int i = 0; i < 3; i++) {
        unk31[i] = 0;
    }
}

void dSv_player_status_a_c::setSelectItemIndex(int i_no, u8 i_slotNo) {
    if (i_no < MAX_SELECT_ITEM) {
        mSelectItem[i_no] = i_slotNo;
    }
}

u8 dSv_player_status_a_c::getSelectItemIndex(int i_no) const {
    if (i_no < MAX_SELECT_ITEM) {
        return mSelectItem[i_no];
    }
    return 0;
}

void dSv_player_status_a_c::setMixItemIndex(int i_no, u8 i_slotNo) {
    if (i_no < MAX_SELECT_ITEM) {
        mMixItem[i_no] = i_slotNo;
    }
}

u8 dSv_player_status_a_c::getMixItemIndex(int i_no) const {
    if (i_no < MAX_SELECT_ITEM) {
        return mMixItem[i_no];
    }
    return 0;
}

u16 dSv_player_status_a_c::getRupeeMax() const {
    if (mWalletSize < 3) {  // if you make this a default, it wont match. Compiler, pls.
        switch (mWalletSize) {
        case WALLET:
            return 300;
        case BIG_WALLET:
            return 600;
        case GIANT_WALLET:
            return 1000;
        }
    }

    return 0;
}

void dSv_player_status_a_c::onMagicFlag(u8 i_magic) {
    std::cout << "dSv_player_status_a_c::onMagicFlag() is stubbed" << std::endl;

    /* if (i_magic == 0) {
        // Main Event - Can use magic
        dComIfGs_onEventBit(dSv_event_flag_c::M_097);
    }

    mMagicFlag |= (u8)(1 << i_magic); */
}

void dSv_player_status_a_c::offMagicFlag(u8 i_magic) {
    std::cout << "dSv_player_status_a_c::offMagicFlag() is stubbed" << std::endl;

    /* if (i_magic == 0) {
        // Main Event - Can use magic
        dComIfGs_offEventBit(dSv_event_flag_c::M_097);
    }

    mMagicFlag &= (u8)~(u8)(1 << i_magic); */
}

int dSv_player_status_a_c::isMagicFlag(u8 i_magic) const {
    std::cout << "dSv_player_status_a_c::isMagicFlag() is stubbed" << std::endl;

    /* if (i_magic == 0) {
        // Main Event - Can use magic
        return dComIfGs_isEventBit(dSv_event_flag_c::M_097);
    } */

    return 0; // (mMagicFlag & (u8)(1 << i_magic)) ? 1 : 0;
}

void dSv_player_status_b_c::init() {
    // mDateIpl = 0;
    mTransformLevelFlag = 0;
    mDarkClearLevelFlag = 0;
    unk10 = 0;
    mTime = 255.0f;
    mDate = 0;

    for (int i = 0; i < 3; i++) {
        unk18[i] = 0;
    }
}

void dSv_player_status_b_c::onDarkClearLV(int i_no) {
    mDarkClearLevelFlag |= (u8)(1 << i_no);
}

void dSv_player_status_b_c::offDarkClearLV(int i_no) {
    mDarkClearLevelFlag &= (u8)~(u8)(1 << i_no);
}

BOOL dSv_player_status_b_c::isDarkClearLV(int i_no) const {
    return mDarkClearLevelFlag & (u8)(1 << i_no) ? TRUE : FALSE;
}

void dSv_player_status_b_c::onTransformLV(int i_no) {
    mTransformLevelFlag |= (u8)(1 << i_no);
}

void dSv_player_status_b_c::offTransformLV(int i_no) {
    mTransformLevelFlag &= (u8)~(u8)(1 << i_no);
}

BOOL dSv_player_status_b_c::isTransformLV(int i_no) const {
    return mTransformLevelFlag & (u8)(1 << i_no) ? TRUE : FALSE;
}

void dSv_player_return_place_c::init() {
    strcpy(mName, "F_SP108");
    mRoomNo = 1;
    mPlayerStatus = 0;
    unk10 = 21;
    unk11 = 0;
}

void dSv_player_return_place_c::set(const char* i_name, s8 i_roomNo, u8 i_status) {
    strcpy(mName, i_name);
    mRoomNo = i_roomNo;
    mPlayerStatus = i_status;
}

void dSv_player_field_last_stay_info_c::init() {
    strcpy(mName, "");
    mPos.set(0.0f, 0.0f, 0.0f);
    mAngleY = 0;
    mLastSpawnId = 0;
    mRegionNo = 1;
    mFieldDataExistFlag = false;
    mRegion = 0;

    for (int i = 0; i < 2; i++) {
        unk26[i] = 0;
    }
}

void dSv_player_field_last_stay_info_c::set(const char* i_name, const cXyz& i_pos, s16 i_angle, s8 i_spawn, u8 i_regionNo) {
    strcpy(mName, i_name);
    mPos.set(i_pos);
    mAngleY = i_angle;
    mLastSpawnId = i_spawn;
    mRegionNo = i_regionNo;
}

void dSv_player_field_last_stay_info_c::onRegionBit(int i_region) {
    if (i_region >= 0 && i_region < 8) {
        mRegion |= (u8)(1 << i_region);
    }
}

BOOL dSv_player_field_last_stay_info_c::isRegionBit(int i_region) const {
    if (i_region >= 0 && i_region < 8) {
        return (mRegion & (u8)(1 << i_region)) ? TRUE : FALSE;
    }
}

void dSv_player_last_mark_info_c::init() {
    strcpy(mName, "");
    mPos.set(0.0f, 0.0f, 0.0f);
    mAngleY = 0;
    mRoomNo = 0;
    mSpawnId = 0;
    resetWarpAcceptStage();

    for (int i = 0; i < 3; i++) {
        unk25[i] = 0;
    }
}

void dSv_player_last_mark_info_c::setWarpItemData(const char* i_name, const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u8 unk_4, u8 unk_5) {
    strcpy(mName, i_name);
    mPos.set(i_pos);
    mAngleY = i_angle;
    mRoomNo = i_roomNo;
}

void dSv_player_item_c::init() {
    std::cout << "dSv_player_item_c::init() is stubbed" << std::endl;

    /* for (int i = 0; i < MAX_ITEM_SLOTS; i++) {
        mItems[i] = fpcNm_ITEM_NONE;
        mItemSlots[i] = fpcNm_ITEM_NONE;
    } */
}

void dSv_player_item_c::setItem(int i_slotNo, u8 i_itemNo) {
    if (i_slotNo < MAX_ITEM_SLOTS) {
        mItems[i_slotNo] = i_itemNo;
        setLineUpItem();
    }

    for (int i = DEFAULT_SELECT_ITEM_INDEX; i < MAX_SELECT_ITEM - 1; i++) {
        if (i_slotNo == dComIfGs_getSelectItemIndex(i)) {
            dComIfGp_setSelectItem(i);
        }
    }
}

u8 dSv_player_item_c::getItem(int i_slotNo, bool i_checkCombo) const {
    std::cout << "dSv_player_item_c::getItem() is stubbed" << std::endl;

    /* if (i_slotNo < MAX_ITEM_SLOTS) {
        if (i_checkCombo) {
            for (int i = 0; i < SELECT_ITEM_NUM; i++) {
                if ((i_slotNo == dComIfGs_getSelectItemIndex(i) || i_slotNo == dComIfGs_getMixItemIndex(i)) &&
                    dComIfGs_getMixItemIndex(i) != fpcNm_ITEM_NONE)
                {
                    u8 select_item = mItems[dComIfGs_getSelectItemIndex(i)];
                    u8 mix_item = mItems[dComIfGs_getMixItemIndex(i)];

                    // Get Bomb arrow check: Bow + Normal Bombs
                    if ((select_item == fpcNm_ITEM_BOW && mix_item == fpcNm_ITEM_NORMAL_BOMB) ||
                        (mix_item == fpcNm_ITEM_BOW && select_item == fpcNm_ITEM_NORMAL_BOMB)) {
                        return fpcNm_ITEM_BOMB_ARROW;
                    }

                    // Get Bomb arrow check: Bow + Water Bombs
                    if ((select_item == fpcNm_ITEM_BOW && mix_item == fpcNm_ITEM_WATER_BOMB) ||
                        (mix_item == fpcNm_ITEM_BOW && select_item == fpcNm_ITEM_WATER_BOMB)) {
                        return fpcNm_ITEM_BOMB_ARROW;
                    }

                    // Get Bomb arrow check: Bow + Bomblings
                    if ((select_item == fpcNm_ITEM_BOW && mix_item == fpcNm_ITEM_POKE_BOMB) ||
                        (mix_item == fpcNm_ITEM_BOW && select_item == fpcNm_ITEM_POKE_BOMB)) {
                        return fpcNm_ITEM_BOMB_ARROW;
                    }

                    // Get Hawkeye check
                    if ((select_item == fpcNm_ITEM_BOW && mix_item == fpcNm_ITEM_HAWK_EYE) ||
                        (mix_item == fpcNm_ITEM_BOW && select_item == fpcNm_ITEM_HAWK_EYE)) {
                        return fpcNm_ITEM_HAWK_ARROW;
                    }

                    // Get Rod w/ bee larva
                    if ((select_item == fpcNm_ITEM_FISHING_ROD_1 && mix_item == fpcNm_ITEM_BEE_CHILD) ||
                        (mix_item == fpcNm_ITEM_FISHING_ROD_1 && select_item == fpcNm_ITEM_BEE_CHILD)) {
                        return fpcNm_ITEM_BEE_ROD;
                    }

                    // Get Rod w/ coral earring
                    if ((select_item == fpcNm_ITEM_FISHING_ROD_1 && mix_item == fpcNm_ITEM_ZORAS_JEWEL) ||
                        (mix_item == fpcNm_ITEM_FISHING_ROD_1 && select_item == fpcNm_ITEM_ZORAS_JEWEL)) {
                        return fpcNm_ITEM_JEWEL_ROD;
                    }

                    // Get Rod w/ worm
                    if ((select_item == fpcNm_ITEM_FISHING_ROD_1 && mix_item == fpcNm_ITEM_WORM) ||
                        (mix_item == fpcNm_ITEM_FISHING_ROD_1 && select_item == fpcNm_ITEM_WORM)) {
                        return fpcNm_ITEM_WORM_ROD;
                    }

                    // This block will only run on the Wii version
                    if (i == SELECT_ITEM_B) {
                        if (dComIfGs_getSelectItemIndex(i) == 0 &&
                            dComIfGs_getMixItemIndex(i) == 0)
                        {
                            dComIfGs_setSelectItemIndex(i, fpcNm_ITEM_NONE);
                            dComIfGs_setMixItemIndex(i, fpcNm_ITEM_NONE);
                            return fpcNm_ITEM_NONE;
                        }
                    }
                }
            }
        }
        return mItems[i_slotNo];
    } */

    return -1; // fpcNm_ITEM_NONE;
}

void dSv_player_item_c::setLineUpItem() {
    std::cout << "dSv_player_item_c::setLineUpItem() is stubbed" << std::endl;

    /* static u8 i_item_lst[23] = {
        10, 8,  6,  2,  9,  4,  3,
        0,  1,  23, 20, 5,  15, 16,
        17, 11, 12, 13, 14, 19, 18,
        22, 21
    };

    int slot_idx = 0;

    for (int i = 0; i < 24; i++) {
        mItemSlots[i] = fpcNm_ITEM_NONE;
    }

    for (int i = 0; i < 23; i++) {
        u8 current = i_item_lst[i];
        if (mItems[current] != fpcNm_ITEM_NONE) {
            mItemSlots[slot_idx] = current;
            slot_idx++;
        }
    } */
}

u8 dSv_player_item_c::getLineUpItem(int i_slotNo) const {
    std::cout << "dSv_player_item_c::getLineUpItem() is stubbed" << std::endl;

    /* if (i_slotNo < MAX_ITEM_SLOTS) {
        return mItemSlots[i_slotNo];
    } */

    return -1; // fpcNm_ITEM_NONE;
}

void dSv_player_item_c::setBottleItemIn(u8 curItemIn, u8 newItemIn) {
    std::cout << "dSv_player_item_c::setBottleItemIn() is stubbed" << std::endl;

    /* curItemIn = dSv_item_rename(curItemIn);
    newItemIn = dSv_item_rename(newItemIn);

    for (int i = 0; i < 4; i++) {
        if (curItemIn == mItems[i + SLOT_11]) {
            setItem(i + SLOT_11, newItemIn);
            if (newItemIn == fpcNm_ITEM_HOT_SPRING) {
                dMeter2Info_setHotSpringTimer(i + SLOT_11);
            }

            for (int j = 0; j < 3; j++) {
                if (i + SLOT_11 == dComIfGs_getSelectItemIndex(j)) {
                    dComIfGp_setSelectItem(j);
                }
            }
            return;
        }
    } */
}

void dSv_player_item_c::setEmptyBottleItemIn(u8 i_itemNo) {
    std::cout << "dSv_player_item_c::setEmptyBottleItemIn() is stubbed" << std::endl;

    /* i_itemNo = dSv_item_rename(i_itemNo);
    setBottleItemIn(fpcNm_ITEM_EMPTY_BOTTLE, i_itemNo); */
}

void dSv_player_item_c::setEmptyBottle() {
    std::cout << "dSv_player_item_c::setEmptyBottle() is stubbed" << std::endl;

    /* for (int i = 0; i < 4; i++) {
        if (dComIfGs_getItem((u8)(i + SLOT_11), true) == fpcNm_ITEM_NONE) {
            dComIfGs_setItem((u8)(i + SLOT_11), fpcNm_ITEM_EMPTY_BOTTLE);
            return;
        }
    } */
}

void dSv_player_item_c::setEmptyBottle(u8 i_itemNo) {
    std::cout << "dSv_player_item_c::setEmptyBottle() is stubbed" << std::endl;

    /* for (int i = 0; i < 4; i++) {
        if (dComIfGs_getItem((u8)(i + SLOT_11), true) == fpcNm_ITEM_NONE) {
            dComIfGs_setItem((u8)(i + SLOT_11), i_itemNo);
            return;
        }
    } */
}

void dSv_player_item_c::setEquipBottleItemIn(u8 curItemIn, u8 newItemIn) {
    std::cout << "dSv_player_item_c::setEquipBottleItemIn() is stubbed" << std::endl;

    /* newItemIn = dSv_item_rename(newItemIn);

    if (dComIfGs_getSelectItemIndex(curItemIn) >= SLOT_11 &&
        dComIfGs_getSelectItemIndex(curItemIn) <= SLOT_14) {
        if (newItemIn == fpcNm_ITEM_HOT_SPRING) {
            dMeter2Info_setHotSpringTimer(dComIfGs_getSelectItemIndex(curItemIn));
        }

        setItem(dComIfGs_getSelectItemIndex(curItemIn), newItemIn);
        dComIfGs_setItem(dComIfGs_getSelectItemIndex(curItemIn), newItemIn);
        dComIfGp_setItem(dComIfGs_getSelectItemIndex(curItemIn), newItemIn);
        dComIfGp_setSelectItem(curItemIn);
    } */
}

void dSv_player_item_c::setEquipBottleItemEmpty(u8 curItemIn) {
    std::cout << "dSv_player_item_c::setEquipBottleItemEmpty() is stubbed" << std::endl;
    // setEquipBottleItemIn(curItemIn, fpcNm_ITEM_EMPTY_BOTTLE);
}

u8 dSv_player_item_c::checkBottle(u8 i_itemNo) {
    std::cout << "dSv_player_item_c::checkBottle() is stubbed" << std::endl;

    u8 num_bottles = 0;

    /* i_itemNo = dSv_item_rename(i_itemNo);

    for (int i = 0; i < BOTTLE_MAX; i++) {
        if (i_itemNo == mItems[i + SLOT_11]) {
            num_bottles++;
        }
    } */
    
    return num_bottles;
}

int dSv_player_item_c::checkInsectBottle() {
    std::cout << "dSv_player_item_c::checkInsectBottle() is stubbed" << std::endl;

    /* for (int i = 0; i < 24; i++) {
        if (dComIfGs_isItemFirstBit(fpcNm_ITEM_M_BEETLE + i) &&
            !dComIfGs_isEventBit(dSv_event_flag_c::saveBitLabels[0x191 + i])) {
            return 1;
        }
    } */

    return 0;
}

u8 dSv_player_item_c::checkEmptyBottle() {
    std::cout << "dSv_player_item_c::checkEmptyBottle() is stubbed" << std::endl;

    u8 bottleNum = 0;

    /* for (int i = 0; i < BOTTLE_MAX; i++) {
        if (mItems[i + SLOT_11] == fpcNm_ITEM_EMPTY_BOTTLE) {
            bottleNum++;
        }
    } */

    return bottleNum;
}

void dSv_player_item_c::setBombBagItemIn(u8 i_curBomb, u8 i_newBomb, bool i_setNum) {
    std::cout << "dSv_player_item_c::setBombBagItemIn() is stubbed" << std::endl;

    /* for (int i = 0; i < 3; i++) {
        if (i_curBomb == mItems[i + SLOT_15]) {
            setItem(i + SLOT_15, i_newBomb);

            if (i_setNum == true && i_newBomb != fpcNm_ITEM_BOMB_BAG_LV1) {
                dComIfGs_setBombNum(i, dComIfGs_getBombMax(i_newBomb));
            }

            for (int j = 0; j < 3; j++) {
                if (i + SLOT_15 == dComIfGs_getSelectItemIndex(j)) {
                    dComIfGp_setSelectItem(j);
                }
            }
            break;
        }
    } */
}

void dSv_player_item_c::setBombBagItemIn(u8 i_curBomb, u8 i_newBomb, u8 i_bombNum, bool i_setNum) {
    std::cout << "dSv_player_item_c::setBombBagItemIn() is stubbed" << std::endl;

    /* for (int i = 0; i < 3; i++) {
        if (i_curBomb == mItems[i + SLOT_15]) {
            setItem(i + SLOT_15, i_newBomb);

            if (i_setNum == 1 && i_newBomb != fpcNm_ITEM_BOMB_BAG_LV1) {
                if (i_bombNum > dComIfGs_getBombMax(i_newBomb)) {
                    i_bombNum = dComIfGs_getBombMax(i_newBomb);
                }
                dComIfGs_setBombNum(i, i_bombNum);
            }

            for (int j = 0; j < 3; j++) {
                if (i + SLOT_15 == dComIfGs_getSelectItemIndex(j)) {
                    dComIfGp_setSelectItem(j);
                }
            }
            break;
        }
    } */
}

void dSv_player_item_c::setEmptyBombBagItemIn(u8 i_newBomb, bool i_setNum) {
    std::cout << "dSv_player_item_c::setEmptyBombBagItemIn() is stubbed" << std::endl;
    // setBombBagItemIn(fpcNm_ITEM_BOMB_BAG_LV1, i_newBomb, i_setNum);
}

void dSv_player_item_c::setEmptyBombBagItemIn(u8 i_newBomb, u8 i_bombNum, bool i_setNum) {
    std::cout << "dSv_player_item_c::setEmptyBombBagItemIn() is stubbed" << std::endl;
    // setBombBagItemIn(fpcNm_ITEM_BOMB_BAG_LV1, i_newBomb, i_bombNum, i_setNum);
}

void dSv_player_item_c::setEmptyBombBag() {
    std::cout << "dSv_player_item_c::setEmptyBombBag() is stubbed" << std::endl;

    /* for (int i = 0; i < 3; i++) {
        if (dComIfGs_getItem((u8)(i + SLOT_15), true) == fpcNm_ITEM_NONE) {
            dComIfGs_setItem((u8)(i + SLOT_15), fpcNm_ITEM_BOMB_BAG_LV1);
            return;
        }
    } */
}

void dSv_player_item_c::setEmptyBombBag(u8 i_newBomb, u8 i_bombNum) {
    std::cout << "dSv_player_item_c::setEmptyBombBag() is stubbed" << std::endl;

    /* for (int i = 0; i < 3; i++) {
        if (dComIfGs_getItem((u8)(i + SLOT_15), true) == fpcNm_ITEM_NONE) {
            dComIfGs_setItem((u8)(i + SLOT_15), i_newBomb);

            if (i_newBomb != fpcNm_ITEM_BOMB_BAG_LV1) {
                if (i_bombNum > dComIfGs_getBombMax(i_newBomb)) {
                    i_bombNum = dComIfGs_getBombMax(i_newBomb);
                }
    
                dComIfGs_setBombNum(i, i_bombNum);
            }
            return;
        }
    } */
}

u8 dSv_player_item_c::checkBombBag(u8 i_itemNo) {
    u8 bombBags = 0;

    for (int i = 0; i < dSv_player_item_c::BOMB_BAG_MAX; i++) {
        if (i_itemNo == mItems[i + SLOT_15]) {
            bombBags++;
        }
    }

    return bombBags;
}

void dSv_player_item_c::setWarashibeItem(u8 i_itemNo) {
    std::cout << "dSv_player_item_c::setWarashibeItem() is stubbed" << std::endl;

    /* dComIfGs_setItem(SLOT_21, i_itemNo);
    dComIfGp_setItem(SLOT_21, i_itemNo);

    for (int i = 0; i < 4; i++) {
        if (dComIfGs_getSelectItemIndex((u8)i) == SLOT_21) {
            dComIfGp_setSelectItem((u8)i);
        }
    } */
}

void dSv_player_item_c::setRodTypeLevelUp() {
    std::cout << "dSv_player_item_c::setRodTypeLevelUp() is stubbed" << std::endl;

    /* switch (mItems[SLOT_20]) {
        case fpcNm_ITEM_BEE_ROD: {
            mItems[SLOT_20] = fpcNm_ITEM_JEWEL_BEE_ROD;
            break;
        }
        case fpcNm_ITEM_WORM_ROD: {
            mItems[SLOT_20] = fpcNm_ITEM_JEWEL_WORM_ROD;
            break;
        }
        case fpcNm_ITEM_FISHING_ROD_1: {
            mItems[SLOT_20] = fpcNm_ITEM_JEWEL_ROD;
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        dComIfGp_setSelectItem(i);
    } */
}

void dSv_player_item_c::setBaitItem(u8 i_itemNo) {
    std::cout << "dSv_player_item_c::setBaitItem() is stubbed" << std::endl;

    /* switch (i_itemNo) {
        case fpcNm_ITEM_BEE_CHILD: {
            if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ZORAS_JEWEL)) {
                mItems[SLOT_20] = fpcNm_ITEM_JEWEL_BEE_ROD;
            } else {
                mItems[SLOT_20] = fpcNm_ITEM_BEE_ROD;
            }
            break;
        }
        case fpcNm_ITEM_WORM: {
            if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ZORAS_JEWEL)) {
                mItems[SLOT_20] = fpcNm_ITEM_JEWEL_WORM_ROD;
            } else {
                mItems[SLOT_20] = fpcNm_ITEM_WORM_ROD;
            }
            break;
        }
        case fpcNm_ITEM_NONE: {
            if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ZORAS_JEWEL)) {
                mItems[SLOT_20] = fpcNm_ITEM_JEWEL_ROD;
            } else {
                mItems[SLOT_20] = fpcNm_ITEM_FISHING_ROD_1;
            }
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        dComIfGp_setSelectItem(i);
    } */
}

void dSv_player_get_item_c::init() {
    for (int i = 0; i < 8; i++) {
        mItemFlags[i] = 0;
    }
}

void dSv_player_get_item_c::onFirstBit(u8 i_itemno) {
    int index = i_itemno / 32;
    int bit = i_itemno % 32;
    mItemFlags[index] |= (1 << bit);
}

void dSv_player_get_item_c::offFirstBit(u8 i_itemno) {
    int index = i_itemno / 32;
    int bit = i_itemno % 32;
    mItemFlags[index] &= ~(1 << bit);
}

int dSv_player_get_item_c::isFirstBit(u8 i_itemno) const {
    int index = i_itemno / 32;
    int bit = i_itemno % 32;
    return mItemFlags[index] & (1 << bit) ? 1 : 0;
}

void dSv_player_item_record_c::init() {
    mArrowNum = 0;

    for (int i = 0; i < 3; i++) {
        mBombNum[i] = 0;
    }

    for (int i = 0; i < 4; i++) {
        mBottleNum[i] = 0;
    }

    mPachinkoNum = 0;

    for (int i = 0; i < 3; i++) {
        unk5[i] = 0;
    }
}

void dSv_player_item_record_c::setBombNum(u8 i_bagIdx, u8 i_bombNum) {
    mBombNum[i_bagIdx] = i_bombNum;
}

u8 dSv_player_item_record_c::getBombNum(u8 i_bagIdx) const {
    return mBombNum[i_bagIdx];
}

void dSv_player_item_record_c::setBottleNum(u8 i_bottleIdx, u8 i_bottleNum) {
    mBottleNum[i_bottleIdx] = i_bottleNum;
}

u8 dSv_player_item_record_c::addBottleNum(u8 i_bottleIdx, s16 i_no) {
    std::cout << "dSv_player_item_record_c::addBottleNum() is stubbed" << std::endl;

    /* int bottleNum = mBottleNum[i_bottleIdx] + i_no;

    u8 var_r28 = dComIfGs_getItem((u8)(i_bottleIdx + SLOT_11), true);

    if (bottleNum < 0) {
        mBottleNum[i_bottleIdx] = 0;
    } else if (bottleNum > dComIfGs_getBottleMax()) {
        mBottleNum[i_bottleIdx] = dComIfGs_getBottleMax();
    } else {
        mBottleNum[i_bottleIdx] = bottleNum;
    } */

    return 0; // mBottleNum[i_bottleIdx];
}

u8 dSv_player_item_record_c::getBottleNum(u8 i_bottleIdx) const {
    return mBottleNum[i_bottleIdx];
}

void dSv_player_item_max_c::init() {
    std::cout << "dSv_player_item_max_c::init() is stubbed" << std::endl;

    /* for (int i = 0; i < 7; i++) {
        mItemMax[i] = 30;
    }

    setBombNum(fpcNm_ITEM_NORMAL_BOMB, 30);
    setBombNum(fpcNm_ITEM_WATER_BOMB, 15);
    setBombNum(fpcNm_ITEM_POKE_BOMB, 10);

    mItemMax[7] = 0; */
}

void dSv_player_item_max_c::setBombNum(u8 i_bombType, u8 i_maxNum) {
    std::cout << "dSv_player_item_max_c::setBombNum() is stubbed" << std::endl;

    /* switch (i_bombType) {
        case fpcNm_ITEM_NORMAL_BOMB:
            mItemMax[NORMAL_BOMB_MAX] = i_maxNum;
            return;
        case fpcNm_ITEM_WATER_BOMB:
            mItemMax[WATER_BOMB_MAX] = i_maxNum;
            return;
        case fpcNm_ITEM_POKE_BOMB:
            mItemMax[POKE_BOMB_MAX] = i_maxNum;
    } */
}

u8 dSv_player_item_max_c::getBombNum(u8 i_bombType) const {
    std::cout << "dSv_player_item_max_c::getBombNum() is stubbed" << std::endl;

    /* u8 lv_multiplier = 1;

    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_BOMB_BAG_LV2)) {
        lv_multiplier = 2;
    }

    switch (i_bombType) {
        case fpcNm_ITEM_NORMAL_BOMB:
            return (u8)(mItemMax[NORMAL_BOMB_MAX] * lv_multiplier);
        case fpcNm_ITEM_WATER_BOMB:
            return (u8)(mItemMax[WATER_BOMB_MAX] * lv_multiplier);
        case fpcNm_ITEM_POKE_BOMB:
            return (u8)(mItemMax[POKE_BOMB_MAX] * lv_multiplier);
        default:
            return 0;
    } */

    return 0;
}

void dSv_player_collect_c::init() {
    for (int i = 0; i < 8; i++) {
        mItem[i] = 0;
    }

    unk8 = 0;
    mCrystal = 0;
    mMirror = 0;
    unk11 = 0xFF;
    mPohNum = 0;
}

void dSv_player_collect_c::setCollect(int i_item_type, u8 i_item) {
    mItem[i_item_type] |= (u8)(1 << i_item);
}

void dSv_player_collect_c::offCollect(int i_item_type, u8 i_item) {
    mItem[i_item_type] &= (u8)~(u8)(1 << i_item);
}

BOOL dSv_player_collect_c::isCollect(int i_item_type, u8 i_item) const {
    return mItem[i_item_type] & (u8)(1 << i_item) ? TRUE : FALSE;
}

void dSv_player_collect_c::onCollectCrystal(u8 i_item) {
    mCrystal |= (u8)(1 << i_item);
}

void dSv_player_collect_c::offCollectCrystal(u8 i_item) {
    mCrystal &= (u8)~(u8)(1 << i_item);
}

BOOL dSv_player_collect_c::isCollectCrystal(u8 i_item) const {
    return mCrystal & (u8)(1 << i_item) ? TRUE : FALSE;
}

void dSv_player_collect_c::onCollectMirror(u8 i_item) {
    mMirror |= (u8)(1 << i_item);
}

void dSv_player_collect_c::offCollectMirror(u8 i_item) {
    mMirror &= (u8)~(u8)(1 << i_item);
}

BOOL dSv_player_collect_c::isCollectMirror(u8 i_item) const {
    return mMirror & (u8)(1 << i_item) ? TRUE : FALSE;
}

void dSv_player_wolf_c::init() {
    for (int i = 0; i < 3; i++) {
        unk0[i] = 0;
    }

    unk3 = 0;
}

void dSv_light_drop_c::init() {
    for (int i = 0; i < 4; i++) {
        mLightDropNum[i] = 0;
    }

    mLightDropGetFlag = 0;

    for (int i = 0; i < 3; i++) {
        unk5[i] = 0;
    }
}

void dSv_light_drop_c::setLightDropNum(u8 i_nowLevel, u8 i_dropNum) {
    if (i_nowLevel < LIGHT_DROP_STAGE || i_nowLevel > 6) {
        mLightDropNum[i_nowLevel] = i_dropNum;
    }
}

u8 dSv_light_drop_c::getLightDropNum(u8 i_nowLevel) const {
    if (i_nowLevel >= LIGHT_DROP_STAGE && i_nowLevel <= 6) {
        return 0;
    }

    return mLightDropNum[i_nowLevel];
}

void dSv_light_drop_c::onLightDropGetFlag(u8 i_nowLevel) {
    if (i_nowLevel < LIGHT_DROP_STAGE || i_nowLevel > 6) {
        mLightDropGetFlag |= (u8)(1 << i_nowLevel);
    }
}

void dSv_light_drop_c::offLightDropGetFlag(u8 i_nowLevel) {
    if (i_nowLevel < LIGHT_DROP_STAGE || i_nowLevel > 6) {
        mLightDropGetFlag &= (u8)~(u8)(1 << i_nowLevel);
    }
}

BOOL dSv_light_drop_c::isLightDropGetFlag(u8 i_nowLevel) const {
    if (i_nowLevel >= LIGHT_DROP_STAGE && i_nowLevel <= 6) {
        return 0;
    }

    return mLightDropGetFlag & (u8)(1 << i_nowLevel) ? TRUE : FALSE;
}

void dSv_letter_info_c::init() {
    for (int i = 0; i < 2; i++) {
        mLetterGetFlags[i] = 0;
        mLetterReadFlags[i] = 0;
    }

    for (int i = 0; i < LETTER_INFO_BIT; i++) {
        mGetNumber[i] = 0;
    }
}

void dSv_letter_info_c::onLetterGetFlag(int i_no) {
    mLetterGetFlags[i_no >> 5] |= 1 << (i_no & 0x1F);
}

BOOL dSv_letter_info_c::isLetterGetFlag(int i_no) const {
    return mLetterGetFlags[i_no >> 5] & (1 << (i_no & 0x1F)) ? TRUE : FALSE;
}

void dSv_letter_info_c::onLetterReadFlag(int i_no) {
    mLetterReadFlags[i_no >> 5] |= 1 << (i_no & 0x1F);
}

int  dSv_letter_info_c::isLetterReadFlag(int i_no) const {
    return mLetterReadFlags[i_no >> 5] & 1 << (i_no & 0x1F) ? 1 : 0;
}

void dSv_fishing_info_c::init() {
    for (int i = 0; i < 16; i++) {
        mFishCount[i] = 0;
        mMaxSize[i] = 0;
    }
}

void dSv_fishing_info_c::addFishCount(u8 i_fishIdx) {
    if (mFishCount[i_fishIdx] < 999) {
        mFishCount[i_fishIdx]++;
    }
}

void dSv_player_info_c::init() {
    /* dMeter2Info_getString(0x382, mPlayerName, NULL);  // Link
    dMeter2Info_getString(0x383, mHorseName, NULL);   // Epona */

    unk0 = 0;
    mTotalTime = 0;
    unk16 = 0;
    mDeathCount = 0;
    mClearCount = 0;

    for (int i = 0; i < 5; i++) {
        unk55[i] = 0;
    }
}

void dSv_player_config_c::init() {
#if VERSION == VERSION_GCN_JPN
    mRuby = 0;
#else
    mRuby = 1;
#endif

    /* if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
        mSoundMode = OS_SOUND_MODE_MONO;
        mDoAud_setOutputMode(OS_SOUND_MODE_MONO);
    } else {
        mSoundMode = OS_SOUND_MODE_STEREO;
        mDoAud_setOutputMode(OS_SOUND_MODE_STEREO);
    } */

    mAttentionType = 0;
    mVibration = 1;

#if REGION_PAL
    mLanguage = OSGetLanguage();
#else
    mLanguage = 0;
#endif

    unk5 = 0;
    mShortCut = 0;
    mCalibrateDist = 350;
    mCalValue = 0;
    mCameraControl = 0;
    mPointer = 1;
}

u32 dSv_player_config_c::checkVibration() const {
    return 0; // JUTGamePad::sRumbleSupported & 0x80000000 ? dComIfGp_getNowVibration() : 0;
}

u8 dSv_player_config_c::getSound() {
    return mSoundMode;
}

void dSv_player_config_c::setSound(u8 i_mode) {
    mSoundMode = i_mode;
}

u8 dSv_player_config_c::getVibration() {
    return mVibration;
}

void dSv_player_config_c::setVibration(u8 i_status) {
    mVibration = i_status;
}

u8 dSv_player_config_c::getPalLanguage() const {
    /* #if VERSION == VERSION_GCN_PAL
    switch (OSGetLanguage()) {
    case 0:
        return LANGUAGE_ENGLISH;
    case 1:
        return LANGUAGE_GERMAN;
    case 2:
        return LANGUAGE_FRENCH;
    case 3:
        return LANGUAGE_SPANISH;
    case 4:
        return LANGUAGE_ITALIAN;
    }
    #endif */

    return 0;
}

void dSv_player_c::init() {
    mPlayerStatusA.init();
    mPlayerStatusB.init();
    // mHorsePlace.init();
    mPlayerReturnPlace.init();
    mPlayerFieldLastStayInfo.init();
    mPlayerLastMarkInfo.init();
    mItem.init();
    mGetItem.init();
    mItemRecord.init();
    mItemMax.init();
    mCollect.init();
    mWolf.init();
    mLightDrop.init();
    mLetterInfo.init();
    mFishingInfo.init();
    mPlayerInfo.init();
    mConfig.init();
}

void dSv_memBit_c::init() {
    for (int i = 0; i < 2; i++) {
        mTbox[i] = 0;
    }

    for (int i = 0; i < 4; i++) {
        mSwitch[i] = 0;
    }

    for (int i = 0; i < 1; i++) {
        mItem[i] = 0;
    }

    mKeyNum = 0;
    mDungeonItem = 0;
}

void dSv_memBit_c::onTbox(int i_no) {
    mTbox[i_no >> 5] |= 1 << (i_no & 0x1F);
}

void dSv_memBit_c::offTbox(int i_no) {
    mTbox[i_no >> 5] &= ~(1 << (i_no & 0x1F));
}

BOOL dSv_memBit_c::isTbox(int i_no) const {
    return 1 << (i_no & 0x1f) & mTbox[i_no >> 5] ? TRUE : FALSE;
}

void dSv_memBit_c::onSwitch(int i_no) {
    mSwitch[i_no >> 5] |= 1 << (i_no & 0x1F);
}

void dSv_memBit_c::offSwitch(int i_no) {
    mSwitch[i_no >> 5] &= ~(1 << (i_no & 0x1F));
}

BOOL dSv_memBit_c::isSwitch(int i_no) const {
    return (mSwitch[i_no >> 5] & 1 << (i_no & 0x1F)) ? TRUE : FALSE;
}

BOOL dSv_memBit_c::revSwitch(int i_no) {
    u32 switchInd = i_no >> 5;
    u32 tmp = 1 << (i_no & 0x1F);
    mSwitch[switchInd] ^= tmp;
    return mSwitch[switchInd] & tmp ? TRUE : FALSE;
}

void dSv_memBit_c::onItem(int i_no) {
    mItem[i_no >> 5] |= 1 << (i_no & 0x1F);
}

void dSv_memBit_c::offItem(int i_no) {
    mItem[i_no >> 5] |= ~(1 << (i_no & 0x1F));
}

BOOL dSv_memBit_c::isItem(int i_no) const {
    return (mItem[i_no >> 5] & 1 << (i_no & 0x1F)) ? TRUE : FALSE;
}

void dSv_memBit_c::onDungeonItem(int i_no) {
    mDungeonItem |= (u8)(1 << i_no);
}

void dSv_memBit_c::offDungeonItem(int i_no) {
    mDungeonItem &= (u8)~(u8)(1 << i_no);
}

s32 dSv_memBit_c::isDungeonItem(int i_no) const {
    return mDungeonItem & (u8)(1 << i_no) ? TRUE : FALSE;
}

void dSv_event_c::init() {
    int i;
    for (i = 0; i < MAX_EVENTS; i++) {
        mEvent[i] = 0;
    }

    // setInitEventBit();
}

void dSv_event_c::onEventBit(u16 i_no) {
    mEvent[i_no >> 8] |= (u8)i_no;
}

void dSv_event_c::offEventBit(u16 i_no) {
    mEvent[i_no >> 8] &= ~(u8)i_no;
}

int dSv_event_c::isEventBit(const u16 i_no) const {
    return mEvent[i_no >> 8] & (i_no & 0xFF) ? 1 : 0;
}

void dSv_event_c::setEventReg(u16 i_reg, u8 i_no) {
    mEvent[i_reg >> 8] &= ~(u8)i_reg;
    mEvent[i_reg >> 8] |= i_no;
}

u8 dSv_event_c::getEventReg(u16 i_reg) const {
    return (u8)i_reg & mEvent[i_reg >> 8];
}

void dSv_MiniGame_c::init() {
    for (int i = 0; i < 1; i++) {
        unk0[i][0] = 0;
        for (int j = 0; j < 3; j++) {
            unk0[i][1 + j] = 0;
        }
    }

    mHookGameTime = 120000;
    mBalloonScore = 0;
    mRaceGameTime = 0;
    unk16 = 0;
    unk20 = 0;
}

void dSv_memory_c::init() {
    mBit.init();
}

void dSv_memory2_c::init() {
    for (int i = 0; i < 2; i++) {
        mVisitedRoom[i] = 0;
    }
}

void dSv_memory2_c::onVisitedRoom(int i_no) {
    mVisitedRoom[i_no >> 5] |= 1 << (i_no & 0x1F);
}

void dSv_memory2_c::offVisitedRoom(int i_no) {
    mVisitedRoom[i_no >> 5] &= ~(1 << (i_no & 0x1F));
}

BOOL dSv_memory2_c::isVisitedRoom(int i_no) {
    return (1 << (i_no & 0x1F) & mVisitedRoom[i_no >> 5]) ? TRUE : FALSE;
}

void dSv_save_c::init() {
    mPlayer.init();
    for (int i = 0; i < STAGE_MAX; i++) {
        mSave[i].init();
    }

    for (int i = 0; i < STAGE2_MAX; i++) {
        mSave2[i].init();
    }

    mEvent.init();
    mMiniGame.init();
}

dSv_memory2_c* dSv_save_c::getSave2(int i_stage2No) {
    return &mSave2[i_stage2No];
}