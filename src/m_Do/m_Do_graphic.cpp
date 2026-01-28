#include "JSystem/JFramework/JFWSystem.h"
#include "SSystem/SComponent/c_math.h"
#include "d/d_com_inf_game.h"
#include "f_ap/f_ap_game.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_machine.h"
#include "m_Do/m_Do_main.h"

int mDoGph_Create() {
    std::cout << "mDoGph_Create() is partially stubbed" << std::endl;

    JKRSolidHeap* heap = mDoExt_createSolidHeapToCurrent(0, NULL, 0);
    mDoGph_gInf_c::create();
    // dComIfGd_init();
    u32 var_r30 = mDoExt_adjustSolidHeap(heap);
    mDoExt_restoreCurrentHeap();

    return 1;
}