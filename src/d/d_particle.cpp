#include "d/d_particle.h"
// #include "d/d_jnt_col.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
// #include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "JSystem/J3DGraphAnimator/J3DMaterialAnm.h"
#include "JSystem/JParticle/JPAEmitterManager.h"
#include "JSystem/JParticle/JPAResourceManager.h"
#include "JSystem/JMath/JMATrigonometric.h"
// #include "d/d_s_play.h"
#include <cstdio>
#include "d/d_com_inf_game.h"
// #include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_graphic.h"
/* #include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_player.h" */
#include "SSystem/SComponent/c_math.h"

// TODO: Deduplicate instances of these
#define M_PI 3.14159265358979323846f
#define DEG_TO_RAD(degrees) (degrees * (M_PI / 180.0f))

extern dPa_particleTracePcallBack_c JPTracePCB4;

void dPa_cleanupGX() {
    std::cout << "dPa_cleanupGX() is stubbed" << std::endl;
}

dPa_followEcallBack::dPa_followEcallBack(u8 param_0, u8 param_1) {
    std::cout << "dPa_followEcallBack::dPa_followEcallBack() is stubbed" << std::endl;
}

void dPa_followEcallBack::execute(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_followEcallBack::execute() is stubbed" << std::endl;
}

void dPa_followEcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_followEcallBack::draw() is stubbed" << std::endl;
}

void dPa_followEcallBack::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8) {
    std::cout << "dPa_followEcallBack::setup() is stubbed" << std::endl;
}

void dPa_followEcallBack::end() {
    std::cout << "dPa_followEcallBack::end() is stubbed" << std::endl;
}

dPa_modelEcallBack dPa_modelEcallBack::mEcallback;

dPa_modelPcallBack dPa_modelEcallBack::mPcallback;

dPa_modelEcallBack::model_c* dPa_modelEcallBack::mModel;

static u8 struct_80450E9C;
static u8 struct_80450E9D;

void dPa_light8EcallBack::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8 param_3) {
    std::cout << "dPa_light8EcallBack::setup() is stubbed" << std::endl;
}

void dPa_gen_b_light8EcallBack::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8 param_3) {
    std::cout << "dPa_gen_b_light8EcallBack::setup() is stubbed" << std::endl;
}

void dPa_gen_d_light8EcallBack::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8 param_3) {
    std::cout << "dPa_gen_d_light8EcallBack::setup() is stubbed" << std::endl;
}

static void dPa_group_id_change(u32* param_0, u8* param_1) {
    std::cout << "dPa_group_id_change() is stubbed" << std::endl;
}

static void initiateLighting8(GXColor& param_0, s16 param_1) {
    std::cout << "initiateLighting8() is stubbed" << std::endl;
}

static void initiate_b_Lighting8(GXColor& param_0) {
    std::cout << "initiate_b_Lighting8() is stubbed" << std::endl;
}

static void drawFirst(JPABaseEmitter* i_emitter) {
    std::cout << "drawFirst() is stubbed" << std::endl;
}

static void drawFirst_l8(JPABaseEmitter* i_emitter) {
    std::cout << "drawFirst_l8() is stubbed" << std::endl;
}

static void drawSecond_light8(JPABaseEmitter* i_emitter) {
    std::cout << "drawSecond_light8() is stubbed" << std::endl;
}

static void drawSecond_b_light8(JPABaseEmitter* i_emitter) {
    std::cout << "drawSecond_b_light8() is stubbed" << std::endl;
}

static void static_light8EcallBack(JPABaseEmitter* i_emitter) {
    std::cout << "static_light8EcallBack() is stubbed" << std::endl;
}

static void static_gen_b_light8EcallBack(JPABaseEmitter* i_emitter) {
    std::cout << "static_gen_b_light8EcallBack() is stubbed" << std::endl;
}

static void static_gen_d_light8EcallBack(JPABaseEmitter* i_emitter) {
    std::cout << "static_gen_d_light8EcallBack() is stubbed" << std::endl;
}

void dPa_light8EcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_light8EcallBack::draw() is stubbed" << std::endl;
}

void dPa_gen_b_light8EcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_gen_b_light8EcallBack::draw() is stubbed" << std::endl;
}

void dPa_gen_d_light8EcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_gen_d_light8EcallBack::draw() is stubbed" << std::endl;
}

static void dPa_setWindPower(JPABaseParticle* param_0) {
    std::cout << "dPa_setWindPower() is stubbed" << std::endl;
}

void dPa_modelPcallBack::draw(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_modelPcallBack::draw() is stubbed" << std::endl;
}

bool dPa_modelEcallBack::model_c::set(J3DModelData* i_modelData, dKy_tevstr_c const& param_1, u8 rotAxis, void* param_3, u8 param_4, u8 param_5) {
    std::cout << "dPa_modelEcallBack::model_c::set() is stubbed" << std::endl;
    return false;
}

void dPa_modelEcallBack::model_c::setup() {
    std::cout << "dPa_modelEcallBack::model_c::setup() is stubbed" << std::endl;
}

void dPa_modelEcallBack::model_c::cleanup() {
    std::cout << "dPa_modelEcallBack::model_c::cleanup() is stubbed" << std::endl;
}

void dPa_modelEcallBack::model_c::draw(f32 (*param_0)[4]) {
    std::cout << "dPa_modelEcallBack::model_c::draw() is stubbed" << std::endl;
}

void dPa_modelEcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::draw() is stubbed" << std::endl;
}

void dPa_modelEcallBack::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8 param_3) {
    std::cout << "dPa_modelEcallBack::setup() is stubbed" << std::endl;
}

void dPa_modelEcallBack::create(u8 param_0) {
    std::cout << "dPa_modelEcallBack::create() is stubbed" << std::endl;
}

void dPa_modelEcallBack::remove() {
    std::cout << "dPa_modelEcallBack::remove() is stubbed" << std::endl;
}

int dPa_modelEcallBack::setModel(JPABaseEmitter* i_emitter, J3DModelData* i_modelData, dKy_tevstr_c const& param_2, u8 param_3, void* param_4, u8 param_5, u8 param_6) {
    std::cout << "dPa_modelEcallBack::setModel() is stubbed" << std::endl;
    return 0;
}

void dPa_modelEcallBack::resetModel(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::resetModel() is stubbed" << std::endl;
}

void dPa_modelEcallBack::setupModel(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::setupModel() is stubbed" << std::endl;
}

void dPa_modelEcallBack::drawModel(JPABaseEmitter* i_emitter, f32 (*param_1)[4]) {
    std::cout << "dPa_modelEcallBack::drawModel() is stubbed" << std::endl;
}

void dPa_modelEcallBack::cleanupModel(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::cleanupModel() is stubbed" << std::endl;
}

dPa_modelEcallBack::model_c* dPa_modelEcallBack::getModel(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::getModel() is stubbed" << std::endl;
    return NULL;
}

u8 dPa_modelEcallBack::getRotAxis(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_modelEcallBack::getRotAxis() is stubbed" << std::endl;
    return 0;
}

void dPa_selectTexEcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_selectTexEcallBack::draw() is stubbed" << std::endl;
}

dPa_simpleEcallBack::dPa_simpleEcallBack() {
    std::cout << "dPa_simpleEcallBack::dPa_simpleEcallBack() is stubbed" << std::endl;
}

void dPa_simpleEcallBack::executeAfter(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_simpleEcallBack::executeAfter() is stubbed" << std::endl;
}

void dPa_simpleEcallBack::draw(JPABaseEmitter* i_emitter) {
    std::cout << "dPa_simpleEcallBack::draw() is stubbed" << std::endl;
}

JPABaseEmitter* dPa_simpleEcallBack::create(JPAEmitterManager* param_0, u16 id, u8 param_2) {
    std::cout << "dPa_simpleEcallBack::create() is stubbed" << std::endl;
    return NULL;
}

dPa_simpleData_c::~dPa_simpleData_c() {
    std::cout << "dPa_simpleData_c::~dPa_simpleData_c() is stubbed" << std::endl;
}

dPa_simpleData_c::dPa_simpleData_c() {
    std::cout << "dPa_simpleData_c::dPa_simpleData_c() is stubbed" << std::endl;
}

JPABaseEmitter* dPa_simpleEcallBack::createEmitter(JPAEmitterManager* param_0) {
    std::cout << "dPa_simpleEcallBack::createEmitter() is stubbed" << std::endl;
    return NULL;
}

u32 dPa_simpleEcallBack::set(cXyz const* i_pos, dKy_tevstr_c const* param_2, u8 param_3, GXColor const& param_4, GXColor const& param_5, int param_6, f32 param_7) {
    std::cout << "dPa_simpleEcallBack::set() is stubbed" << std::endl;
    return 0;
}

void dPa_windPcallBack::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_windPcallBack::execute() is stubbed" << std::endl;
}

void dPa_control_c::level_c::emitter_c::onActive() {
    std::cout << "dPa_control_c::level_c::emitter_c::onActive() is stubbed" << std::endl;
}

void dPa_control_c::level_c::emitter_c::entry(u32 id, u16 name, JPABaseEmitter* i_emitter, dPa_levelEcallBack* p_callback) {
    std::cout << "dPa_control_c::level_c::emitter_c::entry() is stubbed" << std::endl;
}

void dPa_control_c::level_c::emitter_c::cleanup() {
    std::cout << "dPa_control_c::level_c::emitter_c::cleanup() is stubbed" << std::endl;
}

dPa_control_c::level_c::level_c() {
    std::cout << "dPa_control_c::level_c::level_c() is stubbed" << std::endl;
}

void dPa_control_c::level_c::execute(dPa_control_c::level_c::emitter_c* i_emitter) {
    std::cout << "dPa_control_c::level_c::execute(emitter_c*) is stubbed" << std::endl;
}

void dPa_control_c::level_c::execute() {
    std::cout << "dPa_control_c::level_c::execute() is stubbed" << std::endl;
}

void dPa_control_c::level_c::cleanup() {
    std::cout << "dPa_control_c::level_c::cleanup() is stubbed" << std::endl;
}

dPa_control_c::level_c::emitter_c* dPa_control_c::level_c::get(u32 id) {
    std::cout << "dPa_control_c::level_c::get() is stubbed" << std::endl;
    return NULL;
}

void dPa_control_c::level_c::forceOnEventMove(u32 id) {
    std::cout << "dPa_control_c::level_c::forceOnEventMove() is stubbed" << std::endl;
}

void dPa_control_c::level_c::allForceOnEventMove() {
    std::cout << "dPa_control_c::level_c::allForceOnEventMove() is stubbed" << std::endl;
}

JPABaseEmitter* dPa_control_c::level_c::getEmitter(u32 id) {
    std::cout << "dPa_control_c::level_c::getEmitter() is stubbed" << std::endl;
    return NULL;
}

u32 dPa_control_c::level_c::entry(u16 i_name, JPABaseEmitter* i_emitter, dPa_levelEcallBack* i_callback) {
    std::cout << "dPa_control_c::level_c::entry() is stubbed" << std::endl;
    return 0;
}

void dPa_control_c::level_c::addTable(dPa_control_c::level_c::emitter_c* i_emitter) {
    std::cout << "dPa_control_c::level_c::addTable() is stubbed" << std::endl;
}

void dPa_control_c::level_c::cutTable(dPa_control_c::level_c::emitter_c* i_emitter) {
    std::cout << "dPa_control_c::level_c::cutTable() is stubbed" << std::endl;
}

dPa_selectTexEcallBack dPa_control_c::mTsubo[] = {
    dPa_selectTexEcallBack(0),
    dPa_selectTexEcallBack(1),
    dPa_selectTexEcallBack(2),
    dPa_selectTexEcallBack(3),
    dPa_selectTexEcallBack(4),
    dPa_selectTexEcallBack(5),
    dPa_selectTexEcallBack(6),
    dPa_selectTexEcallBack(7),
};

static GXColor l_lifeBallColor[3] = {
    {0xEB, 0x20, 0x78, 0xFF},
    {0x20, 0xF1, 0x9B, 0xFF},
    {0xEB, 0xD7, 0x2F, 0xFF},
};

dPa_setColorEcallBack dPa_control_c::mLifeBall[3] = {
    dPa_setColorEcallBack(l_lifeBallColor[0]),
    dPa_setColorEcallBack(l_lifeBallColor[1]),
    dPa_setColorEcallBack(l_lifeBallColor[2]),
};

JPAEmitterManager* dPa_control_c::mEmitterMng;

dPa_wbPcallBack_c dPa_control_c::mWaterBubblePcallBack;

dPa_fsenthPcallBack dPa_control_c::mFsenthPcallBack;

dPa_light8EcallBack dPa_control_c::mLight8EcallBack;

dPa_light8PcallBack dPa_control_c::mLight8PcallBack;

dPa_gen_b_light8EcallBack dPa_control_c::m_b_Light8EcallBack;

dPa_gen_b_light8PcallBack dPa_control_c::m_b_Light8PcallBack;

dPa_gen_d_light8EcallBack dPa_control_c::m_d_Light8EcallBack;

dPa_gen_d_light8PcallBack dPa_control_c::m_d_Light8PcallBack;

u8 dPa_control_c::mStatus;

Mtx dPa_control_c::mWindViewMatrix;

dPa_particleTracePcallBack_c dPa_control_c::mParticleTracePCB;

dPa_control_c::dPa_control_c() {
    std::cout << "dPa_control_c::dPa_control_c() is stubbed" << std::endl;
}

u8 dPa_control_c::getRM_ID(u16 param_0) {
    std::cout << "dPa_control_c::getRM_ID() is stubbed" << std::endl;
    return 0;
}

void dPa_control_c::createCommon(void const* param_0) {
    std::cout << "dPa_control_c::createCommon() is stubbed" << std::endl;
}

void dPa_control_c::createRoomScene() {
    std::cout << "dPa_control_c::createRoomScene() is stubbed" << std::endl;
}

bool dPa_control_c::readScene(u8 param_0, mDoDvdThd_toMainRam_c** param_1) {
    std::cout << "dPa_control_c::readScene() is stubbed" << std::endl;
    return false;
}

void dPa_control_c::createScene(void const* param_0) {
    std::cout << "dPa_control_c::createScene() is stubbed" << std::endl;
}

bool dPa_control_c::removeRoomScene(bool param_0) {
    std::cout << "dPa_control_c::removeRoomScene() is stubbed" << std::endl;
    return false;
}

void dPa_control_c::removeScene(bool param_0) {
    std::cout << "dPa_control_c::removeScene() is stubbed" << std::endl;
}

void dPa_control_c::cleanup() {
    std::cout << "dPa_control_c::cleanup() is stubbed" << std::endl;
}

void dPa_control_c::calc3D() {
    std::cout << "dPa_control_c::calc3D() is stubbed" << std::endl;
}

void dPa_control_c::calc2D() {
    std::cout << "dPa_control_c::calc2D() is stubbed" << std::endl;
}

void dPa_control_c::calcMenu() {
    std::cout << "dPa_control_c::calcMenu() is stubbed" << std::endl;
}

void dPa_control_c::draw(JPADrawInfo* param_0, u8 param_1) {
    std::cout << "dPa_control_c::draw() is stubbed" << std::endl;
}

void dPa_control_c::setHitMark(u16 param_1, fopAc_ac_c* param_2, cXyz const* param_3, csXyz const* param_4, cXyz const* param_5, u32 param_6) {
    std::cout << "dPa_control_c::setHitMark() is stubbed" << std::endl;
}

void dPa_control_c::setWaterRipple(u32* param_0, cBgS_PolyInfo& param_1, cXyz const* param_2, f32 param_3, dKy_tevstr_c const* param_4, cXyz const* param_5, s8 param_6) {
    std::cout << "dPa_control_c::setWaterRipple() is stubbed" << std::endl;
}

JPABaseEmitter* dPa_control_c::set(u8 param_0, u16 param_1, cXyz const* i_pos, dKy_tevstr_c const* param_3, csXyz const* i_rotation, cXyz const* i_scale, u8 i_alpha, dPa_levelEcallBack* param_7, s8 param_8, GXColor const* param_9, GXColor const* param_10, cXyz const* param_11, f32 param_12) {
    std::cout << "dPa_control_c::set() is stubbed" << std::endl;
    return NULL;
}

s32 dPa_control_c::getPolyColor(cBgS_PolyInfo& param_0, int param_1, GXColor* param_2, GXColor* param_3, u8* param_4, f32* param_5) {
    std::cout << "dPa_control_c::getPolyColor() is stubbed" << std::endl;
    return 0;
}

JPABaseEmitter* dPa_control_c::setPoly(u16 param_0, cBgS_PolyInfo& param_1, cXyz const* param_2, dKy_tevstr_c const* param_3, csXyz const* param_4, cXyz const* param_5, int param_6, dPa_levelEcallBack* param_7, s8 param_8, cXyz const* param_9) {
    std::cout << "dPa_control_c::setPoly() is stubbed" << std::endl;
    return NULL;
}

void dummy3() {
    std::cout << "dummy3() is stubbed" << std::endl;
}

bool dPa_control_c::newSimple(u16 param_0, u8 param_1, u32* param_2) {
    std::cout << "dPa_control_c::newSimple() is stubbed" << std::endl;
    return false;
}

u32 dPa_control_c::setSimple(u16 param_0, cXyz const* i_pos, dKy_tevstr_c const* param_2, u8 param_3, GXColor const& param_4, GXColor const& param_5, int param_6, f32 param_7) {
    std::cout << "dPa_control_c::setSimple() is stubbed" << std::endl;
    return 0;
}

dPa_simpleEcallBack* dPa_control_c::getSimple(u16 param_0) {
    std::cout << "dPa_control_c::getSimple() is stubbed" << std::endl;
    return NULL;
}

static void dPa_kankyocolor_set(f32 param_0, JPABaseEmitter* param_1, dKy_tevstr_c const* param_2, u32 param_3, cXyz const* param_4, GXColor const* param_5, GXColor const* param_6) {
    std::cout << "dPa_kankyocolor_set() is stubbed" << std::endl;
}

u32 dPa_control_c::set(u32 param_0, u8 param_1, u16 param_2, cXyz const* pos, dKy_tevstr_c const* param_4, csXyz const* i_rotation, cXyz const* i_scale, u8 alpha, dPa_levelEcallBack* param_8, s8 param_9, GXColor const* param_10, GXColor const* param_11, cXyz const* param_12, f32 param_13) {
    std::cout << "dPa_control_c::set(u32, ...) is stubbed" << std::endl;
    return 0;
}

u32 dPa_control_c::setPoly(u32 param_0, u16 param_1, cBgS_PolyInfo& param_2, cXyz const* param_3, dKy_tevstr_c const* param_4, csXyz const* param_5, cXyz const* param_6, int param_7, dPa_levelEcallBack* param_8, s8 param_9, cXyz const* param_10) {
    std::cout << "dPa_control_c::setPoly(u32, ...) is stubbed" << std::endl;
    return 0;
}

u32 dPa_control_c::setStopContinue(u32 param_0) {
    std::cout << "dPa_control_c::setStopContinue() is stubbed" << std::endl;
    return 0;
}

u32 dPa_control_c::setSimpleFoot(u32 param_0, u32* param_1, cBgS_PolyInfo& param_2, cXyz const* param_3, dKy_tevstr_c const* param_4, int param_5, csXyz const* param_6, cXyz const* param_7, dPa_levelEcallBack* param_8, s8 param_9, cXyz const* param_10) {
    std::cout << "dPa_control_c::setSimpleFoot() is stubbed" << std::endl;
    return 0;
}

u16 dPa_control_c::setCommonPoly(u32* param_0, cBgS_PolyInfo* param_1, cXyz const* param_2, cXyz const* param_3, dKy_tevstr_c const* param_4, u32 param_5, u32 param_6, csXyz const* param_7, cXyz const* param_8, s8 param_9) {
    std::cout << "dPa_control_c::setCommonPoly() is stubbed" << std::endl;
    return 0;
}

void dPa_wbPcallBack_c::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_wbPcallBack_c::execute() is stubbed" << std::endl;
}

void dPa_fsenthPcallBack::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_fsenthPcallBack::execute() is stubbed" << std::endl;
}

void dPa_fsenthPcallBack::draw(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_fsenthPcallBack::draw() is stubbed" << std::endl;
}

void dPa_light8PcallBack::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_light8PcallBack::execute() is stubbed" << std::endl;
}

void dPa_gen_b_light8PcallBack::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_gen_b_light8PcallBack::execute() is stubbed" << std::endl;
}

void dPa_gen_d_light8PcallBack::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_gen_d_light8PcallBack::execute() is stubbed" << std::endl;
}

void dPa_light8PcallBack::draw(JPABaseEmitter* param_1, JPABaseParticle* param_2) {
    std::cout << "dPa_light8PcallBack::draw() is stubbed" << std::endl;
}

void dPa_gen_b_light8PcallBack::draw(JPABaseEmitter* param_1, JPABaseParticle* param_2) {
    std::cout << "dPa_gen_b_light8PcallBack::draw() is stubbed" << std::endl;
}

void dPa_gen_d_light8PcallBack::draw(JPABaseEmitter* param_1, JPABaseParticle* param_2) {
    std::cout << "dPa_gen_d_light8PcallBack::draw() is stubbed" << std::endl;
}

void dPa_hermiteEcallBack_c::setOldPosP(cXyz const* param_0, cXyz const* param_1) {
    std::cout << "dPa_hermiteEcallBack_c::setOldPosP() is stubbed" << std::endl;
}

void dPa_hermiteEcallBack_c::executeAfter(JPABaseEmitter* param_1) {
    std::cout << "dPa_hermiteEcallBack_c::executeAfter() is stubbed" << std::endl;
}

void dPa_hermiteEcallBack_c::setup(JPABaseEmitter* i_emitter, cXyz const* param_1, csXyz const* param_2, s8 param_3) {
    std::cout << "dPa_hermiteEcallBack_c::setup() is stubbed" << std::endl;
}

void dPa_particleTracePcallBack_c::execute(JPABaseEmitter* i_emitter, JPABaseParticle* param_1) {
    std::cout << "dPa_particleTracePcallBack_c::execute() is stubbed" << std::endl;
}
