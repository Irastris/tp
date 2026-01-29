#include "JSystem/JSystem.h"
#include "JSystem/J3DGraphBase/J3DMatBlock.h"
/* #include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "global.h"
#include <string> */

inline void loadMatColors(const J3DGXColor* color) {
    std::cout << "loadMatColors()) is stubbed" << std::endl;
}

inline void loadAmbColors(const J3DGXColor* color) {
    std::cout << "loadAmbColors() is stubbed" << std::endl;
}

inline void loadTexCoordScale(GXTexCoordID coord, const J3DTexCoordScaleInfo& info) {
    std::cout << "loadTexCoordScale() is stubbed" << std::endl;
}

inline void loadTevColor(u32 reg, const J3DGXColorS10& color) {
    std::cout << "loadTevColor() is stubbed" << std::endl;
}

inline void loadTevKColor(u32 reg, const J3DGXColor& color) {
    std::cout << "loadTevKColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::initialize() {
    std::cout << "J3DColorBlockLightOff::initialize() is stubbed" << std::endl;
}

void J3DColorBlockAmbientOn::initialize() {
    std::cout << "J3DColorBlockAmbientOn::initialize() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::initialize() {
    std::cout << "J3DColorBlockLightOn::initialize() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::initialize() {
    std::cout << "J3DTexGenBlockPatched::initialize() is stubbed" << std::endl;
}

void J3DTexGenBlock4::initialize() {
    std::cout << "J3DTexGenBlock4::initialize() is stubbed" << std::endl;
}

void J3DTexGenBlockBasic::initialize() {
    std::cout << "J3DTexGenBlockBasic::initialize() is stubbed" << std::endl;
}

void J3DTevBlockNull::initialize() {
    std::cout << "J3DTevBlockNull::initialize() is stubbed" << std::endl;
}

void J3DTevBlockPatched::initialize() {
    std::cout << "J3DTevBlockPatched::initialize() is stubbed" << std::endl;
}

void J3DTevBlock1::initialize() {
    std::cout << "J3DTevBlock1::initialize() is stubbed" << std::endl;
}

void J3DTevBlock2::initialize() {
    std::cout << "J3DTevBlock2::initialize() is stubbed" << std::endl;
}

void J3DTevBlock4::initialize() {
    std::cout << "J3DTevBlock4::initialize() is stubbed" << std::endl;
}

void J3DTevBlock16::initialize() {
    std::cout << "J3DTevBlock16::initialize() is stubbed" << std::endl;
}

void J3DIndBlockFull::initialize() {
    std::cout << "J3DIndBlockFull::initialize() is stubbed" << std::endl;
}

void J3DPEBlockFogOff::initialize() {
    std::cout << "J3DPEBlockFogOff::initialize() is stubbed" << std::endl;
}

void J3DPEBlockFull::initialize() {
    std::cout << "J3DPEBlockFull::initialize() is stubbed" << std::endl;
}

s32 J3DColorBlockLightOff::countDLSize() {
    std::cout << "J3DColorBlockLightOff::countDLSize() is stubbed" << std::endl;
    return 34;
}

s32 J3DColorBlockAmbientOn::countDLSize() {
    std::cout << "J3DColorBlockAmbientOn::countDLSize() is stubbed" << std::endl;
    return 47;
}

s32 J3DColorBlockLightOn::countDLSize() {
    std::cout << "J3DColorBlockLightOn::countDLSize() is stubbed" << std::endl;
    return 623;
}

s32 J3DTexGenBlockPatched::countDLSize() {
    std::cout << "J3DTexGenBlockPatched::countDLSize() is stubbed" << std::endl;
    return 424;
}

s32 J3DTexGenBlock4::countDLSize() {
    std::cout << "J3DTexGenBlock4::countDLSize() is stubbed" << std::endl;
    return 254;
}

s32 J3DTexGenBlockBasic::countDLSize() {
    std::cout << "J3DTexGenBlockBasic::countDLSize() is stubbed" << std::endl;
    return 498;
}

s32 J3DTevBlockPatched::countDLSize() {
    std::cout << "J3DTevBlockPatched::countDLSize() is stubbed" << std::endl;
    return 560;
}

s32 J3DTevBlock1::countDLSize() {
    std::cout << "J3DTevBlock1::countDLSize() is stubbed" << std::endl;
    return 105;
}

s32 J3DTevBlock2::countDLSize() {
    std::cout << "J3DTevBlock2::countDLSize() is stubbed" << std::endl;
    return 335;
}

s32 J3DTevBlock4::countDLSize() {
    std::cout << "J3DTevBlock4::countDLSize() is stubbed" << std::endl;
    return 580;
}

s32 J3DTevBlock16::countDLSize() {
    std::cout << "J3DTevBlock16::countDLSize() is stubbed" << std::endl;
    return 1000;
}

s32 J3DIndBlockFull::countDLSize() {
    std::cout << "J3DIndBlockFull::countDLSize() is stubbed" << std::endl;
    return 140;
}

s32 J3DPEBlockOpa::countDLSize() {
    std::cout << "J3DPEBlockOpa::countDLSize() is stubbed" << std::endl;
    return 30;
}

s32 J3DPEBlockTexEdge::countDLSize() {
    std::cout << "J3DPEBlockTexEdge::countDLSize() is stubbed" << std::endl;
    return 30;
}

s32 J3DPEBlockXlu::countDLSize() {
    std::cout << "J3DPEBlockXlu::countDLSize() is stubbed" << std::endl;
    return 30;
}

s32 J3DPEBlockFogOff::countDLSize() {
    std::cout << "J3DPEBlockFogOff::countDLSize() is stubbed" << std::endl;
    return 30;
}

s32 J3DPEBlockFull::countDLSize() {
    std::cout << "J3DPEBlockFull::countDLSize() is stubbed" << std::endl;
    return 85;
}

void J3DColorBlockLightOff::load() {
    std::cout << "J3DColorBlockLightOff::load() is stubbed" << std::endl;
}

void J3DColorBlockAmbientOn::load() {
    std::cout << "J3DColorBlockAmbientOn::load() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::load() {
    std::cout << "J3DColorBlockLightOn::load() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::patch() {
    std::cout << "J3DColorBlockLightOff::patch() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::patchMatColor() {
    std::cout << "J3DColorBlockLightOff::patchMatColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::patchLight() {
    std::cout << "J3DColorBlockLightOff::patchLight() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::patch() {
    std::cout << "J3DColorBlockLightOn::patch() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::patchMatColor() {
    std::cout << "J3DColorBlockLightOn::patchMatColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::patchLight() {
    std::cout << "J3DColorBlockLightOn::patchLight() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::diff(u32 diffFlags) {
    std::cout << "J3DColorBlockLightOff::diff() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::diffMatColor() {
    std::cout << "J3DColorBlockLightOff::diffMatColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::diffColorChan() {
    std::cout << "J3DColorBlockLightOff::diffColorChan() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::diff(u32 diffFlags) {
    std::cout << "J3DColorBlockLightOn::diff() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::diffAmbColor() {
    std::cout << "J3DColorBlockLightOn::diffAmbColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::diffMatColor() {
    std::cout << "J3DColorBlockLightOn::diffMatColor() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::diffColorChan() {
    std::cout << "J3DColorBlockLightOn::diffColorChan() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::diffLightObj(u32 lightObjNum) {
    std::cout << "J3DColorBlockLightOn::diffLightObj() is stubbed" << std::endl;
}

void J3DTexGenBlock4::load() {
    std::cout << "J3DTexGenBlock4::load() is stubbed" << std::endl;
}

void J3DTexGenBlockBasic::load() {
    std::cout << "J3DTexGenBlockBasic::load() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::patch() {
    std::cout << "J3DTexGenBlockPatched::patch() is stubbed" << std::endl;
}

void J3DTexGenBlock4::patch() {
    std::cout << "J3DTexGenBlock4::patch() is stubbed" << std::endl;
}

void J3DTexGenBlockBasic::patch() {
    std::cout << "J3DTexGenBlockBasic::patch() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::diff(u32 diffFlags) {
    std::cout << "J3DTexGenBlockPatched::diff() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::diffTexMtx() {
    std::cout << "J3DTexGenBlockPatched::diffTexMtx() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::diffTexGen() {
    std::cout << "J3DTexGenBlockPatched::diffTexGen() is stubbed" << std::endl;
}

void J3DTevBlock1::load() {
    std::cout << "J3DTevBlock1::load() is stubbed" << std::endl;
}

void J3DTevBlock2::load() {
    std::cout << "J3DTevBlock2::load() is stubbed" << std::endl;
}

void J3DTevBlock4::load() {
    std::cout << "J3DTevBlock4::load() is stubbed" << std::endl;
}

void J3DTevBlock16::load() {
    std::cout << "J3DTevBlock16::load() is stubbed" << std::endl;
}

void J3DTevBlockPatched::patchTexNo() {
    std::cout << "J3DTevBlockPatched::patchTexNo() is stubbed" << std::endl;
}

void J3DTevBlockPatched::patchTevReg() {
    std::cout << "J3DTevBlockPatched::patchTevReg() is stubbed" << std::endl;
}

void J3DTevBlockPatched::patchTexNoAndTexCoordScale() {
    std::cout << "J3DTevBlockPatched::patchTexNoAndTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlockPatched::patch() {
    std::cout << "J3DTevBlockPatched::patch() is stubbed" << std::endl;
}

void J3DTevBlock1::patchTexNo() {
    std::cout << "J3DTevBlock1::patchTexNo() is stubbed" << std::endl;
}

void J3DTevBlock1::patchTevReg() {
    std::cout << "J3DTevBlock1::patchTevReg() is stubbed" << std::endl;
}

void J3DTevBlock1::patchTexNoAndTexCoordScale() {
    std::cout << "J3DTevBlock1::patchTexNoAndTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock1::patch() {
    std::cout << "J3DTevBlock1::patch() is stubbed" << std::endl;
}

void J3DTevBlock2::patchTexNo() {
    std::cout << "J3DTevBlock2::patchTexNo() is stubbed" << std::endl;
}

void J3DTevBlock2::patchTevReg() {
    std::cout << "J3DTevBlock2::patchTevReg() is stubbed" << std::endl;
}

void J3DTevBlock2::patchTexNoAndTexCoordScale() {
    std::cout << "J3DTevBlock2::patchTexNoAndTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock2::patch() {
    std::cout << "J3DTevBlock2::patch() is stubbed" << std::endl;
}

void J3DTevBlock4::patchTexNo() {
    std::cout << "J3DTevBlock4::patchTexNo() is stubbed" << std::endl;
}

void J3DTevBlock4::patchTevReg() {
    std::cout << "J3DTevBlock4::patchTevReg() is stubbed" << std::endl;
}

void J3DTevBlock4::patchTexNoAndTexCoordScale() {
    std::cout << "J3DTevBlock4::patchTexNoAndTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock4::patch() {
    std::cout << "J3DTevBlock4::patch() is stubbed" << std::endl;
}

void J3DTevBlock16::patchTexNo() {
    std::cout << "J3DTevBlock16::patchTexNo() is stubbed" << std::endl;
}

void J3DTevBlock16::patchTevReg() {
    std::cout << "J3DTevBlock16::patchTevReg() is stubbed" << std::endl;
}

void J3DTevBlock16::patchTexNoAndTexCoordScale() {
    std::cout << "J3DTevBlock16::patchTexNoAndTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock16::patch() {
    std::cout << "J3DTevBlock16::patch() is stubbed" << std::endl;
}

void J3DTevBlock::diff(u32 diffFlags) {
    std::cout << "J3DTevBlock::diff() is stubbed" << std::endl;
}

void J3DTevBlockPatched::diffTexNo() {
    std::cout << "J3DTevBlockPatched::diffTexNo() is stubbed" << std::endl;
}

void J3DTevBlockPatched::diffTevStage() {
    std::cout << "J3DTevBlockPatched::diffTevStage() is stubbed" << std::endl;
}

void J3DTevBlockPatched::diffTevStageIndirect() {
    std::cout << "J3DTevBlockPatched::diffTevStageIndirect() is stubbed" << std::endl;
}

void J3DTevBlockPatched::diffTevReg() {
    std::cout << "J3DTevBlockPatched::diffTevReg() is stubbed" << std::endl;
}

void J3DTevBlockPatched::diffTexCoordScale() {
    std::cout << "J3DTevBlockPatched::diffTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock1::diffTexNo() {
    std::cout << "J3DTevBlock1::diffTexNo() is stubbed" << std::endl;
}

void J3DTevBlock1::diffTevReg() {
    std::cout << "J3DTevBlock1::diffTevReg() is stubbed" << std::endl;
}

void J3DTevBlock1::diffTevStage() {
    std::cout << "J3DTevBlock1::diffTevStage() is stubbed" << std::endl;
}

void J3DTevBlock1::diffTevStageIndirect() {
    std::cout << "J3DTevBlock1::diffTevStageIndirect() is stubbed" << std::endl;
}

void J3DTevBlock1::diffTexCoordScale() {
    std::cout << "J3DTevBlock1::diffTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock2::diffTexNo() {
    std::cout << "J3DTevBlock2::diffTexNo() is stubbed" << std::endl;
}

void J3DTevBlock2::diffTevReg() {
    std::cout << "J3DTevBlock2::diffTevReg() is stubbed" << std::endl;
}

void J3DTevBlock2::diffTevStage() {
    std::cout << "J3DTevBlock2::diffTevStage() is stubbed" << std::endl;
}

void J3DTevBlock2::diffTevStageIndirect() {
    std::cout << "J3DTevBlock2::diffTevStageIndirect() is stubbed" << std::endl;
}

void J3DTevBlock2::diffTexCoordScale() {
    std::cout << "J3DTevBlock2::diffTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock4::diffTexNo() {
    std::cout << "J3DTevBlock4::diffTexNo() is stubbed" << std::endl;
}

void J3DTevBlock4::diffTevReg() {
    std::cout << "J3DTevBlock4::diffTevReg() is stubbed" << std::endl;
}

void J3DTevBlock4::diffTevStage() {
    std::cout << "J3DTevBlock4::diffTevStage() is stubbed" << std::endl;
}

void J3DTevBlock4::diffTevStageIndirect() {
    std::cout << "J3DTevBlock4::diffTevStageIndirect() is stubbed" << std::endl;
}

void J3DTevBlock4::diffTexCoordScale() {
    std::cout << "J3DTevBlock4::diffTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock16::diffTexNo() {
    std::cout << "J3DTevBlock16::diffTexNo() is stubbed" << std::endl;
}

void J3DTevBlock16::diffTevReg() {
    std::cout << "J3DTevBlock16::diffTevReg() is stubbed" << std::endl;
}

void J3DTevBlock16::diffTevStage() {
    std::cout << "J3DTevBlock16::diffTevStage() is stubbed" << std::endl;
}

void J3DTevBlock16::diffTevStageIndirect() {
    std::cout << "J3DTevBlock16::diffTevStageIndirect() is stubbed" << std::endl;
}

void J3DTevBlock16::diffTexCoordScale() {
    std::cout << "J3DTevBlock16::diffTexCoordScale() is stubbed" << std::endl;
}

void J3DTevBlock16::ptrToIndex() {
    std::cout << "J3DTevBlock16::ptrToIndex() is stubbed" << std::endl;
}

void J3DTevBlockPatched::ptrToIndex() {
    std::cout << "J3DTevBlockPatched::ptrToIndex() is stubbed" << std::endl;
}

void J3DTevBlock::indexToPtr_private(u32 offs) {
    std::cout << "J3DTevBlock::indexToPtr_private() is stubbed" << std::endl;
}

void J3DIndBlockFull::load() {
    std::cout << "J3DIndBlockFull::load() is stubbed" << std::endl;
}

void J3DIndBlockFull::diff(u32 diffFlags) {
    std::cout << "J3DIndBlockFull::diff() is stubbed" << std::endl;
}

void J3DPEBlockOpa::load() {
    std::cout << "J3DPEBlockOpa::load() is stubbed" << std::endl;
}

void J3DPEBlockTexEdge::load() {
    std::cout << "J3DPEBlockTexEdge::load() is stubbed" << std::endl;
}

void J3DPEBlockXlu::load() {
    std::cout << "J3DPEBlockXlu::load() is stubbed" << std::endl;
}

void J3DPEBlockFogOff::load() {
    std::cout << "J3DPEBlockFogOff::load() is stubbed" << std::endl;
}

void J3DPEBlockFogOff::diffBlend() {
    std::cout << "J3DPEBlockFogOff::diffBlend() is stubbed" << std::endl;
}

void J3DPEBlockFull::load() {
    std::cout << "J3DPEBlockFull::load() is stubbed" << std::endl;
}

void J3DPEBlockFull::patch() {
    std::cout << "J3DPEBlockFull::patch() is stubbed" << std::endl;
}

void J3DPEBlockFull::diffFog() {
    std::cout << "J3DPEBlockFull::diffFog() is stubbed" << std::endl;
}

void J3DPEBlockFull::diffBlend() {
    std::cout << "J3DPEBlockFull::diffBlend() is stubbed" << std::endl;
}

void J3DPEBlockFull::diff(u32 diffFlags) {
    std::cout << "J3DPEBlockFull::diff() is stubbed" << std::endl;
}

void J3DColorBlockLightOff::reset(J3DColorBlock* pBlock) {
    std::cout << "J3DColorBlockLightOff::reset() is stubbed" << std::endl;
}

void J3DColorBlockAmbientOn::reset(J3DColorBlock* pBlock) {
    std::cout << "J3DColorBlockAmbientOn::reset() is stubbed" << std::endl;
}

void J3DColorBlockLightOn::reset(J3DColorBlock* pBlock) {
    std::cout << "J3DColorBlockLightOn::reset() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::reset(J3DTexGenBlock* pBlock) {
    std::cout << "J3DTexGenBlockPatched::reset() is stubbed" << std::endl;
}

void J3DTexGenBlock4::reset(J3DTexGenBlock* pBlock) {
    std::cout << "J3DTexGenBlock4::reset() is stubbed" << std::endl;
}

void J3DTexGenBlockBasic::reset(J3DTexGenBlock* pBlock) {
    std::cout << "J3DTexGenBlockBasic::reset() is stubbed" << std::endl;
}

void J3DTevBlockPatched::reset(J3DTevBlock* pBlock) {
    std::cout << "J3DTevBlockPatched::reset() is stubbed" << std::endl;
}

void J3DTevBlock1::reset(J3DTevBlock* pBlock) {
    std::cout << "J3DTevBlock1::reset() is stubbed" << std::endl;
}

void J3DTevBlock2::reset(J3DTevBlock* pBlock) {
    std::cout << "J3DTevBlock2::reset() is stubbed" << std::endl;
}

void J3DTevBlock4::reset(J3DTevBlock* pBlock) {
    std::cout << "J3DTevBlock4::reset() is stubbed" << std::endl;
}

void J3DTevBlock16::reset(J3DTevBlock* pBlock) {
    std::cout << "J3DTevBlock16::reset() is stubbed" << std::endl;
}

void J3DIndBlockFull::reset(J3DIndBlock* pBlock) {
    std::cout << "J3DIndBlockFull::reset() is stubbed" << std::endl;
}

void J3DPEBlockFogOff::reset(J3DPEBlock* pBlock) {
    std::cout << "J3DPEBlockFogOff::reset() is stubbed" << std::endl;
}

void J3DPEBlockFull::reset(J3DPEBlock* pBlock) {
    std::cout << "J3DPEBlockFull::reset() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::calc(const Mtx modelMtx) {
    std::cout << "J3DTexGenBlockPatched::calc() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::calcWithoutViewMtx(const Mtx modelMtx) {
    std::cout << "J3DTexGenBlockPatched::calcWithoutViewMtx() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::calcPostTexMtx(const Mtx modelMtx) {
    std::cout << "J3DTexGenBlockPatched::calcPostTexMtx() is stubbed" << std::endl;
}

void J3DTexGenBlockPatched::calcPostTexMtxWithoutViewMtx(f32 const (*param_0)[4]) {
    std::cout << "J3DTexGenBlockPatched::calcPostTexMtxWithoutViewMtx() is stubbed" << std::endl;
}
