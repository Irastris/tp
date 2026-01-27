#include "main.h"

static u32 frame;

int main(int argc, char* argv[]) {
    std::cout << "Hello from main() @ main.cpp (m_Do_main)" << std::endl;
    
    // Aurora initialization
    const AuroraConfig auroraConfig{
        .appName = "Zelda: Twilight Princess",
        .desiredBackend = BACKEND_VULKAN,
        .windowWidth = 640,
        .windowHeight = 480,
    };

    const AuroraInfo auroraInfo = aurora_initialize(argc, argv, &auroraConfig);

    // TODO: Determine if reset data logic should remain
    /* mDoRst::setResetData((mDoRstData*)OSAllocFromArenaLo(0x18, 4));

    if (!mDoRst::getResetData()) {
        do {
        } while (true);
    }

    if (!((OSGetResetCode() & 0x80000000) ? 1 : 0)) {
        mDoRst::offReset();
        mDoRst::offResetPrepare();
        mDoRst::off3ButtonReset();
        mDoRst::set3ButtonResetPort(-1);
        mDoRst::setLogoScnFlag(0);
        mDoRst::setProgSeqFlag(0);
        mDoRst::setProgChgFlag(0);
        mDoRst::setWarningDispFlag(0);
        mDoRst::offShutdown();
        mDoRst::offReturnToMenu();
    } */
    
    dComIfG_ct();

    // main01() logic below
    mDoMch_Create();

    mDoGph_Create();

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