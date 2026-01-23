#include "main.h"
#include "game/machine.h"

int main(int argc, char* argv[]) {
    printf("Hello from main() @ main.cpp\n");

    // Aurora initialization
    const AuroraConfig config{
        .appName = "Zelda: Twilight Princess",
    };

    const AuroraInfo auroraInfo = aurora_initialize(argc, argv, &config);

    // dComIfG_ct() goes here

    // main01() logic below
    mDoMch_Create();

    // More stuff goes here

    bool exiting = false;
    do {
        // TODO: From decomp, might not be the ideal with Aurora involved
        static u32 frame;
        frame++;

        const auto* event = aurora_update();

        while (event != nullptr && event->type != AURORA_NONE) {
            switch (event->type) {
                case AURORA_EXIT:
                    exiting = true;
                    break;
                case AURORA_SDL_EVENT:
                case AURORA_WINDOW_RESIZED:
                case AURORA_WINDOW_MOVED:
                case AURORA_CONTROLLER_ADDED:
                case AURORA_CONTROLLER_REMOVED:
                case AURORA_PAUSED:
                case AURORA_UNPAUSED:
                case AURORA_DISPLAY_SCALE_CHANGED:
                default:
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
        
        // TODO: Implement a frame limiter

        aurora_end_frame();
    } while (exiting);

    aurora_shutdown();

    return 0;
}