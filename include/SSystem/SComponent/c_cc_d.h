#ifndef C_CC_D_H
#define C_CC_D_H

#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "SSystem/SComponent/c_m3d_g_cps.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"
#include "SSystem/SComponent/c_m3d_g_vtx.h"
#include "f_pc/f_pc_manager.h"

typedef struct _GXColor GXColor;
class fopAc_ac_c;

enum CcG_Tg_HitMark {
    CcG_Tg_UNK_MARK_0 = 0,
    CcG_Tg_UNK_MARK_1 = 1,
    CcG_Tg_UNK_MARK_2 = 2,
    CcG_Tg_UNK_MARK_3 = 3,
    CcG_Tg_UNK_MARK_6 = 6,
    CcG_Tg_UNK_MARK_8 = 8,
    CcG_Tg_UNK_MARK_9 = 9,
};

class cCcD_PntAttr;
class cCcD_CpsAttr;
class cCcD_TriAttr;
class cCcD_AabAttr;
class cCcD_CylAttr;
class cCcD_SphAttr;

enum cCcD_ObjAtType {
    AT_TYPE_0 = 0,
    AT_TYPE_1 = (1 << 0),
    AT_TYPE_NORMAL_SWORD = (1 << 1),  // wooden or ordon
    AT_TYPE_HORSE = (1 << 2),
    AT_TYPE_THROW_OBJ = (1 << 3),
    AT_TYPE_SHIELD_ATTACK = (1 << 4),
    AT_TYPE_BOMB = (1 << 5),
    AT_TYPE_40 = (1 << 6),
    AT_TYPE_SLINGSHOT = (1 << 7),
    AT_TYPE_100 = (1 << 8),
    AT_TYPE_LANTERN_SWING = (1 << 9),
    AT_TYPE_CSTATUE_SWING = (1 << 10),
    AT_TYPE_800 = (1 << 11),
    AT_TYPE_1000 = (1 << 12),
    AT_TYPE_ARROW = (1 << 13),
    AT_TYPE_HOOKSHOT = (1 << 14),
    AT_TYPE_8000 = (1 << 15),
    AT_TYPE_BOOMERANG = (1 << 16),
    AT_TYPE_20000 = (1 << 17),
    AT_TYPE_40000 = (1 << 18),
    AT_TYPE_SPINNER = (1 << 19),
    AT_TYPE_CSTATUE_BOSS_SWING = (1 << 20),
    AT_TYPE_HEAVY_BOOTS = (1 << 21),
    AT_TYPE_IRON_BALL = (1 << 22),
    AT_TYPE_COPY_ROD = (1 << 23),
    AT_TYPE_1000000 = (1 << 24),
    AT_TYPE_2000000 = (1 << 25),
    AT_TYPE_MASTER_SWORD = (1 << 26),
    AT_TYPE_MIDNA_LOCK = (1 << 27),
    AT_TYPE_10000000 = (1 << 28),
    AT_TYPE_20000000 = (1 << 29),
    AT_TYPE_WOLF_CUT_TURN = (1 << 30),
    AT_TYPE_WOLF_ATTACK = (1 << 31),
    AT_TYPE_UNK = 0xD8000000
};

struct cCcD_SrcTriAttr {
    cM3dGTriS mTri;
};

struct cCcD_SrcCpsAttr {
    cM3dGCpsS mCps;
};

struct cCcD_SrcSphAttr {
    cM3dGSphS mSph;
};

struct cCcD_SrcCylAttr {
    cM3dGCylS mCyl;
};

class cCcD_DivideInfo {
private:
    u32 mXDivInfo;
    u32 mYDivInfo;
    u32 mZDivInfo;
public:
    cCcD_DivideInfo() {}
    virtual ~cCcD_DivideInfo() {}
    void Set(u32, u32, u32);
    bool Chk(cCcD_DivideInfo const&) const;
};

class cCcD_DivideArea : public cM3dGAab {
private:
    bool mXDiffIsZero;
    f32 mScaledXDiff;
    f32 mInvScaledXDiff;
    bool mYDiffIsZero;
    f32 mScaledYDiff;
    f32 mInvScaledYDiff;
    bool mZDiffIsZero;
    f32 mScaledZDiff;
    f32 mInvScaledZDiff;
public:
    cCcD_DivideArea() {}
    virtual ~cCcD_DivideArea() {}
    void SetArea(cM3dGAab const&);
    void CalcDivideInfo(cCcD_DivideInfo*, cM3dGAab const&, u32);
    void CalcDivideInfoOverArea(cCcD_DivideInfo*, cM3dGAab const&);
};

struct cCcD_SrcObjCommonBase {
    s32 mSPrm;
};

struct cCcD_SrcObjTg {
    s32 mType;
    cCcD_SrcObjCommonBase mBase;
};

struct cCcD_SrcObjAt {
    s32 mType;
    u8 mAtp;
    cCcD_SrcObjCommonBase mBase;
};

struct cCcD_SrcObjCo {
    cCcD_SrcObjCommonBase mBase;
};

struct cCcD_SrcObjHitInf {
    cCcD_SrcObjAt mObjAt;
    cCcD_SrcObjTg mObjTg;
    cCcD_SrcObjCo mObjCo;
};

struct cCcD_SrcObj {
    int mFlags;
    cCcD_SrcObjHitInf mSrcObjHitInf;
};

class cCcD_GStts {
public:
    virtual ~cCcD_GStts() {}
private:
};

class cCcD_Stts {
private:
    cXyz m_cc_move;
    fopAc_ac_c* mp_actor;
    fpc_ProcID m_apid;
    u8 m_weight;
    u8 field_0x15;
    u8 m_dmg;
public:
    cCcD_Stts() {}
    virtual ~cCcD_Stts() {}
    virtual const cCcD_GStts* GetGStts() const;
    virtual cCcD_GStts* GetGStts();
    void Init(int, int, void*, fpc_ProcID);
    virtual void Ct();
    void PlusCcMove(f32, f32, f32);
    void ClrCcMove();
    void PlusDmg(int);
    f32 GetWeightF() const;
    virtual void ClrAt() {}
    virtual void ClrTg() { m_dmg = 0; }

    u8 GetWeightUc() const { return m_weight; }
    void SetWeight(u8 weight) { m_weight = weight; }
    fopAc_ac_c* GetAc() { return mp_actor; }
    fopAc_ac_c* GetActor() const { return mp_actor; }
    void SetActor(void* ac) { mp_actor = (fopAc_ac_c*)ac; }
    cXyz* GetCCMoveP() { return &m_cc_move; }
    fpc_ProcID GetApid() const { return m_apid; }
    u8 GetDmg() const { return m_dmg; }
};

class cCcD_Obj;

class cCcD_ObjCommonBase {
protected:
    u32 mSPrm;
    u32 mRPrm;
    cCcD_Obj* mHitObj;
public:
    enum CoSPrm_e {
        CO_SPRM_SET = 1,
        CO_SPRM_NO_CRR = 0x100,
        CO_SPRM_NO_CO_HIT_INF_SET = 0x200,
        CO_SPRM_SAME_ACTOR_HIT = 0x400,
    };

    cCcD_ObjCommonBase() { ct(); }
    virtual ~cCcD_ObjCommonBase() {}
    void ct();
    void SetSPrm(u32 sprm) { mSPrm = sprm; }
    s32 getSPrm() const { return mSPrm; }
    void setRPrm(s32 rprm) { mRPrm = rprm; }
    s32 getRPrm() const { return mRPrm; }
    cCcD_Obj* GetHitObj() { return mHitObj; }
    const cCcD_Obj* GetHitObj() const { return mHitObj; }
    u32 MskSPrm(u32 mask) const { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) const { return mRPrm & mask; }
    void OnSPrmBit(u32 flag) { mSPrm |= flag; }
    void OffSPrmBit(u32 flag) { mSPrm &= ~flag; }
    u32 ChkSPrm(u32 prm) const { return MskSPrm(prm) != 0; }

    void Set(cCcD_SrcObjCommonBase const& src) { mSPrm = src.mSPrm; }
};

#pragma push
#pragma pack(1)
class cCcD_ObjAt : public cCcD_ObjCommonBase {
public:
    cCcD_ObjAt() { Ct(); }
    void Ct() { mType = 0; }
    virtual ~cCcD_ObjAt() {}
    void SetHit(cCcD_Obj*);
    void Set(cCcD_SrcObjAt const&);
    void ClrHit();
    int GetType() const { return mType; }
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    u8 GetAtp() const { return mAtp; }
    u32 MskType(u32 msk) const { return mType & msk; }
    void SetType(u32 type) { mType = type; }
    void SetAtp(int atp) { mAtp = atp; }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() const { return MskRPrm(1); }

protected:
    int mType;
    u8 mAtp;
    u8 field_0x15[3];
};
#pragma pack()
#pragma pop

class cCcD_ObjTg : public cCcD_ObjCommonBase {
public:
    cCcD_ObjTg() { ct(); }
    virtual ~cCcD_ObjTg() {}
    void Set(cCcD_SrcObjTg const&);
    void SetGrp(u32);
    void ClrHit();
    void SetHit(cCcD_Obj*);
    int GetType() const { return mType; }
    void SetType(u32 type) { mType = type; }
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() const { return MskRPrm(1); }

private:
    int mType;
};

class cCcD_ObjCo : public cCcD_ObjCommonBase {
public:
    cCcD_ObjCo() { Ct(); }
    void Ct() {}
    virtual ~cCcD_ObjCo() {}
    void SetHit(cCcD_Obj*);
    void ClrHit();
    void SetIGrp(u32);
    void SetVsGrp(u32);
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    u32 GetVsGrp() const { return MskSPrm(0x70); }
    u32 GetIGrp() const { return MskSPrm(0xE); }
    u32 ChkNoCrr() const { return MskSPrm(0x100); }
    void OnNoCrrBit() { OnSPrmBit(0x100); }
    u32 ChkSph3DCrr() const { return MskSPrm(0x80); }
    u32 ChkCoSameActorHit() const { return MskSPrm(cCcD_ObjCommonBase::CO_SPRM_SAME_ACTOR_HIT); }
    void OnCoSameActorHit() { OnSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SAME_ACTOR_HIT); }
    void OffCoSameActorHit() { OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SAME_ACTOR_HIT); }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() const { return MskRPrm(1); }

    void Set(cCcD_SrcObjCo const& src) { cCcD_ObjCommonBase::Set(src.mBase); }
};

class cCcD_ObjHitInf {
protected:
    cCcD_ObjAt mObjAt;
    cCcD_ObjTg mObjTg;
    cCcD_ObjCo mObjCo;
public:
    virtual ~cCcD_ObjHitInf() {}
    void Set(cCcD_SrcObjHitInf const&);
    cCcD_ObjAt& GetObjAt() { return mObjAt; }
    cCcD_ObjTg& GetObjTg() { return mObjTg; }
    cCcD_ObjCo& GetObjCo() { return mObjCo; }
    u32 GetTgGrp() const { return mObjTg.GetGrp(); }
    u32 GetAtGrp() const { return mObjAt.GetGrp(); }
    u32 GetCoGrp() const { return mObjCo.GetGrp(); }
    int GetTgType() const { return mObjTg.GetType(); }
    u32 GetAtType() const { return mObjAt.GetType(); }
    bool ChkTgSet() const { return mObjTg.ChkSet(); }
    bool ChkAtSet() const { return mObjAt.ChkSet(); }
    bool ChkCoSet() const { return mObjCo.ChkSet(); }
    u32 ChkCoSameActorHit() const { return mObjCo.ChkCoSameActorHit(); }
    void OnCoSameActorHit() { mObjCo.OnCoSameActorHit(); }
    void OffCoSameActorHit() { mObjCo.OffCoSameActorHit(); }
    u32 GetCoVsGrp() const { return mObjCo.GetVsGrp(); }
    u32 GetCoIGrp() const { return mObjCo.GetIGrp(); }
    u8 GetAtAtp() const { return mObjAt.GetAtp(); }
    u32 ChkAtNoTgHitInfSet() const { return mObjAt.MskSPrm(0x20); }
    u32 ChkTgNoAtHitInfSet() const { return mObjTg.MskSPrm(0x20); }
    u32 ChkCoNoCoHitInfSet() const { return mObjCo.MskSPrm(0x200); }
    bool ChkTgNoSlingHitInfSet() const { return mObjTg.MskSPrm(0x40); }
    void SetAtHit(cCcD_Obj* obj) { mObjAt.SetHit(obj); }
    void SetTgHit(cCcD_Obj* obj) { mObjTg.SetHit(obj); }
    void SetCoHit(cCcD_Obj* obj) { mObjCo.SetHit(obj); }
    u32 ChkAtType(u32 type) const { return mObjAt.MskType(type); }
    u32 ChkCoNoCrr() const { return mObjCo.ChkNoCrr(); }
    void OnCoNoCrrBit() { mObjCo.OnNoCrrBit(); }
    u32 ChkCoSph3DCrr() const { return mObjCo.ChkSph3DCrr(); }
    void OnCoNoCoHitInfSet() { mObjCo.OnSPrmBit(0x200); }
    void OnAtSPrmBit(u32 flag) { mObjAt.OnSPrmBit(flag); }
    void OffAtSPrmBit(u32 flag) { mObjAt.OffSPrmBit(flag); }
    void OffTgSPrmBit(u32 flag) { mObjTg.OffSPrmBit(flag); }
    void OffCoSPrmBit(u32 flag) { mObjCo.OffSPrmBit(flag); }
    void SetAtType(u32 type) { mObjAt.SetType(type); }
    void OnAtSetBit() { mObjAt.OnSPrmBit(1); }
    void OnAtNoTgHitInfSet() { mObjAt.OnSPrmBit(0x20); }
    void OffAtNoTgHitInfSet() { mObjAt.OffSPrmBit(0x20); }
    u32 MskTgSPrm(u32 mask) const { return mObjTg.MskSPrm(mask); }
    void SetAtAtp(int atp) { mObjAt.SetAtp(atp); }
    void OffCoSetBit() { mObjCo.ClrSet(); }
    void SetTgType(u32 type) { mObjTg.SetType(type); }
    void OnTgSPrmBit(u32 flag) { mObjTg.OnSPrmBit(flag); }
    void OffAtSetBit() { mObjAt.ClrSet(); }
    void OnTgSetBit() { mObjTg.OnSPrmBit(1); }
    void OffTgSetBit() { mObjTg.ClrSet(); }
    void OnCoSetBit() { mObjCo.OnSPrmBit(1); }
    void OffAtVsEnemyBit() { mObjAt.OffSPrmBit(0x2); }
    void OnAtVsEnemyBit() { mObjAt.OnSPrmBit(0x2); }
    void OffAtVsPlayerBit() { mObjAt.OffSPrmBit(0xC); }
    void OnAtVsPlayerBit() { mObjAt.OnSPrmBit(0xC); }
    void OnCoSPrmBit(u32 flag) { mObjCo.OnSPrmBit(flag); }
    void SetCoVsGrp(u32 grp) { mObjCo.SetVsGrp(grp); }
    void SetCoIGrp(u32 grp) { mObjCo.SetIGrp(grp); }
    void SetTgGrp(u32 grp) { mObjTg.SetGrp(grp); }
    void SetAtSPrm(u32 prm) { mObjAt.SetSPrm(prm); }
    void SetTgSPrm(u32 prm) { mObjTg.SetSPrm(prm); }
    void SetCoSPrm(u32 prm) { mObjCo.SetSPrm(prm); }
    void ClrAtHit() { mObjAt.ClrHit(); }
    void ClrTgHit() { mObjTg.ClrHit(); }
    void ClrCoHit() { mObjCo.ClrHit(); }
    u32 ChkAtHit() const { return mObjAt.ChkHit(); }
    u32 ChkTgHit() const { return mObjTg.ChkHit(); }
    u32 ChkCoHit() const { return mObjCo.ChkHit(); }
    cCcD_Obj* GetAtHitObj() const { return (cCcD_Obj*)mObjAt.GetHitObj(); }
    cCcD_Obj* GetTgHitObj() const { return (cCcD_Obj*)mObjTg.GetHitObj(); }
    cCcD_Obj* GetCoHitObj() const { return (cCcD_Obj*)mObjCo.GetHitObj(); }
    u32 ChkAtSPrm(u32 prm) { return mObjAt.ChkSPrm(prm); }
    u32 ChkCoSPrm(u32 prm) const { return mObjCo.ChkSPrm(prm); }
    void OnTgNoSlingHitInfSet() { mObjTg.OnSPrmBit(0x40); }
    void OnAtVsBitSet(u32 prm) { mObjAt.OnSPrmBit(prm); }
    void OffAtVsBitSet(u32 prm) { mObjAt.OffSPrmBit(prm); }
    void OffTgNoAtHitInfSet() { mObjTg.OffSPrmBit(0x20); }
};

class cCcD_ShapeAttr {
public:
    cM3dGAab mAab;

    struct Shape {
        ~Shape() {}

        int _0;
        cXyz _4;
        f32 _10;
        f32 _14;
    };
    cCcD_ShapeAttr() {}
    virtual ~cCcD_ShapeAttr() {}
    virtual bool CrossAtTg(cCcD_ShapeAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const = 0;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const = 0;
    virtual bool CrossCo(cCcD_ShapeAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const = 0;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const = 0;
    virtual const cXyz& GetCoCP() const { return m_virtual_center; }
    virtual cXyz& GetCoCP() { return m_virtual_center; }
    virtual void CalcAabBox() = 0;
    virtual bool GetNVec(cXyz const&, cXyz*) const = 0;
    virtual void getShapeAccess(cCcD_ShapeAttr::Shape*) const;

    cM3dGAab& GetWorkAab() { return mAab; }
    cM3dGAab const& GetWorkAab() const { return mAab; }

    static cXyz m_virtual_center;
};

class cCcD_GObjInf;

class cCcD_Obj : public cCcD_ObjHitInf {
public:
    cCcD_Obj() { ct(); }
    virtual ~cCcD_Obj() {}
    virtual cCcD_GObjInf const* GetGObjInf() const { return NULL; }
    virtual cCcD_GObjInf* GetGObjInf() { return NULL; }
    virtual cCcD_ShapeAttr const* GetShapeAttr() const { return NULL; }
    virtual cCcD_ShapeAttr* GetShapeAttr() { return NULL; }
    virtual void Draw(_GXColor const&) {}
    void ct();
    void Set(cCcD_SrcObj const&);
    fopAc_ac_c* GetAc();

    cCcD_Stts* GetStts() { return mStts; }
    void SetStts(cCcD_Stts* stts) { mStts = stts; }
    cCcD_DivideInfo& GetDivideInfo() { return mDivideInfo; }
    cCcD_DivideInfo* GetPDivideInfo() { return &mDivideInfo; }
    int ChkBsRevHit() const { return mFlags & 2; }

private:
    int mFlags;
    cCcD_Stts* mStts;
    cCcD_DivideInfo mDivideInfo;
};

class cCcD_GObjInf : public cCcD_Obj {
public:
    cCcD_GObjInf() {}
    virtual ~cCcD_GObjInf() {}
    virtual void ClrAtHit() { cCcD_ObjHitInf::ClrAtHit(); }
    virtual void ClrTgHit() { cCcD_ObjHitInf::ClrTgHit(); }
    virtual void ClrCoHit() { cCcD_ObjHitInf::ClrCoHit(); }
    virtual cCcD_GObjInf const* GetGObjInf() const { return this; }
    virtual cCcD_GObjInf* GetGObjInf() { return this; }
};

class cCcD_PntAttr : public cCcD_ShapeAttr, public cM3dGVtx {
public:
    cCcD_PntAttr() {}
    virtual ~cCcD_PntAttr() {}
    virtual bool GetNVec(cXyz const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& param_0, cXyz* param_1) const { return param_0.CrossAtTg(*this, param_1); }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const { return false; }
    virtual bool CrossCo(const cCcD_ShapeAttr& param_0, f32* param_1) const { return param_0.CrossCo(*this, param_1); }
    virtual bool CrossCo(const cCcD_PntAttr&, f32*) const { return false; }
    virtual bool CrossCo(const cCcD_CpsAttr&, f32*) const { return false; }
    virtual bool CrossCo(const cCcD_TriAttr&, f32*) const { return false; }
    virtual bool CrossCo(const cCcD_AabAttr&, f32*) const { return false; }
    virtual bool CrossCo(const cCcD_CylAttr&, f32*) const { return false; }
    virtual bool CrossCo(const cCcD_SphAttr&, f32*) const { return false; }
    virtual void CalcAabBox() {}
};

class cCcD_CpsAttr : public cCcD_ShapeAttr, public cM3dGCps {
public:
    cCcD_CpsAttr() {}
    void Set(const cCcD_SrcCpsAttr& pSrc) { cM3dGCps::Set(pSrc.mCps); }
    void Set(const cXyz& pStart, const cXyz& pEnd, float radius) { cM3dGCps::Set(pStart, pEnd, radius); }

    virtual ~cCcD_CpsAttr() {}
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const { return shape.CrossAtTg(*this, xyz); }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const { return shape.CrossCo(*this, f); }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
};

class cCcD_TriAttr : public cCcD_ShapeAttr, public cM3dGTri {
public:
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const { return shape.CrossAtTg(*this, xyz); }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const { return shape.CrossCo(*this, f); }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const { return false; }
    virtual ~cCcD_TriAttr() {}
    cCcD_TriAttr() {}
};

class cCcD_CylAttr : public cCcD_ShapeAttr, public cM3dGCyl {
public:
    cCcD_CylAttr() {}
    virtual ~cCcD_CylAttr() {}
    virtual const cXyz& GetCoCP() const { return *GetCP(); }
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const { return shape.CrossAtTg(*this, xyz); }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const { return shape.CrossCo(*this, f); }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual cXyz& GetCoCP() { return *GetCP(); }
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
    virtual void getShapeAccess(cCcD_ShapeAttr::Shape*) const;
    void Set(const cCcD_SrcCylAttr& src) { cM3dGCyl::Set(src.mCyl); }

    const cM3dGCyl* GetShapeP() const { return this; }
};

class cCcD_SphAttr : public cCcD_ShapeAttr, public cM3dGSph {
public:
    cCcD_SphAttr() {}
    void Set(const cCcD_SrcSphAttr& src) { cM3dGSph::Set(src.mSph); }

    virtual ~cCcD_SphAttr() {}
    virtual const cXyz& GetCoCP() const { return *GetCP(); }
    virtual cXyz& GetCoCP() { return *GetCP(); }
    virtual bool CrossAtTg(cCcD_ShapeAttr const& shape, cXyz* xyz) const { return shape.CrossAtTg(*this, xyz); }
    virtual bool CrossAtTg(cCcD_PntAttr const&, cXyz*) const { return false; }
    virtual bool CrossAtTg(cCcD_AabAttr const&, cXyz*) const { return false; }
    virtual bool CrossCo(cCcD_ShapeAttr const& shape, f32* f) const { return shape.CrossCo(*this, f); }
    virtual bool CrossCo(cCcD_PntAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_TriAttr const&, f32*) const { return false; }
    virtual bool CrossCo(cCcD_AabAttr const&, f32*) const { return false; }
    virtual bool CrossAtTg(cCcD_CylAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_TriAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_CpsAttr const&, cXyz*) const;
    virtual bool CrossAtTg(cCcD_SphAttr const&, cXyz*) const;
    virtual bool CrossCo(cCcD_CpsAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_SphAttr const&, f32*) const;
    virtual bool CrossCo(cCcD_CylAttr const&, f32*) const;
    virtual void CalcAabBox();
    virtual bool GetNVec(cXyz const&, cXyz*) const;
    virtual void getShapeAccess(cCcD_ShapeAttr::Shape*) const;

    const cM3dGSph* GetShapeP() const { return this; }
};

#endif
