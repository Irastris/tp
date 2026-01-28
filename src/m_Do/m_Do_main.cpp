#include "m_Do/m_Do_main.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "c/c_dylink.h"
#include "d/d_com_inf_game.h"
#include "f_ap/f_ap_game.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_machine.h"

#include <aurora/aurora.h>
#include <aurora/event.h>
#include <aurora/main.h>

static u32 frame;

s32 LOAD_COPYDATE(void*) {
    std::cout << "LOAD_COPYDATE() is stubbed" << std::endl;

    /* DVDFileInfo ATTRIBUTE_ALIGN(32) fileInfo;
    u8 buffer[32];

    BOOL status = DVDOpen("/str/Final/Release/COPYDATE", &fileInfo);
    if (status) {
        s32 rt = DVDReadPrio(&fileInfo, &buffer, sizeof(buffer), 0, 2);
        char COPYDATE_STRING[18] = "??/??/?? ??:??:??";
        memcpy(COPYDATE_STRING, buffer, sizeof(COPYDATE_STRING) - 1);
        status = DVDClose(&fileInfo);
    } */

    return 1; // status;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello from main() @ m_Do_main.cpp" << std::endl;
    
    // Aurora initialization
    const AuroraConfig auroraConfig{
        .appName = "Zelda: Twilight Princess",
        .desiredBackend = BACKEND_VULKAN,
        .windowWidth = 640,
        .windowHeight = 480,
    };

    const AuroraInfo auroraInfo = aurora_initialize(argc, argv, &auroraConfig);

    // TODO: Determine if reset data logic should remain
    
    dComIfG_ct();

    // main01() logic below
    mDoMch_Create();

    mDoGph_Create();

    mDoCPd_c::create();

    mDoDvdThd_callback_c::create((mDoDvdThd_callback_func)LOAD_COPYDATE, NULL);

    fapGm_Create();

    // More stuff goes here

    bool exiting = false;
    while (1) {
        const auto* event = aurora_update();

        while (event != nullptr && event->type != AURORA_NONE) {
            if (event->type == AURORA_EXIT)
            {
                exiting = true;
                break;
            }
            
            ++event;
        }

        if (exiting) {
            break;
        }

        if (!aurora_begin_frame()) {
            continue;
        }

        /* if (mDoDvdThd::SyncWidthSound) {
            mDoMemCd_UpDate();
        }

        mDoCPd_c::read();   // read controller input

        fapGm_Execute();    // handle game execution

        mDoAud_Execute();   // handle audio execution */
        
        frame++;

        aurora_end_frame();

        // frame_limiter
    };

    aurora_shutdown();

    return 0;
}