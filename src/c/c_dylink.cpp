#include "c/c_dylink.h"
/* #include "DynamicLink.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRFileCache.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h" */

int cCc_Init() {
    std::cout << "cCc_Init() is stubbed" << std::endl;
    return 1;
}

BOOL cCc_Check() {
    std::cout << "cCc_Check() is stubbed" << std::endl;
    return TRUE;
}

BOOL cDyl_IsInitialized() {
    std::cout << "cDyl_IsInitialized() is stubbed" << std::endl;
    return FALSE;
}

BOOL cDyl_IsLinked(s16 i_ProfName) {
    std::cout << "cDyl_IsLinked() is stubbed" << std::endl;
    return TRUE;
}

BOOL cDyl_Unlink(s16 i_ProfName) {
    std::cout << "cDyl_Unlink() is stubbed" << std::endl;
    return FALSE;
}

int cDyl_LinkASync(s16 i_ProfName) {
    std::cout << "cDyl_LinkASync() is stubbed" << std::endl;
    return cPhs_COMPLEATE_e;
}

static int cDyl_InitCallback(void* param_0) {
    std::cout << "cDyl_InitCallback() is stubbed" << std::endl;
    return 1;
}

void cDyl_InitAsync() {
    std::cout << "cDyl_InitAsync() is stubbed" << std::endl;
}

int cDyl_InitAsyncIsDone() {
    std::cout << "cDyl_InitAsyncIsDone() is stubbed" << std::endl;
    return 1;
}

int cDylPhs::phase_01(void* param_0) {
    std::cout << "cDylPhs::phase_01() is stubbed" << std::endl;
    return cPhs_NEXT_e;
}

int cDylPhs::phase_02(s16* p_profName) {
    std::cout << "cDylPhs::phase_02() is stubbed" << std::endl;
    return cPhs_NEXT_e;
}

int cDylPhs::phase_03(void* param_0) {
    std::cout << "cDylPhs::phase_03() is stubbed" << std::endl;
    return cPhs_INIT_e;
}

int cDylPhs::Link(request_of_phase_process_class* i_phase, s16 i_ProfName) {
    std::cout << "cDylPhs::Link() is stubbed" << std::endl;
    return cPhs_COMPLEATE_e;
}

int cDylPhs::Unlink(request_of_phase_process_class* i_phase, s16 i_ProfName) {
    std::cout << "cDylPhs::Unlink() is stubbed" << std::endl;
    return 0;
}
