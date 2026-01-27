#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include <dolphin/mtx.h>
#include "f_pc/f_pc_base.h"
#include "SSystem/SComponent/c_bg_s_grp_pass_chk.h"
#include "SSystem/SComponent/c_bg_s_poly_pass_chk.h"

struct cBgD_Vtx_t : public Vec {};

class cBgS_Chk {
public:
    cBgS_PolyPassChk* mPolyPassChk;
    cBgS_GrpPassChk* mGrpPassChk;
    fpc_ProcID mActorPid;
    bool mSameActorChk;

public:
    cBgS_Chk();
    void SetExtChk(cBgS_Chk&);
    bool ChkSameActorPid(fpc_ProcID) const;

    void SetActorPid(fpc_ProcID pid) { mActorPid = pid; }
    fpc_ProcID GetActorPid() const { return mActorPid; }
    void SetPolyPassChk(cBgS_PolyPassChk* p_chk) { mPolyPassChk = p_chk; }
    void SetGrpPassChk(cBgS_GrpPassChk* p_chk) { mGrpPassChk = p_chk; }
    cBgS_PolyPassChk* GetPolyPassChk() const { return mPolyPassChk; }
    cBgS_GrpPassChk* GetGrpPassChk() const { return mGrpPassChk; }
    void OffSameActorChk() { mSameActorChk = false; }

    virtual ~cBgS_Chk();
};

#endif
