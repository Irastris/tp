#include "main.h"
#include "game/machine.h"

void main01() {
    mDoMch_Create();

    // More stuff goes here

    do {
        static u32 frame;
        frame++;

        // Immediately break out of the loop for now
        break;
    } while (true);
}

int main() {
    printf("Hello from main() @ main.cpp\n");

    // dComIfG_ct() goes here

    main01();

    return 0;
}