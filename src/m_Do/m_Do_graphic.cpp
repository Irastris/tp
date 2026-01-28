// #include "d/dolzel.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DPrint.h"
// #include "JSystem/JAWExtSystem/JAWExtSystem.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JParticle/JPADrawInfo.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "SSystem/SComponent/c_math.h"
// #include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
/* #include "d/d_menu_collect.h"
#include "d/d_jcam_editor.h"
#include "d/d_jpreviewer.h"
#include <dolphin/base/PPCArch.h> */
#include "f_ap/f_ap_game.h"
// #include "f_op/f_op_camera_mng.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_machine.h"
#include "m_Do/m_Do_main.h"
/* #include "d/d_meter2_info.h"
#include "d/d_s_play.h"
#include "DynamicLink.h" */

class mDoGph_HIO_c : public JORReflexible {
public:
    mDoGph_HIO_c() {
        id = 0;
    }

    void entryHIO() {
        if (id == 0) {
            id = mDoHIO_CREATE_CHILD("グラフィック", this);
        }
    }

    void listenPropertyEvent(const JORPropertyEvent*) {}
    void genMessage(JORMContext*) {}

    s8 id;
};

static void drawQuad(f32 param_0, f32 param_1, f32 param_2, f32 param_3) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(param_0, param_1);
    GXPosition2f32(param_2, param_1);
    GXPosition2f32(param_2, param_3);
    GXPosition2f32(param_0, param_3);
    GXEnd();
}

static ResTIMG* createTimg(u16 width, u16 height, u32 format) {
    u32 bufferSize = GXGetTexBufferSize(width, height, format, GX_FALSE, 0) + 0x20;
    ResTIMG* timg;

    timg = (ResTIMG*)JKRAlloc(bufferSize, 0x20);

    if (timg == NULL) {
        return NULL;
    }

    cLib_memSet(timg, 0, bufferSize);
    timg->format = format;
    timg->alphaEnabled = false;
    timg->width = width;
    timg->height = height;
    timg->minFilter = GX_LINEAR;
    timg->magFilter = GX_LINEAR;
    timg->mipmapCount = 1;
    timg->imageOffset = 0x20;
    return timg;
}

JUTFader* mDoGph_gInf_c::mFader;

ResTIMG* mDoGph_gInf_c::mFrameBufferTimg;

void* mDoGph_gInf_c::mFrameBufferTex;

ResTIMG* mDoGph_gInf_c::mZbufferTimg;

void* mDoGph_gInf_c::mZbufferTex;

f32 mDoGph_gInf_c::mFadeRate;

f32 mDoGph_gInf_c::mFadeSpeed;

GXColor mDoGph_gInf_c::mBackColor = {0, 0, 0, 0};

GXColor mDoGph_gInf_c::mFadeColor = {0, 0, 0, 0};

u8 mDoGph_gInf_c::mBlureFlag;

u8 mDoGph_gInf_c::mBlureRate;

u8 mDoGph_gInf_c::mFade;

bool mDoGph_gInf_c::mAutoForcus;

void mDoGph_gInf_c::create() {
    JFWDisplay::createManager(JKRHeap::sCurrentHeap, JUTXfb::UNK_2, true);

    JFWDisplay::getManager()->setDrawDoneMethod(JFWDisplay::UNK_METHOD_1);

    JUTFader* faderPtr = new JUTFader(0, 0, JUTVideo::getManager()->getRenderMode()->fbWidth, JUTVideo::getManager()->getRenderMode()->efbHeight, JUtility::TColor(0, 0, 0, 0));
    setFader(faderPtr);
    JFWDisplay::getManager()->setFader(faderPtr);

    mFrameBufferTimg = createTimg(FB_WIDTH / 2, FB_HEIGHT / 2, 6);
    mFrameBufferTex = (char*)mFrameBufferTimg + sizeof(ResTIMG);

    mZbufferTimg = createTimg(FB_WIDTH / 2, FB_HEIGHT / 2, 3);
    mZbufferTex = (char*)mZbufferTimg + sizeof(ResTIMG);

    J2DPrint::setBuffer(0x400);
    mBlureFlag = false;
    mFade = 0;

    mBackColor = g_clearColor;
    mFadeColor = g_clearColor;

    VISetBlack(TRUE);
}

static bool data_80450BE8;

void mDoGph_gInf_c::beginRender() {
    if (data_80450BE8) {
        JUTXfb::getManager()->setDrawingXfbIndex(-1);
    }

    JFWDisplay::getManager()->beginRender();
}

void mDoGph_gInf_c::fadeOut(f32 fadeSpeed, GXColor& fadeColor) {
    mFade = 1;
    mFadeSpeed = fadeSpeed;
    mFadeColor = fadeColor;
    mFadeRate = fadeSpeed >= 0.0f ? 0.0f : 1.0f;
}

void mDoGph_gInf_c::fadeOut_f(f32 fadeSpeed, GXColor& fadeColor) {
    mFade = 129;
    mFadeSpeed = fadeSpeed;
    mFadeColor = fadeColor;
    mFadeRate = fadeSpeed >= 0.0f ? 0.0f : 1.0f;
}

void mDoGph_gInf_c::onBlure() {
    onBlure(cMtx_getIdentity());
}

GXTexObj mDoGph_gInf_c::mFrameBufferTexObj;

GXTexObj mDoGph_gInf_c::mZbufferTexObj;

mDoGph_gInf_c::bloom_c mDoGph_gInf_c::m_bloom;

Mtx mDoGph_gInf_c::mBlureMtx;

void mDoGph_gInf_c::onBlure(const Mtx m) {
    mBlureFlag = true;
    setBlureMtx(m);
}

void mDoGph_gInf_c::fadeOut(f32 fadeSpeed) {
    fadeOut(fadeSpeed, g_clearColor);
}

void darwFilter(GXColor matColor) {
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetZCompLoc(GX_ENABLE);
    GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    // GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_ENABLE);
    GXSetNumIndStages(0);

    Mtx44 mtx;
    C_MTXOrtho(mtx, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 10.0f);
    GXSetProjection(mtx, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(cMtx_getIdentity(), GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, matColor);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGB8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s8(0, 0, -5);
    GXPosition3s8(1, 0, -5);
    GXPosition3s8(1, 1, -5);
    GXPosition3s8(0, 1, -5);
    GXEnd();
}

void mDoGph_gInf_c::calcFade() {
    if (mDoGph_gInf_c::mFade != 0) {
        mFadeRate += mFadeSpeed;

        if (mFadeRate < 0.0f) {
            mFadeRate = 0.0f;
            mDoGph_gInf_c::mFade = 0;
        } else {
            if (mFadeRate > 1.0f) {
                mFadeRate = 1.0f;
            }
        }
        mFadeColor.a = 255.0f * mFadeRate;
    } else {
        if (dComIfG_getBrightness() != 255) {
            mFadeColor.r = 0;
            mFadeColor.g = 0;
            mFadeColor.b = 0;
            mFadeColor.a = 255 - dComIfG_getBrightness();
        } else {
            mFadeColor.a = 0;
        }
    }

    if (mFadeColor.a != 0) {
        darwFilter(mFadeColor);
    }
}

void mDoGph_BlankingON() {
    // No-op
}

void mDoGph_BlankingOFF() {
    // No-op
}

static void dScnPly_BeforeOfPaint() {
    dComIfGd_reset();
}

int mDoGph_BeforeOfDraw() {
    dScnPly_BeforeOfPaint();
    return 1;
}

int mDoGph_AfterOfDraw() {
    GXSetZCompLoc(GX_ENABLE);
    GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    // GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetCoPlanar(GX_DISABLE);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
    GXSetDither(GX_ENABLE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetCullMode(GX_CULL_NONE);

    JUTVideo::getManager()->setRenderMode(mDoMch_render_c::getRenderModeObj());
    mDoGph_gInf_c::endFrame();
    return 1;
}

static void drawDepth2(view_class* param_0, view_port_class* param_1, int param_2) {
    static GXColorS10 l_tevColor0 = {0, 0, 0, 0};

    if (daPy_getLinkPlayerActorClass() != NULL) {
        if (mDoGph_gInf_c::isAutoForcus()) {
            f32 sp4C[7];
            f32 sp34[6];
            f32 sp1C;
            f32 sp18;
            f32 sp14;
            GXGetProjectionv(sp4C);
            GXGetViewportv(sp34);
            GXProject(param_0->lookat.center.x, param_0->lookat.center.y, param_0->lookat.center.z, param_0->viewMtx, sp4C, sp34, &sp1C, &sp18, &sp14);
            
            param_2 = (0xFF0000 - (int)(16777215.0f * sp14)) >> 8;
            param_2 = cLib_minMaxLimit<int>(param_2, -0x400, 0);
        }

        fopAc_ac_c* player_p = dComIfGp_getPlayer(0);
        camera_class* camera_p = (camera_class*)dComIfGp_getCamera(0);
        f32 var_f31;
        f32 var_f29;
        f32 var_f28 = -255.0f;

        if (dCam_getBody()->Mode() != 4 && dCam_getBody()->Mode() != 7) {
            int cam_id = dComIfGp_getPlayerCameraID(0);
            camera_class* temp_r4 = dComIfGp_getCamera(cam_id);
            dAttention_c* attention = dComIfGp_getAttention();

            f32 var_f30;
            if (temp_r4 != NULL) {
                var_f30 = fopCamM_GetFovy(temp_r4);
            } else {
                var_f30 = 48.0f;
            }
            var_f30 = 60.0f / var_f30;

            if (attention->LockonTruth()) {
                fopAc_ac_c* atn_actor =
                    fopAcM_SearchByID(daPy_getLinkPlayerActorClass()->getAtnActorID());

                if (atn_actor != NULL) {
                    cXyz sp28;
                    sp28 = atn_actor->eyePos;
                    if (std::fabs(sp28.y - camera_p->lookat.eye.y) < 400.0f) {
                        sp28.y = camera_p->lookat.eye.y;
                    }

                    var_f29 = atn_actor->current.pos.abs(camera_p->lookat.eye);
                    var_f31 = var_f29 / ((SREG_F(2) + 280.0f) * var_f30);
                    var_f31 -= 0.8f;
                    if (var_f31 < 0.0f) {
                        var_f31 = 0.0f;
                    } else if (var_f31 > 1.0f) {
                        var_f31 = 1.0f;
                    }
                    var_f28 = -180.0f - 75.0f * var_f31;
                }
            } /* else if (dComIfGp_event_runCheck() && var_f30 < 3.0f && g_env_light.field_0x126c < 999999.0f) {
                var_f29 = g_env_light.field_0x126c;
                var_f31 = var_f29 / ((SREG_F(2) + 80.0f) * var_f30);
                var_f31 -= 0.8f;
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                } else if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                var_f28 = -180.0f - 75.0f * var_f31;
            } */
        }

        /* cLib_addCalc(&g_env_light.field_0x1264, var_f28, SREG_F(5) + 0.1f, SREG_F(4) + 100.0f, 0.0001f);
        l_tevColor0.a = g_env_light.field_0x1264; */
        if (l_tevColor0.a <= -254) {
            l_tevColor0.a = -255;
        }

        s16 x_orig = (int)param_1->x_orig & ~7;
        s16 y_orig = (int)param_1->y_orig & ~7;
        s16 y_orig_pos = y_orig < 0 ? 0 : y_orig;

        s16 width = (int)param_1->width & ~7;
        s16 height = (int)param_1->height & ~7;

        void* zBufferTex = (void*)mDoGph_gInf_c::getZbufferTex();
        void* frameBufferTex = (void*)mDoGph_gInf_c::getFrameBufferTex();

        if (y_orig < 0) {
            height += y_orig;
            y_orig = -y_orig >> 1;
            zBufferTex = (char*)zBufferTex + GXGetTexBufferSize(FB_WIDTH / 2, y_orig, GX_TF_IA8, GX_FALSE, 0);
            frameBufferTex = (char*)frameBufferTex + GXGetTexBufferSize(FB_WIDTH / 2, y_orig, mDoGph_gInf_c::getFrameBufferTimg()->format, GX_FALSE, 0);
        }

        u16 halfWidth = width >> 1;
        u16 halfHeight = height >> 1;
        GXRenderModeObj* sp24 = JUTGetVideoManager()->getRenderMode();
        GXSetCopyFilter(GX_FALSE, NULL, GX_TRUE, sp24->vfilter);
        GXSetTexCopySrc(x_orig, y_orig_pos, width, height);
        GXSetTexCopyDst(halfWidth, halfHeight, GX_TF_Z16, GX_TRUE);
        GXCopyTex(zBufferTex, GX_FALSE);
        GXSetTexCopySrc(x_orig, y_orig_pos, width, height);
        GXSetTexCopyDst(halfWidth, halfHeight, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_TRUE);
        GXCopyTex(frameBufferTex, GX_FALSE);
        GXInitTexObj(mDoGph_gInf_c::getZbufferTexObj(), zBufferTex, halfWidth, halfHeight, GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(mDoGph_gInf_c::getZbufferTexObj(), GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXInitTexObj(mDoGph_gInf_c::getFrameBufferTexObj(), frameBufferTex, halfWidth, halfHeight, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(mDoGph_gInf_c::getFrameBufferTexObj(), GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXPixModeSync();
        GXInvalidateTexAll();
        GXLoadTexObj(mDoGph_gInf_c::getFrameBufferTexObj(), GX_TEXMAP1);
        GXLoadTexObj(mDoGph_gInf_c::getZbufferTexObj(), GX_TEXMAP0);

        /* if (0.0f != g_env_light.mDemoAttentionPoint) {
            if (g_env_light.mDemoAttentionPoint >= 0.0f) {
                l_tevColor0.a = -254.0f + 509.0f * g_env_light.mDemoAttentionPoint;
            } else {
                l_tevColor0.a = -254.0f + 509.0f * (1.0f + g_env_light.mDemoAttentionPoint);
            }
        } */

        GXSetTevColorS10(GX_TEVREG0, l_tevColor0);
        GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP3);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_EQ, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);

        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD2, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_CPREV, GX_CC_TEXC, GX_CC_HALF, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetZCompLoc(GX_TRUE);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        /* if (g_env_light.mDemoAttentionPoint >= 0.0f) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, 0);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCALPHA, GX_BL_SRCALPHA, GX_LO_CLEAR);
            GXSetAlphaCompare(GX_LESS, 0xff, GX_AOP_OR, GX_LESS, 0xff);
        } */

        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
        GXSetCullMode(GX_CULL_NONE);
        GXSetDither(GX_TRUE);
        GXSetNumIndStages(0);
        Mtx44 ortho;
        C_MTXOrtho(ortho, param_1->y_orig, param_1->y_orig + param_1->height, param_1->x_orig, param_1->x_orig + param_1->width, 0.0f, 10.0f);
        GXLoadPosMtxImm(cMtx_getIdentity(), 0);

        mDoMtx_stack_c::transS(0.0025f, 0.0025f, 0.0f);
        GXLoadTexMtxImm(mDoMtx_stack_c::get(), 0x1e, GX_MTX2x4);

        mDoMtx_stack_c::transS(-0.0025f, -0.0025f, 0.0f);
        GXLoadTexMtxImm(mDoMtx_stack_c::get(), 0x21, GX_MTX2x4);

        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_S8, 0);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3c);
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x1e);
        GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, 0x21);
        GXSetNumChans(0);
        GXSetNumTexGens(3);
        GXSetNumTevStages(4);
        GXSetProjection(ortho, GX_ORTHOGRAPHIC);
        GXSetCurrentMtx(0);

        if (l_tevColor0.a > -255) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3s16(x_orig, y_orig_pos, -5);
            GXTexCoord2s8(0, 0);
            GXPosition3s16(width, y_orig_pos, -5);
            GXTexCoord2s8(1, 0);
            GXPosition3s16(width, height, -5);
            GXTexCoord2s8(1, 1);
            GXPosition3s16(x_orig, height, -5);
            GXTexCoord2s8(0, 1);
            GXEnd();
        }

        GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetProjection(param_0->projMtx, GX_PERSPECTIVE);
    }
}

static void trimming(view_class* param_0, view_port_class* param_1) {
    s16 y_orig = (int)param_1->y_orig & ~7;
    s16 y_orig_pos = y_orig < 0 ? 0 : y_orig;
    if ((y_orig_pos == 0) && (param_1->scissor.y_orig != param_1->y_orig ||
                              (param_1->scissor.height != param_1->height)))
    {
        s32 sc_top = (int)param_1->scissor.y_orig;
        s32 sc_bottom = param_1->scissor.y_orig + param_1->scissor.height;
        GXSetNumChans(1);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetZCompLoc(1);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
        GXSetCullMode(GX_CULL_NONE);
        GXSetDither(GX_TRUE);
        GXSetNumIndStages(0);
        Mtx44 ortho;
        C_MTXOrtho(ortho, 0.0f, FB_HEIGHT, 0.0f, FB_WIDTH, 0.0f, 10.0f);
        GXLoadPosMtxImm(cMtx_getIdentity(), 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
        GXSetProjection(ortho, GX_ORTHOGRAPHIC);
        GXSetCurrentMtx(0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 8);
        GXPosition3s16(0, 0, -5);
        GXPosition3s16(FB_WIDTH, 0, -5);
        GXPosition3s16(FB_WIDTH, sc_top, -5);
        GXPosition3s16(0, sc_top, -5);
        GXPosition3s16(0, sc_bottom, -5);
        GXPosition3s16(FB_WIDTH, sc_bottom, -5);
        GXPosition3s16(FB_WIDTH, FB_HEIGHT, -5);
        GXPosition3s16(0, FB_HEIGHT, -5);
        GXEnd();
    }

    GXSetScissor(param_1->scissor.x_orig, param_1->scissor.y_orig, param_1->scissor.width, param_1->scissor.height);
}

void mDoGph_drawFilterQuad(s8 param_0, s8 param_1) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2s8(0, 0);
    GXTexCoord2s8(0, 0);
    GXPosition2s8(param_0, 0);
    GXTexCoord2s8(1, 0);
    GXPosition2s8(param_0, param_1);
    GXTexCoord2s8(1, 1);
    GXPosition2s8(0, param_1);
    GXTexCoord2s8(0, 1);
    GXEnd();
}

void mDoGph_gInf_c::bloom_c::create() {
    if (m_buffer == NULL) {
        u32 size = GXGetTexBufferSize(FB_WIDTH / 2, FB_HEIGHT / 2, 6, GX_FALSE, 0);
        m_buffer = mDoExt_getArchiveHeap()->alloc(size, -32);

        mEnable = false;
        mMode = 0;
        mPoint = 128;
        mBlureSize = 64;
        mBlureRatio = 128;
        mBlendColor = (GXColor){255, 255, 255, 255};
    }
}

void mDoGph_gInf_c::bloom_c::remove() {
    if (m_buffer != NULL) {
        mDoExt_getArchiveHeap()->free(m_buffer);
        m_buffer = NULL;
    }
    mMonoColor.a = 0;
}

void mDoGph_gInf_c::bloom_c::draw() {
    bool enabled = mEnable && m_buffer != NULL;

    if (mMonoColor.a != 0 || enabled) {
        GXSetViewport(0.0f, 0.0f, FB_WIDTH, FB_HEIGHT, 0.0f, 1.0f);
        GXSetScissor(0, 0, FB_WIDTH, FB_HEIGHT);
        GXLoadTexObj(getFrameBufferTexObj(), GX_TEXMAP0);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3c);
        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_GREEN);
        GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
        GXSetZCompLoc(1);
        GXSetZMode(0, GX_ALWAYS, 0);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
        // GXSetFogRangeAdj(0, 0, 0);
        GXSetCullMode(GX_CULL_NONE);
        GXSetDither(1);
        Mtx44 ortho;
        C_MTXOrtho(ortho, 0.0f, 4.0f, 0.0f, 4.0f, 0.0f, 10.0f);
        GXLoadPosMtxImm(cMtx_getIdentity(), 0);
        GXSetProjection(ortho, GX_ORTHOGRAPHIC);
        GXSetCurrentMtx(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGB8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8, 0);
        if (mMonoColor.a != 0) {
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A2);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
            GXSetTevColor(GX_TEVREG2, mMonoColor);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
            mDoGph_drawFilterQuad(4, 4);
        }
        if (enabled) {
            GXSetTexCopySrc(0, 0, FB_WIDTH / 2, FB_HEIGHT / 2);
            GXSetTexCopyDst(FB_WIDTH / 2, FB_HEIGHT / 2, GX_TF_RGBA8, 0);
            GXCopyTex(m_buffer, 0);
            GXSetNumTevStages(3);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_TEXA, GX_CC_HALF, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_CPREV, GX_CC_HALF, GX_CC_C0);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP3, GX_TEV_SWAP3);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_OR);
            GXColorS10 tevColor0 = {(s16)-mPoint, (s16)-mPoint, (s16)-mPoint, 0x40};
            GXSetTevColorS10(GX_TEVREG0, tevColor0);
            GXColor tevColor1 = {mBlureRatio, mBlureRatio, mBlureRatio, mBlureRatio};
            GXSetTevColor(GX_TEVREG1, tevColor1);
            GXPixModeSync();
            mDoGph_drawFilterQuad(2, 2);
            GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
            void* zBufferTex = getZbufferTex();
            GXSetTexCopySrc(0, 0, FB_WIDTH / 2, FB_HEIGHT / 2);
            GXSetTexCopyDst(FB_WIDTH / 4, FB_HEIGHT / 4, GX_TF_RGBA8, GX_TRUE);
            GXCopyTex(zBufferTex, 0);
            GXTexObj auStack_c0;
            GXInitTexObj(&auStack_c0, zBufferTex, FB_WIDTH / 4, FB_HEIGHT / 4, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&auStack_c0, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&auStack_c0, GX_TEXMAP0);
            GXSetNumTexGens(8);
            u32 iVar11 = 0x1e;
            int sVar10 = 0;
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3c);
            for (int texCoord = (int)GX_TEXCOORD1; texCoord < (int)GX_MAX_TEXCOORD; texCoord++) {
                GXSetTexCoordGen((GXTexCoordID)texCoord, GX_TG_MTX2x4, GX_TG_TEX0, iVar11);
                f32 dVar15 = mBlureSize * (1.0f / 6400.0f);
                mDoMtx_stack_c::transS((dVar15 * cM_scos(sVar10)) * getInvScale(), dVar15 * cM_ssin(sVar10), 0.0f);
                GXLoadTexMtxImm(mDoMtx_stack_c::get(), iVar11, GX_MTX2x4);

                iVar11 += 3;
                sVar10 += 0x2492;
            }
            GXSetNumTevStages(8);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            for (int tevStage = (int)GX_TEVSTAGE1; tevStage < 8; tevStage++) {
                GXSetTevOrder((GXTevStageID)tevStage, (GXTexCoordID)tevStage, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorIn((GXTevStageID)tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp((GXTevStageID)tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn((GXTevStageID)tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
                GXSetTevAlphaOp((GXTevStageID)tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            GXPixModeSync();
            mDoGph_drawFilterQuad(1, 1);
            GXSetTexCopySrc(0, 0, FB_WIDTH / 4, FB_HEIGHT / 4);
            GXSetTexCopyDst(FB_WIDTH / 8, FB_HEIGHT / 8, GX_TF_RGBA8, GX_TRUE);
            GXCopyTex(zBufferTex, GX_FALSE);
            GXTexObj auStack_e0;
            GXInitTexObj(&auStack_e0, zBufferTex, FB_WIDTH / 8, FB_HEIGHT / 8, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&auStack_c0, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&auStack_e0, GX_TEXMAP0);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
            GXPixModeSync();
            GXInvalidateTexAll();
            mDoGph_drawFilterQuad(1, 1);
            GXSetTexCopySrc(0, 0, FB_WIDTH / 4, FB_HEIGHT / 4);
            GXSetTexCopyDst(FB_WIDTH / 4, FB_HEIGHT / 4, GX_TF_RGBA8, GX_FALSE);
            GXCopyTex(zBufferTex, GX_FALSE);
            GXInitTexObj(&auStack_e0, m_buffer, FB_WIDTH / 2, FB_HEIGHT / 2, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&auStack_e0, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&auStack_e0, GX_TEXMAP0);
            GXSetNumTexGens(1);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3c);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_OR);
            mDoGph_drawFilterQuad(2, 2);
            GXLoadTexObj(&auStack_c0, GX_TEXMAP0);
            GXSetTevColor(GX_TEVREG0, mBlendColor);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetBlendMode(GX_BM_BLEND, mMode == 1 ? GX_BL_INVDSTCLR : GX_BL_ONE, GX_BL_SRCALPHA, GX_LO_OR);
            GXPixModeSync();
            GXInvalidateTexAll();
            mDoGph_drawFilterQuad(4, 4);
        }
    }
}

static void retry_captue_frame(view_class* param_0, view_port_class* param_1, int param_2) {
    s16 x_orig = (int)param_1->x_orig & 0xFFFFFFF8;
    s16 y_orig = (int)param_1->y_orig & 0xFFFFFFF8;
    s16 y_orig_pos = y_orig < 0 ? 0 : y_orig;
    s16 width = (int)param_1->width & 0xFFFFFFF8;
    s16 height = (int)param_1->height & 0xFFFFFFF8;
    void* tex = (void*)mDoGph_gInf_c::getFrameBufferTex();
    u16 var_r24;
    u16 var_r23;

    if (!dComIfGp_isPauseFlag()) {
        if (y_orig < 0) {
            height += y_orig;
            y_orig = -y_orig >> 1;
            tex = (char*)tex + GXGetTexBufferSize(FB_WIDTH / 2, y_orig, mDoGph_gInf_c::getFrameBufferTimg()->format, GX_FALSE, 0);
        }

        var_r24 = width >> 1;
        var_r23 = height >> 1;
        GXSetTexCopySrc(x_orig, y_orig_pos, width, height);
        GXSetTexCopyDst(var_r24, var_r23, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_TRUE);
        GXCopyTex(tex, GX_FALSE);
        GXPixModeSync();
        GXInvalidateTexAll();
    }
}

static void motionBlure(view_class* param_0) {
    std::cout << "motionBlure() is stubbed" << std::endl;

    /* if (g_env_light.is_blure) {
        GXLoadTexObj(mDoGph_gInf_c::getFrameBufferTexObj(), GX_TEXMAP0);
        GXColor local_60;
        local_60.a = mDoGph_gInf_c::getBlureRate();
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1e);
        GXSetNumTevStages(1);
        GXSetTevColor(GX_TEVREG0, local_60);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetZCompLoc(1);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
        GXSetCullMode(GX_CULL_NONE);
        GXSetDither(GX_TRUE);
        Mtx44 ortho;
        C_MTXOrtho(ortho, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 10.0f);
        GXLoadPosMtxImm(cMtx_getIdentity(), 0);
        GXLoadTexMtxImm(mDoGph_gInf_c::getBlureMtx(), 0x1e, GX_MTX2x4);
        GXSetProjection(ortho, GX_ORTHOGRAPHIC);
        GXSetCurrentMtx(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGB8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8, 0);
        mDoGph_drawFilterQuad(1, 1);
        GXSetProjection(param_0->projMtx, GX_PERSPECTIVE);
    }

    if (mDoGph_gInf_c::isBlure()) {
        g_env_light.is_blure = 1;
    } else {
        g_env_light.is_blure = 0;
    } */
}

static void setLight() {
    GXLightObj obj;

    GXInitLightPos(&obj, -35000.0f, 0.0f, -30000.0f);
    GXInitLightDir(&obj, 0.0f, 0.0f, 0.0f);
    GXInitLightColor(&obj, g_whiteColor);
    GXInitLightDistAttn(&obj, 0.0f, 0.0f, GX_DA_GENTLE);
    GXInitLightSpot(&obj, 0.0f, GX_SP_FLAT);
    GXLoadLightObjImm(&obj, GX_LIGHT0);
}

static void drawItem3D() {
    Mtx item_mtx;
    dMenu_Collect3D_c::setupItem3D(item_mtx);

    setLight();
    j3dSys.setViewMtx(item_mtx);
    GXSetClipMode(GX_CLIP_DISABLE);
    dComIfGd_drawListItem3d();
    GXSetClipMode(GX_CLIP_ENABLE);
    j3dSys.reinitGX();
}

int mDoGph_Painter() {
    dComIfGp_particle_calcMenu();

    JFWDisplay::getManager()->setFader(mDoGph_gInf_c::getFader());
    mDoGph_gInf_c::setClearColor(mDoGph_gInf_c::getBackColor());
    mDoGph_gInf_c::beginRender();

    GXSetAlphaUpdate(GX_DISABLE);
    mDoGph_gInf_c::setBackColor(g_clearColor);

    j3dSys.drawInit();
    GXSetDither(GX_ENABLE);

    J2DOrthoGraph ortho(0.0f, 0.0f, FB_WIDTH, FB_HEIGHT, -1.0f, 1.0f);
    ortho.setOrtho(mDoGph_gInf_c::getMinXF(), mDoGph_gInf_c::getMinYF(), mDoGph_gInf_c::getWidthF(), mDoGph_gInf_c::getHeightF(), -1.0f, 1.0f);
    ortho.setPort();

    dComIfGp_setCurrentGrafPort(&ortho);
    dComIfGd_drawCopy2D();

    // 2D drawing end

    if (dComIfGp_getWindowNum() != 0) {
        dDlst_window_c* window_p = dComIfGp_getWindow(0);
        int camera_id = window_p->getCameraID();
        camera_class* camera_p = dComIfGp_getCamera(camera_id);

        if (camera_p != NULL) {
            dComIfGd_imageDrawShadow(camera_p->viewMtx);

            // Shadow texture drawing end

            view_port_class* view_port = window_p->getViewPort();

            if (view_port->x_orig != 0.0f || view_port->y_orig != 0.0f) {
                view_port_class new_port;
                new_port.x_orig = 0.0f;
                new_port.y_orig = 0.0f;
                new_port.width = FB_WIDTH;
                new_port.height = FB_HEIGHT;
                new_port.near_z = view_port->near_z;
                new_port.far_z = view_port->far_z;
                new_port.scissor = view_port->scissor;

                view_port = &new_port;
            }

            GXSetViewport(view_port->x_orig, view_port->y_orig, view_port->width, view_port->height, view_port->near_z, view_port->far_z);
            GXSetScissor(view_port->x_orig, view_port->y_orig, view_port->width, view_port->height);

            JPADrawInfo draw_info(camera_p->viewMtx, camera_p->fovy, camera_p->aspect);

            dComIfGp_setCurrentWindow(window_p);
            dComIfGp_setCurrentView(camera_p);
            dComIfGp_setCurrentViewport(view_port);
            GXSetProjection(camera_p->projMtx, GX_PERSPECTIVE);

            // PPCSync();

            j3dSys.setViewMtx(camera_p->viewMtx);
            dKy_setLight();
            dComIfGd_drawOpaListSky();
            dComIfGd_drawXluListSky();

            GXSetClipMode(GX_CLIP_ENABLE);

            // Translucent end

            dComIfGd_drawOpaListBG();
            dComIfGd_drawOpaListDarkBG();
            dComIfGd_drawOpaListMiddle();

            dComIfGp_particle_drawFogPri0_B(&draw_info);

            dComIfGp_particle_drawNormalPri0_B(&draw_info);

            // Terrain opaque end

            dComIfGd_drawShadow(camera_p->viewMtx);

            // Shadow end

            dComIfGd_drawOpaList();

            dComIfGd_drawOpaListDark();

            dComIfGd_drawOpaListPacket();

            // Special-use opaque except J3D end

            dComIfGd_drawXluListBG();
            dComIfGd_drawXluListDarkBG();

            dComIfGp_particle_drawFogPri0_A(&draw_info);
            dComIfGp_particle_drawNormalPri0_A(&draw_info);

            // Terrain translucent end

            dComIfGd_drawXluList();

            dComIfGd_drawXluListDark();

            // Object translucent end

            j3dSys.reinitGX();
            GXSetClipMode(GX_CLIP_ENABLE);

            if (!dComIfGp_isPauseFlag()) {
                motionBlure(camera_p);

                // Motion blur end

                drawDepth2(camera_p, view_port, dComIfGp_getCameraZoomForcus(camera_id));
                GXInvalidateTexAll();
                GXSetClipMode(GX_CLIP_ENABLE);

                // Depth of field end

                /* if (!(g_kankyoHIO.navy.field_0x30d != 0 && dKy_darkworld_check() == TRUE)) {
                    if (g_env_light.is_blure == 0) {
                        dComIfGd_drawOpaListInvisible();
                        dComIfGd_drawXluListInvisible();
                    }
                } */

                // Projection translucent end

                dComIfGp_particle_drawFogPri4(&draw_info);
                dComIfGp_particle_drawProjection(&draw_info);

                // Projection particle end

                dComIfGd_drawListZxlu();

                // 2-draw Z-update translucent end

                GXSetClipMode(GX_CLIP_ENABLE);

                dComIfGd_drawOpaListFilter();

                // Filter draw end

                GXSetClipMode(GX_CLIP_ENABLE);

                dComIfGp_particle_drawFogPri1(&draw_info);
                dComIfGp_particle_draw(&draw_info);
                dComIfGp_particle_drawFogPri2(&draw_info);
                dComIfGp_particle_drawFog(&draw_info);
                dComIfGp_particle_drawFogPri3(&draw_info);
                dComIfGp_particle_drawP1(&draw_info);
                dComIfGp_particle_drawDarkworld(&draw_info);

                // Dark world particle end

                retry_captue_frame(camera_p, view_port, dComIfGp_getCameraZoomForcus(camera_id));

                // Frame buffer capture #2 end

                GXSetClipMode(GX_CLIP_ENABLE);

                /* if (!(g_kankyoHIO.navy.field_0x30d != 0 && dKy_darkworld_check() == TRUE)) {
                    if (g_env_light.is_blure == 1) {
                        dComIfGd_drawOpaListInvisible();
                        dComIfGd_drawXluListInvisible();
                    }
                } */

                dComIfGp_particle_drawScreen(&draw_info);

                // Full projection particle end

                GXSetClipMode(GX_CLIP_ENABLE);

                dComIfGd_drawIndScreen();

                if (strcmp(dComIfGp_getStartStageName(), "F_SP124") == 0) {
                    retry_captue_frame(camera_p, view_port,
                                       dComIfGp_getCameraZoomForcus(camera_id));
                }

                GXSetViewport(0.0f, 0.0f, FB_WIDTH, FB_HEIGHT, 0.0f, 1.0f);

                Mtx m2;
                Mtx44 m;
                C_MTXPerspective(m, AREG_F(8) + 60.0f, mDoGph_gInf_c::getAspect(), 1.0f, 100000.0f);
                GXSetProjection(m, GX_PERSPECTIVE);
                cXyz sp38c(0.0f, 0.0f, AREG_F(7) + -2.0f);
                cXyz sp398(0.0f, 1.0f, 0.0f);

                cMtx_lookAt(m2, &sp38c, &cXyz::Zero, &sp398, 0);
                j3dSys.setViewMtx(m2);
                dComIfGd_drawXluList2DScreen();

                j3dSys.setViewMtx(camera_p->viewMtx);
                GXSetProjection(camera_p->projMtx, GX_PERSPECTIVE);

                // Full projection screen end

                j3dSys.reinitGX();

                /* if ((g_env_light.camera_water_in_status || !strcmp(dComIfGp_getStartStageName(), "D_MN08")))
                {
                    u8 enable = mDoGph_gInf_c::getBloom()->getEnable();
                    GXColor color = *mDoGph_gInf_c::getBloom()->getMonoColor();
                    if (color.a != 0 || enable) {
                        retry_captue_frame(camera_p, view_port, dComIfGp_getCameraZoomForcus(camera_id));
                    }
                } */

                // Frame buffer capture #3 end

                mDoGph_gInf_c::getBloom()->draw();
                j3dSys.setViewMtx(camera_p->viewMtx);
                GXSetProjection(camera_p->projMtx, GX_PERSPECTIVE);

                dComIfGd_drawOpaList3Dlast();

                // Saturation add filter end

                ortho.setOrtho(mDoGph_gInf_c::getMinXF(), mDoGph_gInf_c::getMinYF(), mDoGph_gInf_c::getWidthF(), mDoGph_gInf_c::getHeightF(), 100000.0f, -100000.0f);
                ortho.setPort();

                Mtx m3;
                MTXTrans(m3, FB_WIDTH / 2, FB_HEIGHT / 2, 0.0f);
                JPADrawInfo draw_info2(m3, 0.0f, FB_HEIGHT, 0.0f, FB_WIDTH);
                dComIfGp_particle_draw2Dgame(&draw_info2);

                trimming(camera_p, view_port);

                if (strcmp(dComIfGp_getStartStageName(), "F_SP127") != 0 &&
                    (mDoGph_gInf_c::isFade() & 0x80) == 0)
                {
                    mDoGph_gInf_c::calcFade();
                }
            }
        }
    }

    GXSetClipMode(GX_CLIP_ENABLE);
    dDlst_list_c::calcWipe();
    j3dSys.reinitGX();

    ortho.setOrtho(mDoGph_gInf_c::getMinXF(), mDoGph_gInf_c::getMinYF(), mDoGph_gInf_c::getWidthF(), mDoGph_gInf_c::getHeightF(), 100000.0f, -100000.0f);
    ortho.setPort();

    // 2D drawing
    Mtx m4;
    cMtx_copy(j3dSys.getViewMtx(), m4);

    Mtx m5;
    MTXTrans(m5, FB_WIDTH / 2, FB_HEIGHT / 2, 0.0f);

    JPADrawInfo draw_info3(m5, 0.0f, FB_HEIGHT, 0.0f, FB_WIDTH);

    if (!dComIfGp_isPauseFlag()) {
        dComIfGp_particle_draw2Dback(&draw_info3);
    }

    dComIfGp_particle_draw2DmenuBack(&draw_info3);
    ortho.setPort();

    dComIfGd_draw2DOpa();
    drawItem3D();
    ortho.setPort();

    dComIfGd_draw2DOpaTop();
    dComIfGd_draw2DXlu();

    if (!dComIfGp_isPauseFlag()) {
        dComIfGp_particle_draw2Dfore(&draw_info3);
    }

    if (strcmp(dComIfGp_getStartStageName(), "F_SP127") == 0 || (mDoGph_gInf_c::isFade() & 0x80) != 0)
    {
        mDoGph_gInf_c::calcFade();
    }

    dComIfGp_particle_draw2DmenuFore(&draw_info3);
    j3dSys.setViewMtx(m4);

    mDoGph_gInf_c::endRender();

    return 1;
}

int mDoGph_Create() {
    JKRSolidHeap* heap = mDoExt_createSolidHeapToCurrent(0, NULL, 0);
    mDoGph_gInf_c::create();
    dComIfGd_init();
    u32 var_r30 = mDoExt_adjustSolidHeap(heap);
    mDoExt_restoreCurrentHeap();

    return 1;
}
