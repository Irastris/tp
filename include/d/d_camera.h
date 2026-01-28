#ifndef D_D_CAMERA_H
#define D_D_CAMERA_H

/* #include "d/d_attention.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cam_param.h" */
#include "d/d_drawlist.h"
// #include "d/d_spline_path.h"
#include "d/d_stage.h"
/* #include "d/actor/d_a_player.h"
#include "f_op/f_op_actor.h" */
#include "m_Do/m_Do_graphic.h"

dAttention_c* dComIfGp_getAttention();

struct dCamMapToolData {
    dCamMapToolData() { Clr(); }

    int Set(s32, s32, fopAc_ac_c*, u16, u8);

    dCamMapToolData& operator=(dCamMapToolData const& other) {
        __memcpy(&mCamData, &other.mCamData, sizeof(stage_camera2_data_class));
        __memcpy(&mArrowData, &other.mArrowData, sizeof(stage_arrow_data_class));
        mArrowIndex = other.mArrowIndex;
        mCameraIndex = other.mCameraIndex;
        mpActor = other.mpActor;
        mPriority = other.mPriority;
        mFlags = other.mFlags;
        mPathId = other.mPathId;
        return *this;
    }

    void Clr() {
        mCameraIndex = mArrowIndex = 0xFF;
        mFlags = 0;
        mpActor = NULL;
        mPathId = 0xFF;
        mPriority = 0xFF;
    }

    stage_camera2_data_class mCamData;
    stage_arrow_data_class mArrowData;
    int mArrowIndex;
    s32 mCameraIndex;
    fopAc_ac_c* mpActor;
    u16 mPriority;
    u8 mFlags;
    u8 mPathId;
};

struct dCamForcusLine {
    void Init();
    void Draw();
    bool Off();

    dDlst_effectLine_c mEffectLine;
    cXyz field_0x38;
    GXColor field_0x44;
    u8 field_0x48;
    bool field_0x49;
    int field_0x4c;
    int field_0x50;
    int field_0x54;
    u16 field_0x58;
    u16 field_0x5a;
    u16 field_0x5c;
    u16 field_0x5e;
    f32 field_0x60;
    f32 field_0x64;
    f32 field_0x68;
    f32 field_0x6c;
};

struct UnkManualCameraParam {
    f32 r;
    f32 v;
    f32 u;
    f32 fov;
};

struct dCamera_event_param {
    char name[16];
    int field_0x10;
    int value;
};

struct dCamera_type_data {
    char name[24];
    s16 field_0x18[2][11];
};

struct camSphChkdata {
    camSphChkdata(cXyz* i_center, cXyz* param_1, f32 i_radius) {
        field_0x0 = i_center;
        field_0x8 = param_1;
        field_0xc = *i_center;
        field_0x4 = i_radius;
        field_0x1c = false;
        field_0x18 = i_radius;
    }

    void Base(cXyz* param_0) {
        field_0x0 = param_0;
        field_0xc = *param_0;
    }

    cXyz* field_0x0;
    f32 field_0x4;
    cXyz* field_0x8;
    cXyz field_0xc;
    f32 field_0x18;
    bool field_0x1c;
};

class camera_class;

class dCamera_c;
typedef bool (dCamera_c::*engine_fn)(s32);

class dCamera_c {
public:
    class dCamInfo_c {
    public:
        dCamInfo_c() {}
        ~dCamInfo_c() {}
        cXyz mCenter;
        cXyz mEye;
        f32 mFovy;
        cSAngle mBank;
        s16 field_0x1e;
    };

    struct dCamera_pad_info {
        struct _stick {
            f32 mLastPosX;
            f32 mLastPosY;
            f32 mLastValue;
            f32 mPosXDelta;
            f32 mPosYDelta;
            f32 mValueDelta;
            cSAngle mAngle;
        };

        _stick mMainStick;
        _stick mCStick;
    };

    struct dCamera_event_data {
        u8 field_0x0;
        int mStaffIdx;
        int field_0x8;
        int field_0xc;
        u8 field_0x10;
        int field_0x14;
        int field_0x18;
        int field_0x1c;
        int field_0x20;
        int field_0x24;
        u8 field_0x28[0x2C - 0x28];
        dCamera_event_param mEventParams[8];
        dStage_MapEvent_dt_c* field_0xec;
        d2DBSplinePath field_0xf0;
    };

    struct dCamera_monitoring_things {
        cXyz field_0x0;
        f32 field_0xc;
        f32 field_0x10;
        struct {
            cXyz field_0x0;
        } field_0x14;
    };

    struct dCamera_FakeAngle_system {
        u8 field_0x0;
        cSAngle field_0x2;
        cSAngle field_0x4;
    };

    struct BG {
        struct {
            bool field_0x0;
            dBgS_CamGndChk field_0x4;
            f32 field_0x58;
        } field_0x0, field_0x5c;
        u8 field_0xb8[0xC0 - 0xB8];
        struct {
            u8 field_0x0;
            u8 field_0x1;
            cXyz field_0x4;
            cXyz field_0x10;
            cSAngle field_0x1c;
            cSAngle field_0x1e;
            fopAc_ac_c* field_0x20;
            cSGlobe field_0x24;
            cSGlobe field_0x2c;
            int field_0x34;
            f32 field_0x38;
            int field_0x3c;
            int field_0x40;
            u8 field_0x44;
        } field_0xc0;
        struct {
            int field_0x0;
            f32 field_0x4;
            cXyz field_0x8;
        } field_0x108;
    };

    struct Shake {
        u8 field_0x0[4];
        u8 field_0x4[4];
        u8 field_0x8[0xC - 0x8];
        s32 m_length;
        int field_0x10;
        u8 field_0x14[4];
        cXyz m_pos;
        cXyz field_0x24;
        cXyz mEyeShake;
        f32 field_0x3c;
        cSAngle field_0x40;
    };

    struct ChaseData {
        int field_0x0;
        int field_0x4;
        f32 field_0x8;
        f32 field_0xc;
        int field_0x10;
        int field_0x14;
        s16 field_0x18;
        s16 field_0x1a;
        s16 field_0x1c;
        f32 field_0x20;
        f32 field_0x24;
        f32 field_0x28;
        f32 field_0x2c;
        f32 field_0x30;
        f32 field_0x34;
        f32 field_0x38;
        f32 field_0x3c;
        f32 field_0x40;
        int field_0x44;
        f32 field_0x48;
        f32 field_0x4c;
        f32 field_0x50;
        f32 field_0x54;
        cXyz field_0x58;
        cXyz field_0x64;
        bool field_0x70;
        bool field_0x71;
        bool field_0x72;
        bool field_0x73;
        f32 field_0x74;
        f32 field_0x78;
        f32 field_0x7c;
        f32 field_0x80;
        f32 field_0x84;
        f32 field_0x88;
        int field_0x8c;
        bool field_0x90;
        bool field_0x91;
        bool field_0x92;
        bool field_0x93;
        bool field_0x94;
        bool field_0x95;
        cSAngle field_0x96;
        cSAngle field_0x98;
        cSAngle field_0x9a;
        int field_0x9c;
        int field_0xa0;
        f32 field_0xa4;
        int field_0xa8;
        f32 field_0xac;
    };

    struct LockOnData {
        int field_0x0;
        u8 field_0x4[8];
        int field_0xc;
        f32 field_0x10;
        int field_0x14;
        bool field_0x18;
        cXyz field_0x1c;
        bool field_0x28;
        bool field_0x29;
        bool field_0x2a;
        int field_0x2c;
        int field_0x30;
        cSGlobe field_0x34;
        fpc_ProcID field_0x3c;
        bool field_0x40;
        cSAngle field_0x42;
        int field_0x44;
        f32 field_0x48;
        f32 field_0x4c;
        cSAngle field_0x50;
        f32 field_0x54;
        f32 field_0x58;
        f32 field_0x5c;
        f32 field_0x60;
    };

    struct TalkData {
        int field_0x0;
        cXyz field_0x4;
        cXyz field_0x10;
        cXyz field_0x1c;
        cSGlobe field_0x28;
        cSGlobe field_0x30;
        int field_0x38;
        int field_0x3c;
        int field_0x40;
        int field_0x44;
        int field_0x48;
        f32 field_0x4c;
        f32 field_0x50;
        f32 field_0x54;
        f32 field_0x58;
        f32 field_0x5c;
        f32 field_0x60;
        f32 field_0x64;
        f32 field_0x68;
        f32 field_0x6c;
        fopAc_ac_c* field_0x70;
        fopAc_ac_c* field_0x74;
        fopAc_ac_c* field_0x78;
        f32 field_0x7c;
        f32 field_0x80;
        s16 field_0x84;
        s16 field_0x86;
        bool field_0x88;
        bool field_0x89;
        u32 field_0x8c;
        cXyz field_0x90;
        cXyz field_0x9c;
        cSGlobe field_0xa8;
        f32 field_0xb0;
        cXyz field_0xb4;
        cXyz field_0xc0;
        cXyz field_0xcc;
        cXyz field_0xd8;
    };

    struct SubjectData {
        int field_0x0;
        cXyz field_0x4;
        int field_0x10;
        int field_0x14;
        int field_0x18;
        bool field_0x1c;
        bool field_0x1d;
        f32 field_0x20;
        f32 mZoomRatio;
        cSAngle field_0x28;
        cSAngle field_0x2a;
        cSAngle field_0x2c;
        cSAngle field_0x2e;
        cXyz field_0x30;
        cXyz field_0x3c;
        cSGlobe field_0x48;
    };

    struct MagneData {
        int field_0x0;
        cXyz field_0x4;
        cXyz field_0x10;
        cSGlobe field_0x1c;
    };

    struct ColosseumData {
        u8 field_0x0[8];
        cXyz field_0x8;
        f32 field_0x14;
        int field_0x18;
    };

    struct TowerData {
        int field_0x0;
        int field_0x4;
        f32 field_0x8;
        f32 field_0xc;
        int field_0x10;
        int field_0x14;
        f32 field_0x18;
        f32 field_0x1c;
        f32 field_0x20;
        f32 field_0x24;
        cSAngle field_0x28;
        f32 field_0x2c;
        f32 field_0x30;
        f32 field_0x34;
        int field_0x38;
        f32 field_0x3c;
        f32 field_0x40;
        f32 field_0x44;
        cXyz field_0x48;
        cXyz field_0x54;
        cSAngle field_0x60;
        int field_0x64;
        bool field_0x68;
        bool field_0x69;
        bool field_0x6a;
        bool field_0x6b;
        bool field_0x6c;
        f32 field_0x70;
        f32 field_0x74;
        f32 field_0x78;
        f32 field_0x7c;
        f32 field_0x80;
        f32 field_0x84;
    };

    struct HookshotData {
        int field_0x0;
        u8 field_0x4[4];
        cXyz field_0x8;
        cXyz field_0x14;
        bool field_0x20;
    };

    struct EventData {
        bool field_0x0;
        bool field_0x1;
        int field_0x4;
        int field_0x8;
        u8 field_0xc[0x10 - 0xc];
        cXyz field_0x10;
        f32 mFovy;
        f32 mBank;
        fopAc_ac_c* mRelActor;
        char mRelUseMask;
        char field_0x29;
        int mTimer;
        bool field_0x30;
        cXyz mBasePos;
        char field_0x40;
        char field_0x41;
        u8 field_0x42[0x48 - 0x42];
        char field_0x48;
        u8 field_0x49[0x4c - 0x49];
        int field_0x4c;
        int field_0x50;
        u8 field_0x54[0x5c - 0x54];
        f32* field_0x5c;
        u8 field_0x60[0x6c - 0x60];
        int field_0x6c;
    };

    struct FixedFrameEvData {
        bool field_0x0;
        cXyz field_0x4;
        cXyz field_0x10;
        f32 field_0x1c;
        f32 field_0x20;
        fopAc_ac_c* mpRelActor;
        char mRelUseMask[4];
        int mTimer;
        bool field_0x30;
        cXyz mBasePos;
    };

    struct StokerData {
        bool field_0x0;
        bool field_0x1;
        u8 field_0x2[2];
        cXyz field_0x4;
        cXyz field_0x10;
        f32 field_0x1c;
        f32 field_0x20;
        f32 field_0x24;
        f32 field_0x28;
        fopAc_ac_c* field_0x2c;
        fopAc_ac_c* field_0x30;
        fpc_ProcID field_0x34;
        fpc_ProcID field_0x38;
        u8 field_0x3c[0x40 - 0x3c];
        int field_0x40;
    };

    struct RollingData {
        bool field_0x0;
        bool field_0x1;
        cXyz field_0x4;
        cXyz field_0x10;
        cXyz mEye;
        cXyz mCenter;
        f32 mFovy;
        f32 mBank;
        fopAc_ac_c* mpRelActor;
        char mRelActor[4];
        int mTimer;
        int mTransType;
        f32 mRoll;
        f32 mRadiusAdd;
        f32 mLatitude;
        f32 mCtrCus;
    };

    struct FixedPosData {
        bool field_0x0;
        bool field_0x1;
        cXyz field_0x4;
        cXyz field_0x10;
        cXyz field_0x1c;
        f32 field_0x28;
        f32 field_0x2c;
        f32 field_0x30;
        f32 field_0x34;
        f32 field_0x38;
        fopAc_ac_c* field_0x3c;
        fopAc_ac_c* field_0x40;
        fpc_ProcID field_0x44;
        char field_0x48;
        int field_0x4c;
    };

    struct TransData {
        cXyz mStartEye;
        cXyz mStartCenter;
        f32 mStartFovy;
        f32 field_0x1c;
        cXyz mEye;
        cXyz mCenter;
        f32 mFovy;
        f32 field_0x3c;
        fopAc_ac_c* mRelActor;
        fpc_ProcID mRelActorID;
        char mRelUseMask;
        char field_0x49;
        char field_0x4a;
        char field_0x4b;
        u8 field_0x4c[4];
        int mTimer;
        int mTransType;
        f32 mCushion;
        f32* mBSpPoints;
        cSGlobe field_0x60;
        bool field_0x68;
        int mBSpCurve;
    };

    struct ActorData {
        cXyz mCtrGap;
        cXyz field_0xc;
        f32 mCushion;
        int mNearTimer;
        f32 mNearDist;
        int mFarTimer;
        f32 mFarDist;
        f32 mZoomDist;
        f32 mZoomVAngle;
        fopAc_ac_c* mTargetActor;
        fpc_ProcID mTargetActorID;
        cSGlobe field_0x3c;
        int field_0x44;
        u8 field_0x48[4];
        cSGlobe field_0x4c;
        int field_0x54;
        int mBlure;
        f32 mFrontAngle;
        f32 mFovy;
        u8 field_0x64[4];
        int field_0x68;
    };

    struct RestorePosData {
        cXyz field_0x0;
        cXyz field_0xc;
        f32 field_0x18;
        int field_0x1c;
        f32 field_0x20;
        int field_0x24;
        f32 field_0x28;
        u8 field_0x2c[0x034 - 0x02C];
        fopAc_ac_c* field_0x34;
        cSGlobe field_0x38;
        int field_0x40;
        int field_0x44;
        dCamInfo_c field_0x48;
        int field_0x68;
    };

    struct GameOverData {
        int field_0x0;
        int field_0x4;
        int field_0x8;
        int mType;
        cXyz field_0x10;
        cSGlobe field_0x1c;
        u8 field_0x24[0x3c - 0x24];
        bool field_0x3c;
    };

    struct TactData {
        int field_0x0;
        int field_0x4;
        int field_0x8;
        int field_0xc;
        u8 field_0x10[4];
        int field_0x14;
        u8 field_0x18[4];
        cXyz* field_0x1c;
        cXyz* field_0x20;
        int field_0x24;
        u8 field_0x28[4];
        f32 field_0x2c;
        cXyz field_0x30;
        cXyz field_0x3c;
    };

    struct LoadData {
        int mTimer;
        int mSlot;
        int mType;
        cSGlobe field_0xc;
        cSGlobe field_0x14;
        cXyz field_0x1c;
        cXyz field_0x28;
        cXyz field_0x34;
        cSAngle field_0x40;
        cSAngle field_0x42;
        f32 field_0x44;
        f32 field_0x48;
    };

    struct ItemData {
        int field_0x0;
        int field_0x4;
        int mType;
        cXyz field_0xc;
        f32 field_0x18;
        int field_0x1c;
        int field_0x20;
        cSGlobe field_0x24;
        cXyz field_0x2c;
        cXyz field_0x38;
        cXyz field_0x44;
        cXyz field_0x50;
        f32 field_0x5c;
    };

    struct GetItemData {
        u8 field_0x0[4];
        int mTimer;
        int field_0x8;
        fopAc_ac_c* mRelActor;
        fpc_ProcID mRelActorID;
        f32* mCurvePoints;
        int field_0x18;
        cXyz mStartCenter;
        cXyz mStartEye;
        u8 field_0x34[8];
        cSGlobe field_0x3c;
        cXyz field_0x44;
        cXyz field_0x50;
        u8 field_0x5C[8];
        cSGlobe field_0x64;
    };

    struct PossessedData {
        int field_0x0;
        int mType;
        int mTimer;
        int field_0xc;
        f32 mRadius;
        cSAngle mLatitude;
        cSAngle mLongitude;
        f32 mFovy;
        f32 mCushion;
        int mBlure;
        fopAc_ac_c* mTargetActor;
        cSGlobe field_0x28;
    };

    struct FixedFramesData {
        bool field_0x0;
        cXyz field_0x4;
        cXyz field_0x10;
        cXyz* field_0x1c[2];
        f32* field_0x24;
        f32 field_0x28;
        fopAc_ac_c* mRelActor;
        char mRelUseMask;
        char field_0x31;
        int mTimer;
        int field_0x38;
        int mChoice;
    };

    struct BSplineData {
        cXyz* mCenters;
        cXyz* mEyes;
        f32* mFovys;
        int mTimer;
        int field_0x10;
        fopAc_ac_c* mRelActor;
        u8 field_0x18[4];
        bool field_0x1c;
    };

    struct TwoActor0Data {
        fopAc_ac_c* mActor1;
        fopAc_ac_c* mActor2;
        u8 field_0x8[4];
        fpc_ProcID mActor1ID;
        fpc_ProcID mActor2ID;
        f32 mCtrCus;
        f32 mEyeCus;
        f32 mRadiusMin;
        f32 mRadiusMax;
        f32 mLatitudeMin;
        f32 mLatitudeMax;
        f32 mLongitudeMin;
        f32 mLongitudeMax;
        int mLongitudeType;
        f32 mFovy;
        f32 mCtrRatio;
        cXyz mCtrGap;
        f32 field_0x4c;
        f32 field_0x50;
        cSAngle field_0x54;
        cSAngle field_0x56;
        cSAngle field_0x58;
        cSAngle field_0x5a;
    };

    struct DigHoleData {
        int field_0x0;
        int mType;
        int field_0x8;
        f32 field_0xc;
        u8 field_0x10;
        u8 field_0x11[3];
        cXyz field_0x14;
        cXyz field_0x20;
    };

    struct HintTalkData {
        fopAc_ac_c* mTeacher;
        fopAc_ac_c* mStudent;
        cXyz field_0x8;
        cXyz field_0x14;
        cSGlobe mDirection;
        cSGlobe field_0x28;
        f32 mRadius;
        f32 mFovy;
        f32 mCtrGapY;
        int mTimer;
        cXyz field_0x40;
    };

    struct BspTransData {
        int mTimer;
        f32* mBase;
        f32* mSet1;
        d2DBSplinePath mSplinePath1;
        f32* mSet2;
        d2DBSplinePath mSplinePath2;
        cXyz field_0x78;
        cXyz field_0x84;
        f32 field_0x90;
        cXyz field_0x94;
        cXyz field_0xa0;
        f32 field_0xac;
        fopAc_ac_c* mRelActor;
        fpc_ProcID mRelActorID;
        char mRelUseMask;
        char field_0xb9;
        f32 mCushion;
        u32 field_0xc0[6];
    };

    struct RailData {
        int field_0x00;
        fopAc_ac_c* field_0x04;
        fopAc_ac_c* field_0x08;
        u8 field_0x0c;
        u8 field_0x0d;
        u8 field_0xe[0x10 - 0x0e];
        f32 field_0x10;
        cXyz field_0x14;
        cXyz field_0x20;
    };

    struct ParaRailData {
        int field_0x00;
        fopAc_ac_c* field_0x04;
        fopAc_ac_c* field_0x08;
        u8 field_0x0c;
        u8 field_0x0d;
        cXyz field_0x10;
        f32 field_0x1c;
    };

    struct OneSideData {
        int field_0x00;
        u8 field_0x04[0x1c - 0x04];
        cXyz field_0x1c;
        u8 field_0x28;
        int field_0x2c;
        s16 field_0x30;
        cSAngle field_0x32;
        int field_0x34;
    };

    struct ObserveData {
        int field_0x00;
        cXyz field_0x04;
        cSGlobe field_0x10;
        u8 field_0x24[0x28 - 0x18];
        cXyz field_0x28;
    };

    struct FixedFrameData {
        int field_0x00;
        cXyz field_0x04;
        cSGlobe field_0x10;
        int field_0x18;
        f32 field_0x1c;
        f32 field_0x20;
        f32 field_0x24;
        int mArrowIndex;
        cXyz field_0x2c;
        cXyz field_0x38;
    };

    struct FixedPositionData {
        int field_0x00;
        s32 field_0x04;
        f32 field_0x08;
        f32 field_0x0c;
        cXyz field_0x10;
        cXyz field_0x1c;
        u8 field_0x28;
        int field_0x2c;
        int field_0x30;
    };

    struct RideData {
        int field_0x00;
        int prove;
        int field_0x08;
        u32 field_0x0c;
        int field_0x10;
        int field_0x14;
        int field_0x18;
        u8 field_0x1c;
        u8 field_0x1d;
        int field_0x20;
        cXyz field_0x24;
        cXyz field_0x30;
        cXyz field_0x3c;
        cSAngle field_0x48;
        f32 field_0x4c;
        f32 field_0x50;
        f32 field_0x54;
        f32 field_0x58;
        cXyz field_0x5c;
        cXyz field_0x68;
        f32 field_0x74;
        f32 field_0x78;
        f32 field_0x7c;
        f32 field_0x80;
        cXyz field_0x84;
        u8 field_0x90;
        u8 field_0x91;
        u8 field_0x92;
        bool field_0x93;
        fopAc_ac_c* field_0x94;
        daHorse_c* field_0x98;
        fopAc_ac_c* field_0x9c;
        fopAc_ac_c* field_0xa0;
    };

    struct ManualData {
        int field_0x00;
        cXyz field_0x04;
        cXyz field_0x10;
        f32 field_0x1c;
        f32 field_0x20;
        int field_0x24;
        u8 field_0x28;
        f32 field_0x2c;
        cSGlobe field_0x30;
        f32 field_0x38;
        f32 field_0x3c;
        int field_0x40;
        cSAngle field_0x44;
        f32 field_0x48;
    };

    int StartEventCamera(int, int, ...);
    int EndEventCamera(int);
    int searchEventArgData(char*);
    bool getEvIntData(int*, char*, int);
    bool getEvIntData(int*, char*);
    bool getEvFloatData(f32*, char*);
    bool getEvFloatData(f32*, char*, f32);
    int getEvFloatListData(f32**, char*);
    int getEvXyzListData(cXyz**, char*);
    char* getEvStringPntData(char*, char*);
    char* getEvStringPntData(char*);
    bool getEvXyzData(cXyz*, char*, cXyz);
    bool getEvStringData(char*, char*, char*);
    fopAc_ac_c* getEvActor(char*);
    fopAc_ac_c* getEvActor(char*, char*);
    bool pauseEvCamera();
    bool fixedFrameEvCamera();
    bool stokerEvCamera();
    bool rollingEvCamera();
    bool fixedPositionEvCamera();
    bool uniformTransEvCamera();
    bool uniformBrakeEvCamera();
    bool uniformAcceleEvCamera();
    bool transEvCamera(int);
    bool watchActorEvCamera();
    bool restorePosEvCamera();
    bool talktoEvCamera();
    bool maptoolIdEvCamera();
    bool styleEvCamera();
    bool gameOverEvCamera();
    bool tactEvCamera();
    bool turnToActorEvCamera();
    bool stbWaitEvCamera();
    bool saveEvCamera();
    bool loadEvCamera();
    bool useItem0EvCamera();
    bool useItem1EvCamera();
    bool getItemEvCamera();
    bool possessedEvCamera();
    bool fixedFramesEvCamera();
    bool bSplineEvCamera();
    bool twoActor0EvCamera();
    bool peepHoleEvCamera();
    bool digHoleEvCamera();
    bool hintTalkEvCamera();
    bool bspTransEvCamera();
    bool portalWarpEvCamera();
    cXyz attentionPos(fopAc_ac_c* i_this) { return i_this->attention_info.position; }
    cSAngle directionOf(fopAc_ac_c* i_this) { return i_this->shape_angle.y; }
    cXyz positionOf(fopAc_ac_c* i_this) { return i_this->current.pos; }
    cXyz eyePos(fopAc_ac_c* i_this) { return i_this->eyePos; }
    dCamera_c(camera_class*);
    ~dCamera_c();
    void initialize(camera_class*, fopAc_ac_c*, u32, u32);
    void Start();
    void QuickStart();
    void Stop();
    void Stay();
    bool ChangeModeOK(s32);
    void initPad();
    void updatePad();
    void initMonitor();
    void updateMonitor();
    bool checkForceLockTarget();
    void infoReport();
    bool Run();
    bool NotRun();
    s16 V();
    s16 U();
    bool SetTrimSize(s32);
    bool SetTrimTypeForce(s32);
    void CalcTrimSize();
    int Draw();
    void setStageMapToolData();
    void setMapToolData();
    void SetTagData(fopAc_ac_c*, s32, u16, u8);
    inline void setRoomMapToolData(dCamMapToolData*, s32, s32);
    s32 nextMode(s32);
    bool onModeChange(s32, s32);
    int ModeFix(s32);
    s32 nextType(s32);
    bool onTypeChange(s32, s32);
    bool onStyleChange(s32, s32);
    int onRoomChange(s32);
    fopAc_ac_c* getParamTargetActor(s32);
    int GetCameraTypeFromMapToolID(s32, s32);
    int GetCameraTypeFromCameraName(char const*);
    int GetCameraTypeFromToolData(stage_camera2_data_class*);
    void pushInfo(dCamera_c::dCamInfo_c*, s16);
    void popInfo(dCamera_c::dCamInfo_c*);
    f32 heightOf(fopAc_ac_c*);
    cXyz relationalPos(fopAc_ac_c*, fopAc_ac_c*, cXyz*, f32);
    cXyz relationalPos(fopAc_ac_c*, cXyz*);
    void setUSOAngle();
    cSAngle getUSOAngle(cSAngle);
    bool pointInSight(cXyz*);
    f32 radiusActorInSight(fopAc_ac_c*, fopAc_ac_c*, fopAc_ac_c*);
    f32 radiusActorInSight(fopAc_ac_c*, fopAc_ac_c*, cXyz*, cXyz*, f32, s16, f32);
    f32 radiusActorInSight(fopAc_ac_c* param_0, fopAc_ac_c* param_1) {
        return radiusActorInSight(param_0, param_1, &mViewCache.mCenter, &mViewCache.mEye, mFovy,
                                  mBank, 0.05f);
    }
    f32 groundHeight(cXyz*);
    bool lineBGCheck(cXyz*, cXyz*, dBgS_LinChk*, u32);
    bool lineBGCheck(cXyz*, cXyz*, u32);
    bool lineBGCheck(cXyz*, cXyz*, cXyz*, u32);
    u32 lineCollisionCheckBush(cXyz*, cXyz*);
    cXyz compWallMargin(cXyz*, cXyz*, f32);
    int defaultTriming();
    void setView(f32, f32, f32, f32);
    cSAngle forwardCheckAngle();
    bool bumpCheck(u32);
    bool lineBGCheckBoth(cXyz*, cXyz*, dBgS_LinChk*, u32);
    BOOL jutOutCheck(cXyz*, f32);
    void tooNearEscape(cXyz*);
    f32 getWaterSurfaceHeight(cXyz*);
    void checkGroundInfo();
    bool chaseCamera(s32);
    bool lockonCamera(s32);
    fopAc_ac_c* getMsgCmdSpeaker();
    s32 getMsgCmdCut(s32);
    bool talktoCamera(s32);
    bool CalcSubjectAngle(s16*, s16*);
    bool SaveZoomRatio();
    bool subjectCamera(s32);
    bool magneCamera(s32);
    bool colosseumCamera(s32);
    bool test1Camera(s32);
    bool test2Camera(s32);
    bool towerCamera(s32);
    bool hookshotCamera(s32);
    bool railCamera(s32);
    bool paraRailCamera(s32);
    bool rideCamera(s32);
    bool manualCamera(s32);
    bool observeCamera(s32);
    bool fixedFrameCamera(s32);
    bool fixedPositionCamera(s32);
    bool oneSideCamera(s32);
    bool eventCamera(s32);
    bool currentEvCamera();
    bool letCamera(s32);
    void setEventRecoveryTrans(s16);
    s16 runEventRecoveryTrans();
    void EventRecoverNotime();
    int Set(cXyz, cXyz);
    int Set(cXyz, cXyz, f32, s16);
    int Set(cXyz, cXyz, s16, f32);
    int Reset(cXyz, cXyz);
    int Reset();
    int Reset(cXyz, cXyz, f32, s16);
    f32 shakeCamera();
    int StartShake(s32, u8*, s32, cXyz);
    int StopShake();
    void StartBlure(int, fopAc_ac_c*, f32, f32);
    void ResetBlure();
    void SetBlureAlpha(f32);
    void SetBlureScale(f32, f32, f32);
    void SetBlurePosition(f32, f32, f32);
    void SetBlureActor(fopAc_ac_c*);
    int blureCamera();
    void onHorseDush();
    fopAc_ac_c* GetForceLockOnActor();
    int ForceLockOn(fopAc_ac_c*);
    int ForceLockOff(fpc_ProcID);
    int ForceLockOff(fopAc_ac_c*);
    cXyz Up();
    cXyz Eye();
    cXyz Center();

    f32 footHeightOf(fopAc_ac_c* i_actor) { return i_actor->current.pos.y; }
    cSAngle Bank() { return mBank + mShake.field_0x40; }
    cXyz talkBasePos(fopAc_ac_c* i_actor) { return i_actor->current.pos; }
    cXyz talkEyePos(fopAc_ac_c* i_actor) { return i_actor->eyePos; }

    int CameraID() { return mCameraID; }

    bool Active() { return mCurState == 0; }
    f32 TrimHeight() { return mTrimHeight; }
    int Type() { return mCurType; }
    int Mode() { return mCurMode; }
    f32 Fovy() { return mFovy + mShake.field_0x3c; }
    bool isModeOK() { return mStyleSettle.mFinished; }
    bool push_any_key() { return mCameraInputActive; }

    bool chkFlag(u32 i_flag) { return (mEventFlags & i_flag) != 0; }
    u32 setFlag(u32 i_flag) { return mEventFlags |= i_flag; }
    u32 clrFlag(u32 i_flag) { return mEventFlags &= ~i_flag; }

    bool CheckFlag(u32 i_flag) { return (mEventFlags & i_flag) != 0 ? true : false; }

    void ResetView() { setView(0.0f, 0.0f, FB_WIDTH, FB_HEIGHT); }

    void clearInfo(dCamInfo_c* i_info, s16 param_1) {
        i_info->field_0x1e = param_1;
    }

    int EventFlag(int i_flag) {
        return mEventData.field_0x24 = i_flag;
    }

    void Att() {
        dAttention_c* attn = dComIfGp_getAttention();
        mpLockonTarget = attn->LockonTruth() ? attn->LockonTarget(0) : NULL;
        attn->LockSoundOn();
    }

    void SetWindow(f32 param_0, f32 param_1) {
        mWindowWidth = param_0;
        mWindowHeight = param_1;
        mWindowAspect = param_0 / param_1;
    }

    f32 R() {
        if (chkFlag(0x10)) {
            return mUpOverride.field_0x24.R();
        } else {
            return mDirection.R();
        }
    }

    cXyz iCenter() { return mViewCache.mCenter; }
    cXyz iEye() { return mViewCache.mEye; }
    s16 iU() { return mViewCache.mDirection.U().Inv(); }
    s16 iV() { return mViewCache.mDirection.V(); }
    f32 iR() { return mViewCache.mDirection.R(); }

    s16 U2() {
        if (chkFlag(0x10)) {
            return mViewCache.mDirection.U();
        } else {
            return mControlledYaw;
        }
    }

    void U2(s16 i_val) { mControlledYaw = i_val; }

    void CorrectCenter() { setFlag(0x40000000); }

    int Gear() { return mGear; }

    bool HideBGPartsOK() {
        return chkFlag(0x4);
    }

    f32 Near4Debug() {
        return mCamSetup.Near();
    }
    f32 Far4Debug() {
        return mCamSetup.Far();
    }

    static engine_fn engine_tbl[];

    camera_class* field_0x0;

    struct {
        int mRoomNo;
        cXyz field_0x04;
        cXyz field_0x10;
    }
    mRoomCtx;
    u8 field_0x20;
    u8 field_0x21;
    u8 field_0x22[2];
    int mCurState;
    cSGlobe mDirection;
    cXyz mCenter;
    cXyz mEye;
    cXyz mUp;
    cSAngle mBank;
    f32 mFovy;
    class {
    public:
        cSGlobe mDirection;
        cXyz mCenter;
        cXyz mEye;
        cSAngle mBank;
        f32 mFovy;
    }
    mViewCache;
    f32 field_0x84;
    u32 mBumpCheckFlags;
    cSAngle mControlledYaw;
    cXyz mLastHitPos;
    cXyz mCornerNormalSum;
    u32 mFrameCounter;
    u32 mTicks;
    dCamInfo_c mSavedView;
    dCamInfo_c mSavedViewStack[2];
    class {
    public:
        int field_0x0;
        s16 field_0x4;
        dCamInfo_c field_0x8;
        cXyz field_0x28;
    }
    mRecovery;
    class {
    public:
        cXyz field_0x0;
        csXyz field_0xc;
    }
    field_0x144;
    class {
    public:
        bool mFinished;
        cSAngle field_0x2;
        cSAngle field_0x4;
    }
    mStyleSettle;
    u32 field_0x160;
    int field_0x164;
    u8 field_0x168;
    int field_0x16c;
    u32 field_0x170;
    u32 mCurCamStyleTimer;
    u32 mCameraID;
    u32 mPadID;
    fopAc_ac_c* mpPlayerActor;
    fopAc_ac_c* mpLockonTarget;
    fopAc_ac_c* mpAuxTargetActor1;
    fopAc_ac_c* mpAuxTargetActor2;
    int mIsWolf;
    bool mMidnaRidingAndVisible;
    fpc_ProcID mLockOnActorID;
    fopAc_ac_c* mpLockOnActor;
    int mForceLockTimer;
    int mCurMode;
    int mNextMode;
    int mForcedMode;
    cSAngle mForwardTiltOffset;
    f32 mSightFitRadius;
    u8 field_0x1b8[4];
    dCamera_pad_info mPadInfo;
    int mCStickYState;
    int mCStickYHoldCount;
    int mCStickUpLatch;
    f32 mTriggerLeftLast;
    f32 mTriggerLeftDelta;
    bool mHoldLockL;
    bool mTrigLockL;
    bool mLockLActive;
    bool mLockLJustActivated;
    f32 mTriggerRightLast;
    f32 mTriggerRightDelta;
    bool mHoldLockR;
    bool mTrigLockR;
    bool mLockRActive;
    bool mLockRJustActivated;
    bool mHoldX;
    bool mTrigX;
    bool mHoldY;
    bool mTrigY;
    bool mHoldZ;
    bool mTrigZ;
    u8 field_0x21e;
    u8 field_0x21f;
    bool mHoldB;
    bool mTrigB;
    u8 field_0x222;
    u8 field_0x223;
    bool mCameraInputActive;
    dCamForcusLine mFocusLine;
    dCamera_FakeAngle_system mFakeAngleSys;
    dCamera_monitoring_things mMonitor;
    f32 field_0x2c0;
    int mIdleFrameCount;
    f32 field_0x2c8;
    BG mBG;
    u8 mWork[0x100];
    dCamera_event_data mEventData;
    u32 mEventFlags;
    u8 mFastShotState;
    u8 field_0x611;
    u8 field_0x612[2];
    class {
    public:
        u8 field_0x0[8];
        cSGlobe field_0x8;
        u8 field_0x10[4];
    }
    field_0x614[4];
    u8 field_0x664[4];
    int field_0x668;
    int field_0x66c;
    int field_0x670;
    int field_0x674;
    u8 field_0x678;
    int mCamStyle;
    int mEngineHoldState;
    dCamera_type_data* mCamTypeData;
    int mCamTypeNum;
    int mCurType;
    int mNextType;
    int mMapToolType;
    int field_0x698;
    int field_0x69c;
    u8 field_0x6a0[0x6b8 - 0x6a0];
    Shake mShake;
    int field_0x6fc;
    class {
    public:
        u8 field_0x0[4];
        int field_0x4;
        csXyz field_0x8;
        fopAc_ac_c* mpActor;
        int field_0x14;
        cXyz mPosition;
        cXyz mScale;
        f32 mAlpha;
    }
    mBlure;
    f32 field_0x734;
    f32 field_0x738;
    f32 mZoomRatio;
    class {
    public:
        cXyz field_0x0;
        cXyz field_0xc;
        cXyz field_0x18;
        cSGlobe field_0x24;
    }
    mUpOverride;
    u8 field_0x76c[0x79c - 0x76c];
    class {
    public:
        u8 field_0x0[4];
        cXyz field_0x4;
    }
    field_0x79c;
    dCamMapToolData mRoomMapTool;
    dCamMapToolData mStageCamTool;
    dCamMapToolData mDefRoomCamTool;
    dCamMapToolData mTagCamTool;
    dCamMapToolData field_0x89c;
    dCamMapToolData field_0x8d8;
    f32 mWindowWidth;
    f32 mWindowHeight;
    f32 field_0x91c;
    f32 mTrimHeight;
    int mTrimSize;
    int mTrimTypeForce;
    f32 mWindowAspect;
    u8 field_0x930[0x930 - 0x92c];
    f32 mWallUpDist;
    int mWallRecoverStepCount;
    int field_0x93c;
    int mGear;
    u8 field_0x944;
    int mThrowTimer;
    cSAngle mBankOverride;
    int field_0x950;
    u8 field_0x954[0x958 - 0x954];
    int mLastBumpCase;
    cXyz field_0x95c;
    f32 field_0x968;
    f32 field_0x96c;
    dCamSetup_c mCamSetup;
    dCamParam_c mCamParam;
    u8 field_0xb0c;
    u8 field_0xb0d[0xd58 - 0xb0d];
};

dCamera_c* dCam_getBody();
camera_class* dCam_getCamera();
s16 dCam_getControledAngleY(camera_class* param_0);
s16 dCam_getAngleX(camera_class* i_cam);
s16 dCam_getAngleY(camera_class* i_cam);

#endif
