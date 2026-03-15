// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero
//
// The project is not associated with Nintendo Co., Ltd.

#include <3ds.h>
#include <stdio.h>

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, nullptr);
    printf("Hi!\n");
    while (aptMainLoop()) {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    gfxExit();
    return 0;
}
