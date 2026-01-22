#include "main.h"
#include "game/machine.h"

int main() {
    printf("Hello from main() @ main.cpp\n");

    // dComIfG_ct() goes here

    // Relocating main01() logic to here
    mDoMch_Create();

    // More stuff goes here

    do {
        static u32 frame;
        frame++;

        if (frame > 0) {
            printf("One iteration of the game loop has passed, exitting.");
            break; // Immediately break out of the loop for now
        }
    } while (true);

    return 0;
}